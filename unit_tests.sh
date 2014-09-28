run_tests() {
    make -s clean
    make -s tests
    ./unit_tests
}

if [ "$1" == "--watch" ] || [ "$1" == "-w" ]; then
    while true; do
        clear
        run_tests
        inotifywait -q -e close_write {*.c,*.h}
    done
else
    run_tests
fi
