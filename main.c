#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char flip; // 0 if starts with lower case otherwise 0
    char resetAtNewWords; // 0 / 1
    unsigned char upperSpan;
    unsigned char lowerSpan;
} Options;

void curser(char* text, Options options);

int main(int argc, char **argv){
    if (argc < 2) {
        return 0;
    }
    Options options = {0,0,1,1};
    int opt;

    while ((opt = getopt(argc, argv, "hiu:l:n")) != -1) {
        switch (opt) {
            case 'i':
                options.flip = 1;
                break;
            case 'l':
                options.lowerSpan = atoi(optarg);
                break;
            case 'u':
                options.upperSpan = atoi(optarg);
                break;
            case 'n':
                options.resetAtNewWords = 1;
                break;
            case 'h':
            default:
                printf("Usage: %s [-i] [-u <value>] [-l <value>] <type content here>\n"
                        "-i         | Flipping the order\n"
                        "-u <value> | Set the number of UPPER cased letters the span\n"
                        "-l <value> | Set the number of LOWER cased letters the span\n", argv[0]);
        }
    }

    for (int i = optind; i < argc; i++) {
        curser(argv[i], options);
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}

void curser(char* text, Options options){
    static char flipflop = -1;
    if(options.resetAtNewWords || flipflop == -1)
        flipflop = options.flip;
    static char upperCounter = 0;
    static char lowerCounter = 0;

    int len = (int)strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] >= 65 || text[i] <= 90 ||
            text[i] >= 97 || text[i] <= 122) {

            if (flipflop == 0) {
                text[i] = tolower(text[i]);
                lowerCounter++;
                if (lowerCounter >= options.lowerSpan) {
                    flipflop = 1;
                    lowerCounter = 0;
                }
            }
            else {
                text[i] = toupper(text[i]);
                upperCounter++;
                if (upperCounter >= options.upperSpan) {
                    flipflop = 0;
                    upperCounter = 0;
                }
            }
        }
    }
}
