#include <stdio.h>
#include <stdlib.h>

#include "../lib/parser.h"

void parse(FILE* file) {
    int current_char;
    STATE_MACHINE_RETURN_VALUE result = STATE_MACHINE_READY;
    while ((current_char = fgetc(file)) != EOF) {
        result = parse_char(current_char);
        switch (result) {
            case STATE_MACHINE_READY: {
                print_data();
                break;
            }
            case STATE_MACHINE_ERROR: {
                return;
            }
            case STATE_MACHINE_NOT_READY:
                break;
        }
    }
    if (result == STATE_MACHINE_NOT_READY) {
        printf("error: incomplete response at end of file\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("error: no file specified\n");
        printf("usage: ./main.exe file.txt\n");
        printf("                  ^^^^^^^^\n");
        return EXIT_FAILURE;
    } else if (argc > 2) {
        printf("error: too many arguments\n");
        printf("usage: ./main.exe file.txt\n");
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");

    if (!file) {
        printf("error: could not open file %s\n", filename);
        return EXIT_FAILURE;
    }

    parse(file);
    fclose(file);

    return 0;
}