run_tests() {
    echo
    echo "User Acceptance Tests"
    echo "====================="
    ./ua_tests.sh
    echo

    echo "Unit Tests"
    echo "=========="
    ./unit_tests.sh
    echo
}

if [ "$1" == "--watch" ] || [ "$1" == "-w" ]; then
    while true; do
        clear
        run_tests
        change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
        change=${change#./ * }
    done
else
    run_tests
fi
