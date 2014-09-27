clear
echo "Watching for changes..."

run_tests() {
    rm tests > /dev/null
    make tests
    clear
    ./tests
}
run_tests

while true; do
    change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    change=${change#./ * }
    run_tests
done
