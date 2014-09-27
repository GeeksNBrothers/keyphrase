#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "funcs.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        return printf("usage: %s [hex key] [key phrase]\n", argv[0]);
    }

    char *wordlist[NUMWORDS];
    FILE *fp = fopen(WORDFILE, "r");

    if (!fp) {
       printf("Could not find wordlist: '%s' is missing!\n", WORDFILE); 
       return 1;
    }

    for(int i=0; i < NUMWORDS; i++) {
        wordlist[i] = malloc(WORDLENGTH + 1);
        fgets(wordlist[i], WORDLENGTH + 1, fp);
        for (int j=strlen(wordlist[i])-1; j>=0 && (wordlist[i][j] == '\n' || wordlist[i][j]=='\r'); j--) {
            wordlist[i][j]='\0';
        }
    }

    if (is_hex(argv[1])) {

        char hex[normalized_hex_string_length(argv[1])];
        normalize_hex_string(hex, argv[1]);

        char phrase[max_phrase_length(hex)];
        get_phrase(phrase, hex, wordlist);

        printf("%s\n", phrase);

    } else {
        char key[key_length(argv[1])];
        get_key(key, argv[1], wordlist, NUMWORDS);
        printf("0x%s\n", key);
    }

    for (int i=0; i < NUMWORDS; i++) {
        free(wordlist[i]);
    }
}
