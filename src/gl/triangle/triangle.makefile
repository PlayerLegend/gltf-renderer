C_PROGRAMS += test/gl-triangle

test/gl-triangle: CFLAGS += `pkg-config --cflags glfw3`
test/gl-triangle: LDLIBS += `pkg-config --libs glfw3`
test/gl-triangle: LDLIBS += -ldl

test/gl-triangle: src/gl/triangle/triangle.test.o
test/gl-triangle: src/gl/triangle/glfw/simple-mouse-wrapper.o
test/gl-triangle: src/gl/triangle/load-shader.o
test/gl-triangle: src/convert/def.o
test/gl-triangle: src/window/alloc.o
test/gl-triangle: src/convert/fd.o
test/gl-triangle: src/log/log.o
test/gl-triangle: glad/src/glad.o

tests-gl: test/gl-triangle

test: tests-gl
