LD = $(CC)
PREFIX ?= /usr/local
DESTDIR ?= $(PREFIX)
CFLAGS += -std=c99
PATH := $(CURDIR)/bin/:$(CURDIR)/sbin/:$(PATH)
BUILD_ENV ?= release

export PATH

all: utils

.PHONY: test bin install

include env/$(BUILD_ENV).makefile

SUB_MAKEFILES != find src -type f -name '*.makefile'
include $(SUB_MAKEFILES)

#debug tests test: CFLAGS += -ggdb -Wall -Werror
#utils benchmarks: CFLAGS += -DNDEBUG -O2
#benchmarks: CFLAGS += -O2

#utils debug: $(UTILS_C) $(UTILS_SH)
#debug: $(TESTS_C) $(TESTS_SH)
#benchmarks: $(BENCHMARKS_C)

#$(UTILS_C) $(TESTS_C): LDLIBS += $(CFLAGS)

$(C_PROGRAMS):
	@mkdir -p $(@D)
	$(LD) -o $@ $^ $> $(LDLIBS)

$(SH_PROGRAMS):
	@mkdir -p $(@D)
	cp $< $@
	chmod +x $@

utils:
tests:
run-tests:
	make depend
	make clean
	make BUILD_ENV=debug tests utils
	sh run-tests.sh $(RUN_TESTS)
	make clean

clean-fast:
	rm -rf test bin sbin init `find src -name '*.o'`

clean: clean-fast
	rm -rf external boot

depend: clean
	makedepend -Y `find src -name '*.c*' -or -name '*.h*'`

install:
	cp -v bin/* $(DESTDIR)/bin/
#	printf '%s\n' $(UTILS_C) $(UTILS_SH) | cpio -pudm $(DESTDIR)/

install-user:
	make install DESTDIR=$(HOME)/.local

# DO NOT DELETE

src/gltf/glb-toc.test.o: src/range/def.h src/keyargs/keyargs.h
src/gltf/glb-toc.test.o: src/json/json.h src/gltf/gltf.h src/log/log.h
src/gltf/glb-toc.test.o: src/window/def.h src/convert/def.h src/convert/fd.h
src/gltf/glb-toc.test.o: src/gltf/convert.h
src/gltf/gltf.o: src/range/def.h src/keyargs/keyargs.h src/json/json.h
src/gltf/convert.o: src/range/def.h src/keyargs/keyargs.h src/json/json.h
src/gltf/convert.o: src/window/def.h src/window/alloc.h src/convert/def.h
src/gltf/convert.o: src/gltf/gltf.h
src/gltf/glb-json.util.o: src/range/def.h src/window/def.h src/window/alloc.h
src/gltf/glb-json.util.o: src/keyargs/keyargs.h src/json/json.h
src/gltf/glb-json.util.o: src/gltf/gltf.h src/log/log.h src/convert/def.h
src/gltf/glb-json.util.o: src/convert/fd.h src/gltf/convert.h
src/gltf/gltf.o: src/log/log.h src/range/def.h src/window/def.h
src/gltf/gltf.o: src/keyargs/keyargs.h src/json/json.h src/gltf/gltf.h
src/gltf/convert.o: src/range/def.h src/keyargs/keyargs.h src/json/json.h
src/gltf/convert.o: src/window/def.h src/convert/def.h src/gltf/gltf.h
src/gltf/glb-info.util.o: src/range/def.h src/keyargs/keyargs.h
src/gltf/glb-info.util.o: src/json/json.h src/gltf/gltf.h src/log/log.h
src/gltf/glb-info.util.o: src/window/def.h src/convert/def.h
src/gltf/glb-info.util.o: src/gltf/convert.h src/convert/fd.h
src/window/printf.o: src/window/def.h
src/window/alloc.o: src/window/def.h
src/window/test/window.test.o: src/range/def.h src/window/def.h
src/window/test/window.test.o: src/window/alloc.h src/log/log.h
src/window/test/window.test.o: src/debug/debug.h
src/window/test/printf.test.o: src/range/def.h src/window/def.h
src/window/test/printf.test.o: src/window/printf.h src/debug/debug.h
src/window/printf_append.o: src/range/def.h src/window/def.h
src/window/printf_append.o: src/window/printf.h src/window/alloc.h
src/window/printf.o: src/range/def.h src/window/def.h src/window/printf.h
src/window/printf.o: src/window/alloc.h
src/window/alloc.o: src/range/def.h src/window/def.h src/window/alloc.h
src/convert/def.o: src/range/def.h src/window/def.h
src/convert/fd-bifurcated.o: src/window/def.h src/window/def.h
src/convert/getline.o: src/range/def.h src/range/string.h src/window/def.h
src/convert/getline.o: src/window/alloc.h src/window/def.h
src/convert/getline.o: src/convert/getline.h src/log/log.h
src/convert/fd.o: src/range/def.h src/window/def.h src/window/def.h
src/convert/fd-bifurcated.o: src/window/def.h src/window/alloc.h
src/convert/fd-bifurcated.o: src/window/def.h src/convert/fd-bifurcated.h
src/convert/fd-bifurcated.o: src/log/log.h
src/convert/def.o: src/range/def.h src/window/def.h src/window/alloc.h
src/convert/def.o: src/window/def.h src/log/log.h
src/convert/getline.o: src/range/def.h src/window/def.h src/window/def.h
src/convert/fd.o: src/range/def.h src/window/def.h src/window/alloc.h
src/convert/fd.o: src/window/def.h src/convert/fd.h src/log/log.h
src/convert/test/getline.test.o: src/range/def.h src/window/def.h
src/convert/test/getline.test.o: src/window/alloc.h src/window/def.h
src/convert/test/getline.test.o: src/convert/fd.h src/convert/getline.h
src/convert/test/getline.test.o: src/debug/debug.h src/log/log.h
src/convert/test/cat-load-all.test.o: src/window/def.h src/window/alloc.h
src/convert/test/cat-load-all.test.o: src/window/def.h src/convert/fd.h
src/convert/test/cat-load-all.test.o: src/log/log.h
src/convert/test/cat.test.o: src/range/def.h src/window/def.h
src/convert/test/cat.test.o: src/window/alloc.h src/window/def.h
src/convert/test/cat.test.o: src/convert/fd.h src/debug/debug.h src/log/log.h
src/libc/strdup/test/strdup.test.o: src/libc/string-extensions.h
src/libc/strdup/test/strdup.test.o: src/log/log.h
src/libc/strdup/strdup.o: src/libc/string-extensions.h
src/log/test/log.test.o: src/log/log.h src/debug/debug.h
src/log/log.o: src/log/log.h
src/table/table-string.o: src/table/table.h
src/table/table.o: src/range/def.h src/table/table.h src/table/table-string.h
src/table/test/table-string-map.test.o: src/range/def.h src/window/def.h
src/table/test/table-string-map.test.o: src/table/table.h
src/table/test/table-string-map.test.o: src/table/table-string.h
src/table/test/table-string-map.test.o: src/log/log.h src/keyargs/keyargs.h
src/table/test/table-string-map.test.o: src/convert/def.h src/convert/fd.h
src/table/test/table-string-map.test.o: src/convert/getline.h
src/table/test/table-string-benchmark.test.o: src/table/table.h
src/table/test/table-string-benchmark.test.o: src/table/table-string.h
src/table/test/table-string-benchmark.test.o: src/keyargs/keyargs.h
src/table/test/table-string-benchmark.test.o: src/log/log.h
src/table/table-int.o: src/table/table.h
src/range/range_streq_string.o: src/range/string.h
src/range/test/range.test.o: src/range/string.h src/window/def.h
src/range/test/range.test.o: src/range/string.h src/debug/debug.h
src/range/range_atozd.o: src/window/def.h src/range/string.h
src/range/string.o: src/window/def.h src/range/string.h
src/range/range_strstr_string.o: src/range/string.h
src/list/test/list.test.o: src/list/list.h src/debug/debug.h
src/json/json.o: src/range/def.h src/keyargs/keyargs.h
src/json/test/json.test.o: src/json/json.c src/range/string.h src/range/def.h
src/json/test/json.test.o: src/window/def.h src/window/alloc.h
src/json/test/json.test.o: src/keyargs/keyargs.h src/json/json.h
src/json/test/json.test.o: src/log/log.h src/list/list.h
src/json/test/json.test.o: src/libc/string-extensions.h src/table/table.h
src/json/test/json.test.o: src/table/table-string.h
src/json/json.o: src/range/string.h src/range/def.h src/window/def.h
src/json/json.o: src/window/alloc.h src/keyargs/keyargs.h src/json/json.h
src/json/json.o: src/log/log.h src/list/list.h src/libc/string-extensions.h
src/json/json.o: src/table/table.h src/table/table-string.h
