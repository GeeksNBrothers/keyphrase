run_tests() {
    make -s clean
    make -s tests
    result=$(./unit_tests)
    retval=$?

    command -v notify-send >/dev/null 2>&1 
    if [ "$?" -eq 0 ] && [ "$1" -eq 1 ]; then
        notify_result=$(echo $result | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g")
        notify-send "Unit Tests" "$notify_result"
    fi

    echo "$result"
    return $retval
}

watch=0
notify_send=0
while test $# -gt 0
do
    case "$1" in
        --watch) watch=1
            ;;
        -w) watch=1
            ;;
        --notify-send) notify_send=1
            ;;
        -ns) notify_send=1
            ;;
    esac
    shift
done

if [ "$watch" -eq 1 ]; then
    while true; do
        clear
        run_tests $notify_send
        inotifywait -q -e close_write {*.c,*.h}
    done
else
    run_tests $notify_send
    exit $?
fi
