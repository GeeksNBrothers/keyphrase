#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "funcs.h"
#include "constants.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[1;37;41m"
#define KGRN  "\x1B[1;42;37m"

/***************************
 * Key to phrase functions
 ***************************/

static char * is_hex_01a() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return true for hex strings with leading '0x's", is_hex(hex));

    return 0;
}

static char * is_hex_01b() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return true for hex strings with leading '0X's", is_hex(hex));

    return 0;
}

static char * is_hex_01c() {
    char hex[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return true for hex strings without leading '0x's", is_hex(hex));

    return 0;
}

static char * is_hex_02a() {
    char phrase[] = "foo bar is not hex";
    
    _it_should("return false for non-hex strings", !is_hex(phrase));

    return 0;
}

static char * is_hex_02b() {
    char phrase[] = "0xBEINGSNEAKY";
    
    _it_should("return false for non-hex strings that start with 0x", !is_hex(phrase));
    
    return 0;
}

static char * is_hex_02c() {
    char phrase[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2AZ";
    
    _it_should("return false even if the only non-hex character is the last one", !is_hex(phrase));

    return 0;
}

static char * is_hex_padded_01a() {
    char hex[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return false if hex string doesn't start with '0x'", !is_hex_padded(hex));

    return 0;
}

static char * is_hex_padded_02a() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return true if hex string starts with '0x'", is_hex_padded(hex));

    return 0;
}

static char * is_hex_padded_02b() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    
    _it_should("return true if hex string starts with '0X'", is_hex_padded(hex));

    return 0;
}

static char * get_word_01a() {
    char hex[] = "0000";
    char *wordlist[] = {"aahing", "aardvark", "aardvarks", "aardwolf"}; 
    char word[WORDLENGTH];
    get_word(word, hex, wordlist);

    _it_should("return the first word in the wordlist when given '0000'", strcmp(word, "aahing") == 0);

    return 0;
}

static char * get_word_01b() {
    char hex[] = "0003";
    char *wordlist[] = {"aahing", "aardvark", "aardvarks", "aardwolf"}; 
    char word[WORDLENGTH];
    get_word(word, hex, wordlist);
    
    _it_should("return the fourth word in the wordlist when given '0003'", strcmp(word, "aardwolf") == 0);

    return 0;
}

static char * max_phrase_length_01a() {
    char hex[] = "00020000000100030000";
    _it_should("return 59 (words plus spaces) for a hex string of 5 quads", max_phrase_length(hex) == 59);

    return 0;
}

static char * max_phrase_length_01b() {
    char hex[] = "00020000000100030000";
    _it_should("return 59 (words plus spaces) for a hex string of 9 characters", max_phrase_length(hex) == 59);

    return 0;
}

static char * normalized_hex_string_length_01a() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    int expected_length = strlen(hex) - 2;
    _it_should("return the normalized length of strings with leading '0x's", normalized_hex_string_length(hex) == expected_length);

    return 0;
}

static char * normalized_hex_string_length_01b() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    int expected_length = strlen(hex) - 2;
    _it_should("return the normalized length of strings with leading '0X's", normalized_hex_string_length(hex) == expected_length);

    return 0;
}

static char * normalized_hex_string_length_01c() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    int expected_length = strlen(hex) - 1;
    _it_should("return the normalized length of strings with leading '0x's and an odd number of characters", normalized_hex_string_length(hex) == expected_length);

    return 0;
}

static char * normalized_hex_string_length_01d() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    int expected_length = strlen(hex) - 1;
    _it_should("return the normalized length of strings with leading '0X's and an odd number of characters", normalized_hex_string_length(hex) == expected_length);

    return 0;
}

static char * normalize_hex_string_01a() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    char expected[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0x's", strcmp(buffer, expected) == 0);

    return 0;
}

static char * normalize_hex_string_01b() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    char expected[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A3";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0X's", strcmp(buffer, expected) == 0);

    return 0;
}

static char * normalize_hex_string_01c() {
    char hex[] = "0xB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    char expected[] = "0B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0x's and an odd number of characters", strcmp(buffer, expected) == 0);

    return 0;
}

static char * normalize_hex_string_01d() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    char expected[] = "0B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0X's and an odd number of characters", strcmp(buffer, expected) == 0);

    return 0;
}

static char * normalize_hex_string_01e() {
    char hex[] = "FFFFFFFFF";
    char expected[] = "000FFFFFFFFF";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings without leading '0x's and only 9 characters", strcmp(buffer, expected) == 0);

    return 0;
}


static char * get_phrase_01a() {
    char hex[] = "00020000000100030000";
    char *wordlist[] = {"aahing", "aardvark", "aardvarks", "aardwolf"}; 
    char expected_phrase[] = "aardvarks aahing aardvark aardwolf aahing";
    char phrase[max_phrase_length(hex) + 1];
    get_phrase(phrase, hex, wordlist);

    _it_should("return a valid phrase given a normalized string of hex pairs", strcmp(phrase, expected_phrase) == 0);

    return 0;
}

/***************************
 * Phrase to key functions
 ***************************/
static char * index_of_word_01a() {
    char word[] = "aardvarks";
    char *wordlist[4] = {"aahing\0\0\0\0\0", "aardvarik\0\0\0\0", "aardvarks\0\0\0", "aardwolf\0\0\0"}; 
    int numwords = 4;
    int index = index_of_word(word, wordlist, numwords);

    _it_should("return the index in the wordlist of the word given", index == 2);

    return 0;
}

static char * index_of_word_01b() {
    char word[] = "asteroids";
    char *wordlist[4] = {"aahing\0\0\0\0\0", "aardvarik\0\0\0\0", "aardvarks\0\0\0", "aardwolf\0\0\0"}; 
    int numwords = 4;
    int index = index_of_word(word, wordlist, numwords);

    _it_should("return -1 if the word given is not in the wordlist", index  == -1);

    return 0;
}

static char * hex_chunk_01a() {
    char chunk[HEX_CHUNK_LENGTH+1];
    hex_chunk(chunk, 0);

    _it_should("return '0000' for integer 0'", strcmp(chunk, "0000") == 0);

    return 0;
}

static char * hex_chunk_01b() {
    char chunk[HEX_CHUNK_LENGTH+1];
    hex_chunk(chunk, 241);

    _it_should("return '00F1' for integer 241'", strcmp(chunk, "00F1") == 0);

    return 0;
}

static char * wordcount_01a() {
    char phrase[] = "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums";

    _it_should("return 16 for a 16 word phrase", wordcount(phrase) == 16);

    return 0;
}

static char * wordcount_01b() {
    char phrase[] = "  zyzzyvas\t flutings \n mushers octopuses bizones talkier evokers coagent "
                    "ringer      neutral antipode omnibus havening whistles mistitled  vacuums ";

    _it_should("return 16 for a 16 word phrase, ignoring wonky whitespace", wordcount(phrase) == 16);

    return 0;
}

static char * key_length_01a() {
    char phrase[] = "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums";

    _it_should("return 64 for a 16 word phrase", key_length(phrase) == 64);

    return 0;
}

static char * get_key_01a() {
    char wordlist_size = 4;
    char *wordlist[4] = {"aahing\0\0\0\0\0", "aardvark\0\0\0\0", "aardvarks\0\0\0", "elevententh"}; 
    char phrase[] = "aahing aardvark elevententh aardvarks aahing aardvarks aardvark elevententh aahing";
    char expected_key[] = "000000010003000200000002000100030000";
    char key[key_length(phrase)];
    char err_msg[ERR_MSG_LENGTH];
    get_key(key, phrase, wordlist, wordlist_size, err_msg);

    _it_should("return the right key for a given phrase", strcmp(key, expected_key) == 0);

    return 0;
}

static char * get_key_02a() {
    char wordlist_size = 4;
    char *wordlist[4] = {"aahing\0\0\0\0\0", "aardvark\0\0\0\0", "aardvarks\0\0\0", "aardwolf\0\0\0"}; 
    char phrase[] = "aahing aardvark aardfox aardvarks aahing aardvarks aardvark aardwolf aahing";
    char expected_error[] = "Could not find 'aardfox' in the wordlist!";
    char key[key_length(phrase)];
    char err_msg[ERR_MSG_LENGTH];
    get_key(key, phrase, wordlist, wordlist_size, err_msg);

    _it_should("return an error message when the phrase contains an unknown word", strcmp(err_msg, expected_error) == 0);

    return 0;
}

static char * get_key_02b() {
    char wordlist_size = 4;
    char *wordlist[4] = {"aahing\0\0\0\0\0", "aardvark\0\0\0\0", "aardvarks\0\0\0", "aardwolf\0\0\0"}; 
    char phrase[] = "ojo";
    char expected_error[] = "Could not find 'ojo' in the wordlist!";
    char key[key_length(phrase)];
    char err_msg[ERR_MSG_LENGTH];
    get_key(key, phrase, wordlist, wordlist_size, err_msg);

    _it_should("return an error message when the phrase is a short unknown word", strcmp(err_msg, expected_error) == 0);

    return 0;
}

static char * run_tests() {
    _run_test(is_hex_01a);
    _run_test(is_hex_01b);
    _run_test(is_hex_01c);
    _run_test(is_hex_02a);
    _run_test(is_hex_02b);
    _run_test(is_hex_02c);

    _run_test(is_hex_padded_01a);
    _run_test(is_hex_padded_02a);
    _run_test(is_hex_padded_02b);

    _run_test(get_word_01a);
    _run_test(get_word_01b);
    
    _run_test(normalized_hex_string_length_01a);
    _run_test(normalized_hex_string_length_01b);
    _run_test(normalized_hex_string_length_01c);
    _run_test(normalized_hex_string_length_01d);

    _run_test(normalize_hex_string_01a);
    _run_test(normalize_hex_string_01b);
    _run_test(normalize_hex_string_01c);
    _run_test(normalize_hex_string_01d);
    _run_test(normalize_hex_string_01e);
    
    _run_test(max_phrase_length_01a);
    _run_test(max_phrase_length_01b);
    
    _run_test(get_phrase_01a);

    _run_test(index_of_word_01a);
    _run_test(index_of_word_01b);

    _run_test(hex_chunk_01a);
    _run_test(hex_chunk_01b);

    _run_test(wordcount_01a);
    _run_test(wordcount_01b);

    _run_test(key_length_01a);

    _run_test(get_key_01a);
    _run_test(get_key_02a);
    _run_test(get_key_02b);

    return 0;
}

int main(int argc, char **argv) {
    char *result = run_tests();
    if (result != 0) {
        printf(KRED "**FAIL**: %s" KNRM "\n", result);

    } else {
        printf(KGRN "**PASSED ALL %d TESTS**" KNRM "\n", tests_run);
    }
}
