#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "funcs.h"
#include "constants.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[1;37;41m"
#define KGRN  "\x1B[1;42;37m"

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
    char expected[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A0";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0x's and an odd number of characters", strcmp(buffer, expected) == 0);

    return 0;
}

static char * normalize_hex_string_01d() {
    char hex[] = "0XB300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A";
    char expected[] = "B300562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFFB17BBAF2A0";
    char buffer[normalized_hex_string_length(hex) + 1];
    normalize_hex_string(buffer, hex);

    _it_should("normalize strings with leading '0X's and an odd number of characters", strcmp(buffer, expected) == 0);

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
    
    _run_test(max_phrase_length_01a);
    _run_test(max_phrase_length_01b);
    
    _run_test(get_phrase_01a);

    return 0;
}

int main(int argc, char **argv) {
    char *result = run_tests();
    if (result != 0) {
        printf(KRED "**FAIL**: %s" KNRM "\n", result);

    } else {
        printf(KGRN "**PASSED %d TESTS**" KNRM "\n", tests_run);
    }
}
