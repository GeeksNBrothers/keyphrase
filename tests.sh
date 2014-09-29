run_tests() {
    echo -e "\nUser Acceptance Tests\n====================="
    ./ua_tests.sh

    echo -e "\nUnit Tests\n=========="
    ./unit_tests.sh
}

if [ "$1" == "--watch" ] || [ "$1" == "-w" ]; then
    while true; do
        clear
        run_tests
        change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    done
else
    run_tests
fi
