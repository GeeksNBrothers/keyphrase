test_key_to_phrase() {
    actual=$(./keyphrase 0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3)
    expected="zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums"

    if [ "$actual" != "$expected" ]
    then 
        echo -e '\E[37;44m'"\033[1;37;41m**FAIL**: Unexpected phrase output!\n          ↪ Expected '$expected' but got '$actual'\n\033[0m"
    else
        echo -e '\E[37;44m'"\033[1;42;37m**PASS**: Phrase output is as expected\033[0m"
    fi
}

test_phrase_to_key() {
    actual=$(./keyphrase "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums")
    expected="0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3"

    if [ "$actual" != "$expected" ]
    then 
        echo -e '\E[37;44m'"\033[1;37;41m**FAIL**: Unexpected key output!\n          ↪ Expected '$expected' but got '$actual'\n\033[0m"
    else
        echo -e '\E[37;44m'"\033[1;42;37m**PASS**: Key output is as expected\033[0m"
    fi
}
test_short_phrase_to_key() {
    actual=$(./keyphrase "abaser zyzzyvas zyzzyvas")
    expected="0xFFFFFFFFF"

    if [ "$actual" != "$expected" ]
    then 
        echo -e '\E[37;44m'"\033[1;37;41m**FAIL**: Unexpected key output!\n          ↪ Expected '$expected' but got '$actual'\n\033[0m"
    else
        echo -e '\E[37;44m'"\033[1;42;37m**PASS**: Key output for short phrase is as expected\033[0m"
    fi
}

run_tests() {
    rm keyphrase > /dev/null
    clear
    gcc -o keyphrase keyphrase.c funcs.c -std=c99 -Wall
    test_key_to_phrase
    test_phrase_to_key
    test_short_phrase_to_key
}
run_tests

while true; do
    change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    change=${change#./ * }
    run_tests
done
