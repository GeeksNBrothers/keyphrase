run_tests() {
    echo -e "\nUser Acceptance Tests\n====================="
    ./ua_tests.sh
    ua_tests=$?

    echo -e "\nUnit Tests\n=========="
    ./unit_tests.sh
    unit_tests=$?

    return $(($unit_tests || $ua_tests))
}

if [ "$1" == "--watch" ] || [ "$1" == "-w" ]; then
    while true; do
        clear
        run_tests
        change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    done
else
    run_tests
    exit $?
fi
