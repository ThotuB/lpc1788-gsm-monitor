
# AUTOBAUD Commands
## AT Command

```
< AT

> <CR><LF>
> OK<CR><LF>
```

## Error Command

```
< AT+

> <CR><LF>
> ERROR<CR><LF>
```

## RSSI Value in ASU

```
< AT+CSQ

> <CR><LF>
> +CSQ: 31,99<CR><LF>
> <CR><LF>
> OK<CR><LF>
```

## Status of Network Registration

```
< AT+CREG?

> <CR><LF>
> +CREG: 0,1<CR><LF>
> <CR><LF>
> OK<CR><LF>
```

## Selected Network Operator

```
< AT+COPS?

> <CR><LF>
> +COPS: 0,0,"Idea"<CR><LF>
> <CR><LF>
> OK<CR><LF>
```

## List of Network Operators

```
< AT+COPN

> <CR><LF>
> +COPN: "001010","Test PA128-PA4"<CR><LF>
> +COPN: "00101","Test PA128-PA4"<CR><LF>
> +COPN: "20201","GR COSMOTE"<CR><LF>
> +COPN: "20205","vodafone GR"<CR><LF>
> +COPN: "310160","T-Mobile"<CR><LF>
> +COPN: "31016","T-Mobile"<CR><LF>
> +COPN: "310170","AT&T"<CR><LF>
> +COPN: "356110","C&W"<CR><LF>
> +COPN: "90115","OnAir"<CR><LF>
> +COPN: "90117","Navitas1"<CR><LF>
> +COPN: "90118","Maritime Wireless"<CR><LF>
> ...
> <CR><LF>
> OK<CR><LF>
```

## IMEI

```
< AT+CGSN

> <CR><LF>
> 359357080000000<CR><LF>
> <CR><LF>
> OK<CR><LF>
```
