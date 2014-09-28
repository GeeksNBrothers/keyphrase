it_should() {
    if [ "$2" != "$3" ]
    then 
        echo -e '\E[37;44m'"\033[1;37;41m**FAIL**: it should $1 \n          ↪ Expected '$2' but got '$3' \n\033[0m"
    else
        echo -e '\E[37;44m'"\033[1;42;37m**PASS**: it should $1 \033[0m"
    fi
}

test_key_to_phrase() {
    actual=$(./portable/keyphrase 0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3)
    expected="zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums"
    it_should "return the correct passphrase for a 256-bit key" "$expected" "$actual"
}

test_phrase_to_key() {
    actual=$(./portable/keyphrase "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums")
    expected="0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3"
    it_should "return the correct 256-bit key for its passphrase" "$expected" "$actual"
}

test_short_phrase_to_key() {
    actual=$(./portable/keyphrase "abaser zyzzyvas zyzzyvas")
    expected="0x000FFFFFFFFF"
    it_should "return the correct short key for a three word passphrase" "$expected" "$actual"
}

test_invalid_word_in_phrase() {
    actual=$(./portable/keyphrase "abaser thisisnotawordinanydictionary zyzzyvas")
    expected="ERROR: Could not find 'thisisnotaw' in the wordlist!"
    it_should "return an error message when an invalid word is in the phrase passed in" "$expected" "$actual"
}

test_invalid_short_phrase() {
    actual=$(./portable/keyphrase "ojo")
    expected="ERROR: Could not find 'ojo' in the wordlist!"
    it_should "return an error message when a short invalid word is passed in" "$expected" "$actual"
}

run_tests() {
    make clean
    make portable
    clear
    test_key_to_phrase
    test_phrase_to_key
    test_short_phrase_to_key
    test_invalid_word_in_phrase
    test_invalid_short_phrase
}
run_tests

while true; do
    change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    change=${change#./ * }
    run_tests
done
