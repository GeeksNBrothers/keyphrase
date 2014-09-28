run_tests() {
    rm tests > /dev/null
    make -s clean
    make -s tests
    ./tests
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
