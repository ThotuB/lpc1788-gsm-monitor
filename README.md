# GSM AT Command Parser

A byte-at-a-time state machine that parses responses from a GSM modem
(SIMCOM SIM908) to AT commands. It runs both on a PC, against captured
responses, and on an NXP LPC1788 board talking to the modem over UART.

See [commands.md](commands.md) for the supported commands and their expected
responses. [diagram.png](diagram.png) sketches the core of the state machine
(states 0–15); the SMS states 16–21 were added later and are only in the code.

## Layout

| Path | Contents |
| --- | --- |
| `app/lib/` | The parser (`parse_char`, `print_data`, `get_data`) |
| `app/src/main.c` | PC tool: feeds a capture file through the parser |
| `app/test/` | Captured modem responses: basic commands (`c/`), `AT+GMx` info (`g/`), SMS (`sms/`) |
| `keil/` | Keil µVision project for the LPC1788 board (UART3 modem, touchscreen LCD UI) |

## Supported commands

These are standard GSM modem commands (ITU-T V.250 and 3GPP TS 27.007). The
example values come from the test files; [commands.md](commands.md) shows the
exact bytes of each response.

### Device info

These reply with a single plain line, then `OK`.

| Command | Meaning | Example |
| --- | --- | --- |
| `AT+GMI` | Manufacturer | `SIMCOM_Ltd` |
| `AT+GMM` | Model | `SIMCOM_SIM908` |
| `AT+GMR` | Firmware revision | `Revision:1137B04SIM908M64_ST` |
| `AT+GSN` | Serial number (the IMEI on a GSM modem) | `861001003112683` |

### Network

These reply with one or more lines starting with `+`, then `OK`.

| Command | Meaning | Example |
| --- | --- | --- |
| `AT+CSQ` | Signal quality: `<rssi>,<ber>` | `+CSQ: 21,0` |
| `AT+CREG?` | Network registration: `<mode>,<status>` | `+CREG: 0,1` |
| `AT+COPS?` | Operator currently in use | `+COPS: 0,0,"Idea"` |
| `AT+COPN` | Operator names stored in the modem, one per line: `"<MCC><MNC>","<name>"` | `+COPN: "41201","AF AWCC"` |

- **`+CSQ`:** `rssi` ranges from 0 to 31, and dBm = −113 + 2 × rssi, so 21 is
  −71 dBm. `ber` is the bit error rate, 0 to 7. For either value, `99` means
  unknown or not measured.
- **`+CREG`:** a status of `1` means registered on the home network, and `5`
  means registered while roaming.
- **`+COPN`:** MCC is the country code and MNC the network code; `412` is
  Afghanistan. The list runs to hundreds of entries.

### SMS

`AT+CMGL` lists the stored text messages (`AT+CMGL="ALL"` in text mode). Each
message is a header line followed by its text and a blank line:

```
+CMGL: 2,"REC READ","+40722000001","","20/11/08,16:48:54+08"
LalalalalLalLLLalalalala
```

| Field | Meaning |
| --- | --- |
| `2` | Storage index |
| `"REC READ"` | Status: `REC READ`, `REC UNREAD`, `STO SENT` or `STO UNSENT` |
| `"+40722000001"` | Sender |
| `""` | Sender's phonebook name |
| `"20/11/08,16:48:54+08"` | Timestamp `yy/MM/dd,hh:mm:ss±zz`; the time zone `zz` is in quarter hours, so `+08` is UTC+2 |

## Building and running on a PC

```sh
cd app
make build
bin/main.exe test/c/test_file_csq_ok.txt
```

Each complete response is printed with its status and data lines:

```
Status: OK
  1: CSQ: 21,0
```

Malformed input prints the line and column, the parser state, and the
character that was expected. A file that ends partway through a response
prints `error: incomplete response at end of file`.

## Test files

Modem responses use `<CR><LF>` line endings, so the test captures must too.
`.gitattributes` checks them out with CRLF on every platform. The exception is
`test_file_csq_not_ok_4_no_cr_present.txt`, which deliberately has none.

## Firmware

Open `keil/test.uvproj` in Keil µVision 4/5 and build for the LPC1788 target.
The firmware's version of the parser lives in `keil/code/Parser.c`; it is
older than `app/lib/parser.c` and has diverged from it.
