test/phys-mesh-load: LDLIBS += -lm
test/phys-mesh-load: src/physics/mesh/test/load.test.o
test/phys-mesh-load: src/gltf/gltf.o
test/phys-mesh-load: src/log/log.o
test/phys-mesh-load: src/json/json.o
test/phys-mesh-load: src/window/alloc.o
test/phys-mesh-load: src/gltf/accessor_loaders/load_indices.o
test/phys-mesh-load: src/gltf/accessor_loaders/load_GLfloat3.o
test/phys-mesh-load: src/physics/mesh/GLfloat3.o
test/phys-mesh-load: src/physics/mesh/build.o
test/phys-mesh-load: src/table/table.o
test/phys-mesh-load: src/uri/uri.o
test/phys-mesh-load: src/convert/def.o
test/phys-mesh-load: src/convert/fd.o
test/phys-mesh-load: src/window/vprintf.o
test/phys-mesh-load: src/window/vprintf_append.o
test/phys-mesh-load: src/range/range_streq_string.o
test/phys-mesh-load: src/range/string.o

phys-mesh-tests: test/phys-mesh-load
tests: phys-mesh-tests

C_PROGRAMS += test/phys-mesh-load
