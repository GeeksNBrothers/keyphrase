#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "funcs.h"

int is_hex_padded(char hex[]) {
    int length = strlen(hex);
    return (length >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'));
}

int normalized_hex_string_length(char hex_string[]) {
    int length = strlen(hex_string);
    
    if (is_hex_padded(hex_string)) {
        length -= 2;
    }

    if (length % HEX_CHUNK_LENGTH != 0) {
        length += (HEX_CHUNK_LENGTH - (length % HEX_CHUNK_LENGTH));
    }

    return length;
}

int normalize_hex_string(char buffer[], char hex_string[]) {
    memset(buffer, 0, sizeof(*buffer));

    if (is_hex_padded(hex_string)) {
        hex_string += 2;
    }
    strcpy(buffer, hex_string);
    
    int length = strlen(hex_string);
    while (length % HEX_CHUNK_LENGTH != 0) {
        strcat(buffer, "0");
        length++;
    }

    return 0;
}

int is_hex(char arg[]) {
    int index = 0;
    int result = 1;
    int length = strlen(arg);

    if (length == 0) {
        return 0;

    } else if (is_hex_padded(arg)) {
        index = 2;
    }

    while (index < length && result) {
        result = isxdigit(arg[index]);
        index += 1;
    }

    return result;
}

int get_word(char buffer[], char hex_chunk[], char *wordlist[]) {
    strcpy(buffer, wordlist[(int) strtol(hex_chunk, 0, 16)]);
    return 0;
}

int max_phrase_length(char hex_string[]) {
    int length = normalized_hex_string_length(hex_string);
    return (length / HEX_CHUNK_LENGTH) * (WORDLENGTH + 1) - 1;
}

int get_phrase(char buffer[], char hex_string[], char *wordlist[]) {
    memset(buffer, 0, sizeof(*buffer));

    int length = strlen(hex_string);
    char hex_quad[4];
    char word[11];

    for (int i=0; i < length / 4; i++) {
        strncpy(hex_quad, hex_string + (i*4), 4);

        if (i != 0) {
            strcat(buffer, " ");
        }
        get_word(word, hex_quad, wordlist);
        strcat(buffer, word);
    }

    return 0;
}
