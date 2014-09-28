#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
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
        length = (length / HEX_CHUNK_LENGTH + 1) * HEX_CHUNK_LENGTH;
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
    int normalized_length = normalized_hex_string_length(hex_string);
    int gap = (normalized_length - length);

    for (int i=normalized_length; i > 0 && gap; i--) {
        buffer[i] = buffer[i - gap];
    }
    for (int i=0; i < gap; i++) {
        buffer[i] = '0';
    }
    buffer[normalized_length] = '\0';

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

int wordlist_cmp(const void *s1, const void *s2) {
    const char *key = s1;
    const char * const *arg = s2;
    return strcmp(key, *arg);
}

int index_of_word(char *word, char *wordlist[], int numwords) {
    char **ptr = (char**) bsearch(word, wordlist, numwords, sizeof(char *), wordlist_cmp);
    return ptr ? (ptr - wordlist) : -1;
}

int hex_chunk(char buffer[HEX_CHUNK_LENGTH+1], int source) {
    sprintf(buffer, HEX_CHUNK_FORMAT, source);
    return 0;
}

int wordcount(char phrase[]) {
    int count = 0;
    int length = strlen(phrase);
    int in_word = 0;

    for (int i=0; i < length; i++) {
        if (phrase[i] == '\t' || phrase[i] == '\n' || phrase[i] == ' ' || phrase[i] == '\r' || phrase[i] == '\0') {
            count += in_word;
            in_word = 0;
        } else {
            in_word = 1;
        }
    }
    count += in_word;

    return count;
}

int key_length(char phrase[]) {
    return wordcount(phrase) * HEX_CHUNK_LENGTH;
}

int get_key(char key[], char phrase[], char *wordlist[], int wordlist_size, char err_msg[]) {
    int length = strlen(phrase);
    int char_index = 0;
    int word_index;
    int on_whitespace = 0;
    char word[WORDLENGTH+1];
    char chunk[HEX_CHUNK_LENGTH+1];
    memset(word, 0, sizeof(*word));
    memset(chunk, 0, sizeof(*chunk));
    memset(key, 0, sizeof(*key));
    memset(err_msg, 0, sizeof(*err_msg));

    for (int i=0; i < length; i++) {
        on_whitespace = (phrase[i] == '\t' || phrase[i] == '\n' || phrase[i] == ' ' || phrase[i] == '\r' || phrase[i] == '\0');

        if (!on_whitespace) {
            word[char_index] = phrase[i];
            char_index++;
        }
        
        if (char_index && (on_whitespace || char_index == WORDLENGTH || i+1 == length)) {
            word[char_index] = '\0';
            word_index = index_of_word(word, wordlist, wordlist_size);

            if (word_index == -1) {
                sprintf(err_msg, "Could not find '%s' in the wordlist!", word);
                return 1;
            }

            hex_chunk(chunk, word_index);
            strcat(key, chunk);

            memset(word, 0, sizeof(*word));
            memset(chunk, 0, sizeof(*chunk));
            char_index = 0;
            on_whitespace = 0;
        }
    }

    return 0;
}
