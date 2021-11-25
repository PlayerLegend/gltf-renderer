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

src/gltf/glb-toc.test.o: src/range/def.h src/keyargs/keyargs.h src/log/log.h
src/gltf/glb-toc.test.o: src/window/def.h src/convert/def.h src/convert/fd.h
src/gltf/glb-toc.test.o: src/gltf/convert.h
src/gltf/convert.o: src/range/def.h src/keyargs/keyargs.h src/window/def.h
src/gltf/convert.o: src/window/alloc.h src/convert/def.h
src/gltf/def.o: src/range/def.h
src/gltf/env.o: src/range/def.h src/gltf/def.h
src/gltf/accessor_loaders/load_GLfloat3.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/load_GLfloat3.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/vec/vec.h src/vec/vec3.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/range/def.h src/window/def.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/gltf/accessor_loaders/GLfloat3.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/keyargs/keyargs.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/json/def.h src/gltf/def.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/gltf/accessor_loaders/load_indices.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/gltf/accessor_loaders/load_GLfloat3.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/log/log.h src/window/alloc.h
src/gltf/accessor_loaders/load_indices.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/load_indices.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/load_indices.o: src/vec/vec.h src/vec/vec3.h
src/gltf/accessor_loaders/load_indices.o: src/range/def.h src/window/def.h
src/gltf/accessor_loaders/load_indices.o: src/gltf/accessor_loaders/GLfloat3.h
src/gltf/accessor_loaders/load_indices.o: src/keyargs/keyargs.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/vec/vec.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/vec/vec3.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/range/def.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/window/def.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/gltf/accessor_loaders/GLfloat3.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/keyargs/keyargs.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/gltf/accessor_loaders/load_indices.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/gltf/accessor_loaders/load_GLfloat3.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/log/log.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/convert/def.h
src/gltf/accessor_loaders/test/load_GLfloat3.test.o: src/convert/fd.h
src/gltf/accessor_loaders/load_GLfloat3.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/load_GLfloat3.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/vec/vec.h src/vec/vec3.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/range/def.h src/window/def.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/gltf/accessor_loaders/GLfloat3.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/keyargs/keyargs.h
src/gltf/accessor_loaders/load_GLfloat3.o: src/gltf/accessor_loaders/load_indices.h
src/gltf/accessor_loaders/GLfloat3.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/GLfloat3.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/GLfloat3.o: src/vec/vec.h src/vec/vec3.h
src/gltf/accessor_loaders/GLfloat3.o: src/range/def.h src/window/def.h
src/gltf/accessor_loaders/load_indices.o: glad/include/glad/glad.h
src/gltf/accessor_loaders/load_indices.o: glad/include/KHR/khrplatform.h
src/gltf/accessor_loaders/load_indices.o: src/vec/vec.h src/vec/vec3.h
src/gltf/accessor_loaders/load_indices.o: src/range/def.h src/window/def.h
src/gltf/accessor_loaders/load_indices.o: src/gltf/accessor_loaders/GLfloat3.h
src/gltf/accessor_loaders/load_indices.o: src/keyargs/keyargs.h
src/gltf/accessor_loaders/load_indices.o: src/json/def.h src/gltf/def.h
src/gltf/accessor_loaders/load_indices.o: src/gltf/accessor_loaders/load_indices.h
src/gltf/accessor_loaders/load_indices.o: src/window/alloc.h src/log/log.h
src/gltf/parse.o: src/range/def.h src/gltf/def.h
src/gltf/glb-json.util.o: src/range/def.h src/window/def.h src/window/alloc.h
src/gltf/glb-json.util.o: src/keyargs/keyargs.h src/log/log.h
src/gltf/glb-json.util.o: src/convert/def.h src/convert/fd.h
src/gltf/glb-json.util.o: src/gltf/convert.h
src/gltf/gltf.o: src/log/log.h src/range/def.h src/window/def.h
src/gltf/gltf.o: src/keyargs/keyargs.h src/json/def.h src/json/parse.h
src/gltf/gltf.o: src/json/traverse.h
src/gltf/convert.o: src/range/def.h src/window/def.h src/convert/def.h
src/gltf/convert.o: src/gltf/def.h
src/gltf/glb-info.util.o: src/range/def.h src/keyargs/keyargs.h src/log/log.h
src/gltf/glb-info.util.o: src/window/def.h src/convert/def.h
src/gltf/glb-info.util.o: src/gltf/convert.h src/convert/fd.h
src/gltf/env.o: src/range/def.h src/gltf/def.h src/gltf/env.h src/log/log.h
src/gltf/dump-vertices.util.o: src/range/def.h src/window/def.h
src/gltf/dump-vertices.util.o: src/window/alloc.h src/keyargs/keyargs.h
src/gltf/dump-vertices.util.o: src/log/log.h src/convert/def.h
src/gltf/dump-vertices.util.o: src/convert/fd.h src/gltf/convert.h
src/physics/ellipsoid/def.o: src/vec/vec.h src/vec/vec3.h
src/physics/ellipsoid/def.o: src/vec/vec.h src/vec/vec3.h src/gltf/def.h
src/physics/trace/line.o: src/vec/vec.h src/vec/vec3.h src/gltf/def.h
src/physics/trace/line.o: src/range/def.h src/physics/mesh/def.h
src/physics/trace/def.o: src/vec/vec.h src/vec/vec3.h
src/physics/trace/line.o: src/vec/vec.h src/vec/vec3.h src/gltf/def.h
src/physics/trace/line.o: src/range/def.h src/physics/mesh/def.h
src/physics/trace/line.o: src/physics/trace/line.h
src/physics/mesh/load.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/load.o: src/window/def.h src/vec/range_vec3.h
src/physics/mesh/load.o: src/convert/def.h src/gltf/def.h
src/physics/mesh/load.o: src/keyargs/keyargs.h src/gltf/convert.h
src/physics/mesh/build.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/build.o: src/vec/range_vec3.h src/window/def.h
src/physics/mesh/build.o: src/window/alloc.h src/gltf/def.h
src/physics/mesh/build.o: src/physics/mesh/build.h src/log/log.h
src/physics/mesh/subset.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/subset.o: src/window/def.h src/gltf/def.h
src/physics/mesh/subset.o: src/physics/mesh/subset.h src/window/alloc.h
src/physics/mesh/GLfloat3.o: glad/include/glad/glad.h
src/physics/mesh/GLfloat3.o: glad/include/KHR/khrplatform.h src/vec/vec.h
src/physics/mesh/GLfloat3.o: src/vec/vec3.h src/range/def.h src/window/def.h
src/physics/mesh/GLfloat3.o: src/gltf/accessor_loaders/GLfloat3.h
src/physics/mesh/GLfloat3.o: src/gltf/def.h
src/physics/mesh/build.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/build.o: src/vec/range_vec3.h src/gltf/def.h
src/physics/mesh/test/load.test.o: src/log/log.h src/debug/debug.h
src/physics/mesh/test/load.test.o: src/vec/vec.h src/vec/vec3.h
src/physics/mesh/test/load.test.o: src/range/def.h src/window/def.h
src/physics/mesh/test/load.test.o: src/vec/range_vec3.h
src/physics/mesh/test/load.test.o: src/physics/mesh/def.h
src/physics/mesh/test/load.test.o: src/physics/mesh/build.h
src/physics/mesh/test/load.test.o: glad/include/glad/glad.h
src/physics/mesh/test/load.test.o: glad/include/KHR/khrplatform.h
src/physics/mesh/test/load.test.o: src/keyargs/keyargs.h
src/physics/mesh/test/load.test.o: src/gltf/accessor_loaders/GLfloat3.h
src/physics/mesh/test/load.test.o: src/gltf/accessor_loaders/load_indices.h
src/physics/mesh/test/load.test.o: src/gltf/accessor_loaders/load_GLfloat3.h
src/physics/mesh/test/load.test.o: src/gltf/accessor_loaders/GLfloat3.h
src/physics/mesh/test/load.test.o: src/window/alloc.h src/uri/uri.h
src/physics/mesh/def.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/def.o: src/window/def.h
src/physics/mesh/load.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/load.o: src/window/def.h src/vec/range_vec3.h
src/physics/mesh/load.o: src/convert/def.h src/gltf/def.h
src/physics/mesh/subset.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/physics/mesh/subset.o: src/window/def.h src/gltf/def.h
src/physics/mesh/GLfloat3.o: glad/include/glad/glad.h
src/physics/mesh/GLfloat3.o: glad/include/KHR/khrplatform.h src/vec/vec.h
src/physics/mesh/GLfloat3.o: src/vec/vec3.h src/range/def.h src/window/def.h
src/physics/mesh/GLfloat3.o: src/gltf/accessor_loaders/GLfloat3.h
src/physics/mesh/GLfloat3.o: src/gltf/def.h
src/lang/tree/test/tree.test.o: src/range/def.h src/log/log.h
src/lang/tree/test/tree.test.o: src/window/def.h src/convert/def.h
src/lang/tree/test/tree.test.o: src/convert/fd.h src/lang/error/error.h
src/lang/tree/test/tree.test.o: src/lang/tree/tree.h
src/lang/tree/test/tree.test.o: src/lang/tokenizer/tokenizer.h
src/lang/tree/test/tree.test.o: src/immutable/immutable.h
src/lang/tree/tree.o: src/range/def.h src/window/def.h src/window/alloc.h
src/lang/tree/tree.o: src/convert/def.h src/lang/error/error.h
src/lang/tree/tree.o: src/lang/tree/tree.h src/log/log.h
src/lang/tree/tree.o: src/range/def.h src/window/def.h src/convert/def.h
src/lang/tree/tree.o: src/lang/error/error.h
src/lang/tokenizer/test/tokenizer.test.o: src/range/def.h src/window/def.h
src/lang/tokenizer/test/tokenizer.test.o: src/convert/def.h src/convert/fd.h
src/lang/tokenizer/test/tokenizer.test.o: src/lang/error/error.h
src/lang/tokenizer/test/tokenizer.test.o: src/lang/tokenizer/tokenizer.h
src/lang/tokenizer/test/tokenizer.test.o: src/log/log.h
src/lang/tokenizer/tokenizer.o: src/range/def.h src/window/def.h
src/lang/tokenizer/tokenizer.o: src/convert/def.h src/lang/error/error.h
src/lang/tokenizer/tokenizer.o: src/range/def.h src/table/table.h
src/lang/tokenizer/tokenizer.o: src/table/table-string.h src/window/def.h
src/lang/tokenizer/tokenizer.o: src/window/alloc.h src/convert/def.h
src/lang/tokenizer/tokenizer.o: src/log/log.h src/lang/error/error.h
src/lang/tokenizer/tokenizer.o: src/lang/tokenizer/tokenizer.h
src/lang/preprocessor/preprocessor.o: src/range/def.h src/window/def.h
src/lang/preprocessor/preprocessor.o: src/convert/def.h src/table/table.h
src/lang/preprocessor/preprocessor.o: src/lang/error/error.h
src/lang/preprocessor/preprocessor.o: src/lang/tree/tree.h
src/lang/preprocessor/preprocessor.o: src/lang/preprocessor/preprocessor.h
src/lang/preprocessor/preprocessor.o: src/table/table-string.h
src/lang/preprocessor/preprocessor.o: src/range/def.h src/window/def.h
src/lang/preprocessor/preprocessor.o: src/convert/def.h
src/lang/preprocessor/preprocessor.o: src/lang/error/error.h
src/lang/preprocessor/preprocessor.o: src/lang/tree/tree.h
src/lang/error/error.o: src/log/log.h
src/immutable/immutable.o: src/immutable/immutable.h src/range/def.h
src/immutable/immutable.o: src/table/table.h src/table/table-string.h
src/immutable/test/immutable.test.o: src/immutable/immutable.h
src/immutable/test/immutable.test.o: src/debug/debug.h
src/window/string.o: src/range/def.h src/gltf/def.h src/window/alloc.h
src/window/vprintf_append.o: src/range/def.h src/gltf/def.h
src/window/vprintf_append.o: src/window/vprintf.h src/window/alloc.h
src/window/vprintf.o: src/range/def.h src/gltf/def.h src/window/vprintf.h
src/window/vprintf.o: src/window/alloc.h
src/window/printf.o: src/range/def.h src/gltf/def.h
src/window/alloc.o: src/window/def.h
src/window/def.o: src/range/def.h
src/window/vprintf.o: src/range/def.h src/gltf/def.h
src/window/test/window.test.o: src/range/def.h src/physics/mesh/def.h
src/window/test/window.test.o: src/window/alloc.h src/log/log.h
src/window/test/window.test.o: src/debug/debug.h
src/window/test/printf.test.o: src/range/def.h src/physics/mesh/def.h
src/window/test/printf.test.o: src/window/printf.h src/debug/debug.h
src/window/string.o: src/range/def.h src/gltf/def.h src/window/alloc.h
src/window/string.o: src/window/string.h
src/window/printf_append.o: src/range/def.h src/gltf/def.h
src/window/printf_append.o: src/window/printf.h src/window/alloc.h
src/window/printf_append.o: src/window/vprintf.h
src/window/printf.o: src/range/def.h src/gltf/def.h src/window/printf.h
src/window/printf.o: src/window/alloc.h src/window/vprintf.h
src/window/alloc.o: src/window/string.h src/range/def.h src/gltf/def.h
src/window/alloc.o: src/window/alloc.h
src/convert/def.o: src/range/def.h src/window/def.h
src/convert/fd-bifurcated.o: src/window/def.h src/gltf/def.h
src/convert/getline.o: src/window/string.h src/range/def.h src/range/string.h
src/convert/getline.o: src/window/def.h src/window/alloc.h src/gltf/def.h
src/convert/getline.o: src/convert/getline.h src/log/log.h
src/convert/fd.o: src/range/def.h src/window/def.h src/gltf/def.h
src/convert/fd-bifurcated.o: src/window/def.h src/window/alloc.h
src/convert/fd-bifurcated.o: src/gltf/def.h src/convert/fd-bifurcated.h
src/convert/fd-bifurcated.o: src/log/log.h
src/convert/def.o: src/range/def.h src/window/def.h src/window/alloc.h
src/convert/def.o: src/gltf/def.h src/log/log.h
src/convert/getline.o: src/range/def.h src/window/def.h src/gltf/def.h
src/convert/fd.o: src/range/def.h src/window/def.h src/window/alloc.h
src/convert/fd.o: src/gltf/def.h src/convert/fd.h src/log/log.h
src/convert/test/getline.test.o: src/range/def.h src/window/def.h
src/convert/test/getline.test.o: src/window/alloc.h src/physics/mesh/def.h
src/convert/test/getline.test.o: src/convert/fd.h src/convert/getline.h
src/convert/test/getline.test.o: src/debug/debug.h src/log/log.h
src/convert/test/cat-load-all.test.o: src/window/def.h src/window/alloc.h
src/convert/test/cat-load-all.test.o: src/physics/mesh/def.h src/convert/fd.h
src/convert/test/cat-load-all.test.o: src/log/log.h
src/convert/test/cat.test.o: src/range/def.h src/window/def.h
src/convert/test/cat.test.o: src/window/alloc.h src/physics/mesh/def.h
src/convert/test/cat.test.o: src/convert/fd.h src/debug/debug.h src/log/log.h
src/vec/vec2.o: src/vec/vec.h
src/vec/mat4.o: src/window/string.h src/vec/vec.h src/vec/vec2.h
src/vec/mat4.o: src/vec/vec3.h src/vec/vec4.h src/keyargs/keyargs.h
src/vec/mat4.o: src/vec/mat4.h src/log/log.h
src/vec/vec4.o: src/vec/vec.h src/vec/vec3.h src/vec/vec4.h
src/vec/test/vec.test.o: src/vec/vec.h src/vec/vec2.h src/vec/vec3.h
src/vec/test/vec.test.o: src/debug/debug.h
src/vec/test/mat4.test.o: src/vec/vec.h src/vec/vec3.h src/keyargs/keyargs.h
src/vec/test/mat4.test.o: src/debug/debug.h src/vec/vec4.h src/vec/mat4.h
src/vec/test/mat4.test.o: src/log/log.h
src/vec/vec3.o: src/vec/vec.h
src/vec/view.o: src/vec/vec.h src/vec/vec3.h src/vec/vec4.h
src/vec/vec4.o: src/vec/vec.h src/vec/vec3.h
src/vec/vec3.o: src/vec/vec.h src/vec/vec3.h
src/vec/range_vec3.o: src/vec/vec.h src/vec/vec3.h src/range/def.h
src/vec/vec.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/vec/mat4.o: src/vec/vec.h src/vec/vec3.h src/vec/vec4.h
src/vec/mat4.o: src/keyargs/keyargs.h
src/vec/view.o: src/vec/vec.h src/vec/vec3.h src/vec/vec4.h src/vec/view.h
src/vec/view.o: src/keyargs/keyargs.h src/vec/mat4.h
src/libc/strdup/test/strdup.test.o: src/window/string.h
src/libc/strdup/test/strdup.test.o: src/libc/string-extensions.h
src/libc/strdup/test/strdup.test.o: src/log/log.h
src/libc/strdup/strdup.o: src/libc/string-extensions.h
src/log/test/log.test.o: src/log/log.h src/debug/debug.h
src/log/log.o: src/log/log.h
src/table/table.o: src/window/string.h
src/table/table-string.o: src/window/string.h src/range/def.h
src/table/table-string.o: src/table/table.h
src/table/table.o: src/window/string.h src/range/def.h src/table/table.h
src/table/table.o: src/table/table-string.h
src/table/test/table-string-map.test.o: src/window/string.h src/range/def.h
src/table/test/table-string-map.test.o: src/window/def.h src/table/table.h
src/table/test/table-string-map.test.o: src/table/table-string.h
src/table/test/table-string-map.test.o: src/log/log.h src/keyargs/keyargs.h
src/table/test/table-string-map.test.o: src/convert/def.h src/convert/fd.h
src/table/test/table-string-map.test.o: src/convert/getline.h
src/table/test/table-string-benchmark.test.o: src/window/string.h
src/table/test/table-string-benchmark.test.o: src/table/table.h
src/table/test/table-string-benchmark.test.o: src/table/table-string.h
src/table/test/table-string-benchmark.test.o: src/keyargs/keyargs.h
src/table/test/table-string-benchmark.test.o: src/log/log.h
src/table/table-int.o: src/window/string.h src/table/table.h
src/range/range_streq_string.o: src/window/string.h src/gltf/def.h
src/range/test/range.test.o: src/window/string.h src/physics/mesh/def.h
src/range/test/range.test.o: src/range/string.h src/debug/debug.h
src/range/range_atozd.o: src/gltf/def.h src/window/string.h
src/range/string.o: src/gltf/def.h src/window/string.h
src/range/range_strstr_string.o: src/window/string.h
src/gl/mesh/def.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/gl/mesh/def.o: src/range/def.h src/window/def.h src/vec/vec.h
src/gl/mesh/def.o: src/vec/vec3.h src/vec/vec4.h src/keyargs/keyargs.h
src/gl/mesh/def.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/gl/mesh/def.o: src/range/def.h src/window/def.h src/vec/vec.h
src/gl/mesh/def.o: src/vec/vec3.h src/vec/vec4.h src/keyargs/keyargs.h
src/gl/mesh/def.o: src/gltf/def.h src/window/alloc.h
src/gl/buffer/draw.o: src/window/string.h glad/include/glad/glad.h
src/gl/buffer/draw.o: glad/include/KHR/khrplatform.h src/range/def.h
src/gl/buffer/draw.o: src/window/def.h src/vec/vec.h src/vec/vec3.h
src/gl/buffer/draw.o: src/vec/vec4.h src/keyargs/keyargs.h src/vec/mat4.h
src/gl/buffer/draw.o: src/physics/mesh/def.h src/gltf/def.h
src/gl/buffer/draw.o: src/gl/buffer/draw.h
src/gl/buffer/internal/def.o: glad/include/glad/glad.h
src/gl/buffer/internal/def.o: glad/include/KHR/khrplatform.h src/range/def.h
src/gl/buffer/internal/def.o: src/window/def.h src/vec/vec.h src/vec/vec3.h
src/gl/buffer/internal/def.o: src/vec/vec4.h src/keyargs/keyargs.h
src/gl/buffer/internal/def.o: src/gl/mesh/def.h
src/gl/buffer/def.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/gl/buffer/def.o: src/range/def.h src/window/def.h src/vec/vec.h
src/gl/buffer/def.o: src/vec/vec3.h src/keyargs/keyargs.h
src/gl/buffer/def.o: src/physics/mesh/def.h
src/gl/buffer/loader.o: glad/include/glad/glad.h
src/gl/buffer/loader.o: glad/include/KHR/khrplatform.h src/range/def.h
src/gl/buffer/loader.o: src/window/def.h src/vec/vec.h src/vec/vec3.h
src/gl/buffer/loader.o: src/vec/vec4.h src/keyargs/keyargs.h
src/gl/buffer/loader.o: src/physics/mesh/def.h src/gltf/def.h
src/gl/buffer/draw.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/gl/buffer/draw.o: src/range/def.h src/window/def.h src/vec/vec.h
src/gl/buffer/draw.o: src/vec/vec3.h src/vec/vec4.h src/keyargs/keyargs.h
src/gl/buffer/draw.o: src/vec/mat4.h src/physics/mesh/def.h src/gltf/def.h
src/gl/buffer/loader.o: src/window/string.h glad/include/glad/glad.h
src/gl/buffer/loader.o: glad/include/KHR/khrplatform.h src/range/def.h
src/gl/buffer/loader.o: src/window/def.h src/window/alloc.h src/vec/vec.h
src/gl/buffer/loader.o: src/vec/vec3.h src/keyargs/keyargs.h src/json/def.h
src/gl/buffer/loader.o: src/gltf/def.h src/gltf/env.h src/convert/def.h
src/gl/buffer/loader.o: src/gltf/convert.h src/uri/uri.h src/log/log.h
src/gl/buffer/loader.o: src/gltf/accessor_loaders/GLfloat3.h
src/gl/buffer/loader.o: src/gltf/accessor_loaders/load_indices.h
src/gl/buffer/loader.o: src/gltf/accessor_loaders/load_GLfloat3.h
src/gl/buffer/loader.o: src/vec/vec4.h src/vec/mat4.h src/physics/mesh/def.h
src/gl/buffer/loader.o: src/gltf/def.h src/gl/buffer/loader.h
src/gl/gltf-renderer/gltf-renderer.test.o: glad/include/glad/glad.h
src/gl/gltf-renderer/gltf-renderer.test.o: glad/include/KHR/khrplatform.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/range/def.h src/window/def.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/vec/vec.h src/vec/vec2.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/vec/vec3.h src/vec/vec4.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/keyargs/keyargs.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/vec/mat4.h src/vec/view.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/physics/mesh/def.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/gl/buffer/def.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/gl/buffer/draw.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/gl/buffer/loader.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/log/log.h src/ui/init.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/ui/window.h src/ui/button-id.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/ui/input.h
src/gl/gltf-renderer/gltf-renderer.test.o: src/gl/triangle/load-shader.h
src/gl/triangle/load-shader.o: glad/include/glad/glad.h
src/gl/triangle/load-shader.o: glad/include/KHR/khrplatform.h
src/gl/triangle/load-shader.o: src/gl/triangle/load-shader.h src/vec/vec.h
src/gl/triangle/load-shader.o: src/vec/vec2.h
src/gl/triangle/load-shader.o: src/gl/triangle/glfw/simple-mouse-wrapper.h
src/gl/triangle/load-shader.o: src/range/def.h src/log/log.h src/window/def.h
src/gl/triangle/load-shader.o: src/convert/def.h src/convert/fd.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: glad/include/glad/glad.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: glad/include/KHR/khrplatform.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: src/vec/vec.h src/vec/vec2.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: src/gl/triangle/glfw/simple-mouse-wrapper.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: src/log/log.h
src/gl/triangle/glfw/simple-mouse-wrapper.o: src/vec/vec.h src/vec/vec2.h
src/gl/triangle/triangle.test.o: glad/include/glad/glad.h
src/gl/triangle/triangle.test.o: glad/include/KHR/khrplatform.h src/vec/vec.h
src/gl/triangle/triangle.test.o: src/vec/vec2.h src/vec/vec3.h
src/gl/triangle/triangle.test.o: src/gl/triangle/glfw/simple-mouse-wrapper.h
src/gl/triangle/triangle.test.o: src/log/log.h src/gl/triangle/load-shader.h
src/gl/triangle/triangle.test.o: src/range/def.h src/window/def.h
src/gl/triangle/triangle.test.o: src/window/alloc.h
src/gl/triangle/load-shader.o: glad/include/glad/glad.h
src/gl/triangle/load-shader.o: glad/include/KHR/khrplatform.h
src/list/test/list.test.o: src/list/list.h src/debug/debug.h
src/json/test/json.test.o: src/json/json.c src/window/string.h
src/json/test/json.test.o: src/range/def.h src/window/def.h
src/json/test/json.test.o: src/window/alloc.h src/keyargs/keyargs.h
src/json/test/json.test.o: src/gltf/def.h src/json/parse.h
src/json/test/json.test.o: src/json/traverse.h src/log/log.h src/list/list.h
src/json/test/json.test.o: src/libc/string-extensions.h src/table/table.h
src/json/test/json.test.o: src/table/table-string.h
src/json/parse.o: src/range/def.h src/keyargs/keyargs.h src/gltf/def.h
src/json/def.o: src/range/def.h src/keyargs/keyargs.h
src/json/traverse.o: src/range/def.h src/keyargs/keyargs.h src/gltf/def.h
src/json/json.o: src/window/string.h src/range/def.h src/window/def.h
src/json/json.o: src/window/alloc.h src/keyargs/keyargs.h src/gltf/def.h
src/json/json.o: src/json/parse.h src/json/traverse.h src/log/log.h
src/json/json.o: src/list/list.h src/libc/string-extensions.h
src/json/json.o: src/table/table.h src/table/table-string.h
src/uri/uri.o: src/range/def.h src/window/def.h src/convert/def.h
src/uri/path.o: src/range/def.h src/window/def.h
src/uri/uri.o: src/window/string.h src/range/def.h src/range/string.h
src/uri/uri.o: src/window/def.h src/window/alloc.h src/window/vprintf.h
src/uri/uri.o: src/window/printf.h src/window/string.h src/convert/def.h
src/uri/uri.o: src/convert/fd.h src/uri/uri.h src/log/log.h
src/uri/path.o: src/range/def.h src/window/def.h
src/ui/time.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/ui/window.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/ui/window.o: src/vec/vec.h src/vec/vec2.h src/ui/window.h
src/ui/window.o: src/ui/button-id.h src/ui/input.h src/log/log.h
src/ui/input.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/ui/input.o: src/vec/vec.h src/vec/vec2.h src/vec/vec3.h
src/ui/input.o: src/ui/button-id.h src/ui/window.h src/ui/input.h
src/ui/input.o: src/log/log.h
src/ui/init.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
src/ui/init.o: src/ui/window.h src/log/log.h
src/ui/input.o: src/vec/vec.h src/vec/vec2.h src/vec/vec3.h
src/ui/input.o: src/ui/button-id.h src/ui/window.h
