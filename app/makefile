CC     = gcc
CFLAGS = -Wall -Wextra -O3
BIN    = bin

LIB    = lib/parser.c lib/parser.h
MAIN   = $(BIN)/main
TESTER = $(BIN)/tester

TEST_FILES = $(sort $(wildcard test/*/*.txt))

.PHONY: all build run test clean

all: build

build: $(MAIN) $(TESTER)

$(MAIN): src/main.c $(LIB) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

$(TESTER): test/tester.c $(LIB) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

$(BIN):
	mkdir -p $@

# make run FILE=test/c/test_file_csq_ok.txt
run: $(MAIN)
	@test -n "$(FILE)" || { echo "usage: make run FILE=path/to/file.txt"; exit 1; }
	$(MAIN) $(FILE)

# Files with "nok" or "not_ok" in their name must be rejected; all others must parse.
test: $(TESTER)
	@pass=0; fail=0; \
	for f in $(TEST_FILES); do \
		case $$f in *nok*|*not_ok*) expect=1 ;; *) expect=0 ;; esac; \
		if $(TESTER) $$f > /dev/null; then got=0; else got=1; fi; \
		if [ $$got = $$expect ]; then \
			pass=$$((pass + 1)); echo "PASS  $$f"; \
		else \
			fail=$$((fail + 1)); echo "FAIL  $$f"; \
		fi; \
	done; \
	echo "$$pass passed, $$fail failed"; \
	[ $$fail = 0 ]

clean:
	rm -rf $(BIN)
