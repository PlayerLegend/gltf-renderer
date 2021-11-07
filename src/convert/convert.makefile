test/convert-cat: src/convert/test/cat.test.o
test/convert-cat: src/convert/fd.o
test/convert-cat: src/convert/def.o
test/convert-cat: src/window/alloc.o

test/convert-cat-load-all: src/convert/test/cat.test.o
test/convert-cat-load-all: src/convert/fd.o
test/convert-cat-load-all: src/convert/def.o
test/convert-cat-load-all: src/window/alloc.o

test/convert-getline: src/convert/test/getline.test.o
test/convert-getline: src/convert/fd.o
test/convert-getline: src/convert/def.o
test/convert-getline: src/window/alloc.o
test/convert-getline: src/convert/getline.o
test/convert-getline: src/log/log.o
test/convert-getline: src/range/string.o

test/run-convert-cat: src/convert/test/run-cat.sh
test/run-convert-cat-load-all: src/convert/test/run-cat-load-all.sh

C_PROGRAMS += test/convert-cat
C_PROGRAMS += test/convert-cat-load-all
C_PROGRAMS += test/convert-getline
SH_PROGRAMS += test/run-convert-cat
SH_PROGRAMS += test/run-convert-cat-load-all

RUN_TESTS += test/run-convert-cat
RUN_TESTS += test/run-convert-cat-load-all

convert-tests: test/convert-cat
convert-tests: test/convert-cat-load-all
convert-tests: test/run-convert-cat
convert-tests: test/run-convert-cat-load-all
convert-tests: test/convert-getline

tests: convert-tests
