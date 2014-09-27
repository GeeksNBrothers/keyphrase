clear
echo "Watching for changes..."

run_tests() {
    rm tests > /dev/null
    clear
    gcc -o tests tests.c funcs.c -std=c99 -Wall
    ./tests
}
run_tests

while true; do
    change=$(inotifywait -q -e close_write,moved_to,create {*.c,*.h})
    change=${change#./ * }
    run_tests
done
