C_PROGRAMS += test/range
C_PROGRAMS += test/buffer
RUN_TESTS += test/range

range-tests: test/range

test/range: src/range/string.o
test/range: src/range/range_atozd.o
test/range: src/range/test/range.test.o

tests: range-tests
