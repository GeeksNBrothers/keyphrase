// Thanks to JeraTech for this minimalist TDD code,
// which I've modified to resemble AngularJS's a bit more.
// http://www.jera.com/techinfo/jtns/jtn002.html

int tests_run = 0;
#define _it_should(message, test) do { if (!(test)) return message; } while (0)
#define _run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
