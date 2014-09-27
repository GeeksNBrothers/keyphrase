#include "constants.h"

int is_hex(char arg[]);
int get_word(char buffer[], char hex_chunk[], char *wordlist[]);
int is_hex_padded(char hex_string[]);
int normalized_hex_string_length(char hex_string[]);
int normalize_hex_string(char buffer[], char hex_string[]);
int max_phrase_length(char hex_string[]);
int get_phrase(char buffer[], char hex_string[], char *wordlist[]);
int index_of_word(char *word, char *wordlist[], int numwords);
int hex_chunk(char buffer[HEX_CHUNK_LENGTH+1], int source);
int wordcount(char phrase[]);
int key_length(char phrase[]);
int get_key(char key[], char phrase[], char* wordlist[], int wordlist_size);
