run_tests() {
    make -s clean
    make -s tests
    result=$(./unit_tests)

    command -v notify-send >/dev/null 2>&1 
    if [ "$?" -eq 0 ]; then
        notify_result=$(echo $result | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g")
        notify-send "Unit Tests" "$notify_result"
    fi

    echo "$result"
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
