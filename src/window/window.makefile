C_PROGRAMS += test/window
C_PROGRAMS += test/window-printf

test/window: src/window/test/window.test.o
test/window: src/window/alloc.o

test/window-printf: src/window/test/printf.test.o
test/window-printf: src/window/printf.o
test/window-printf: src/window/printf_append.o
test/window-printf: src/window/alloc.o

window-tests: test/window
window-tests: test/window-printf
tests: window-tests
