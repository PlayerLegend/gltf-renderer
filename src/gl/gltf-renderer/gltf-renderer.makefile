test/load_GLfloat3: src/gltf/accessor_loaders/test/load_GLfloat3.test.o
test/load_GLfloat3: src/gltf/accessor_loaders/load_GLfloat3.o
test/load_GLfloat3: src/gltf/accessor_loaders/load_indices.o
test/load_GLfloat3: src/window/alloc.o
test/load_GLfloat3: src/convert/def.o
test/load_GLfloat3: src/convert/fd.o
test/load_GLfloat3: src/log/log.o
test/load_GLfloat3: src/gltf/gltf.o
test/load_GLfloat3: src/json/json.o
test/load_GLfloat3: src/table/table.o

test/gltf-renderer: LDLIBS += -ldl
test/gltf-renderer: LDLIBS += -lglfw
test/gltf-renderer: LDLIBS += -lm
test/gltf-renderer: glad/src/glad.o
test/gltf-renderer: src/convert/def.o
test/gltf-renderer: src/convert/fd.o
test/gltf-renderer: src/gltf/accessor_loaders/load_GLfloat3.o
test/gltf-renderer: src/gltf/accessor_loaders/load_indices.o
test/gltf-renderer: src/gl/buffer/loader.o
test/gltf-renderer: src/gl/buffer/draw.o
test/gltf-renderer: src/gl/gltf-renderer/gltf-renderer.test.o
test/gltf-renderer: src/gl/mesh/def.o
test/gltf-renderer: src/gl/triangle/glfw/simple-mouse-wrapper.o
test/gltf-renderer: src/gl/triangle/load-shader.o
test/gltf-renderer: src/gltf/gltf.o
test/gltf-renderer: src/json/json.o
test/gltf-renderer: src/log/log.o
test/gltf-renderer: src/table/table.o
test/gltf-renderer: src/uri/uri.o
test/gltf-renderer: src/vec/vec3.o
test/gltf-renderer: src/vec/vec4.o
test/gltf-renderer: src/vec/mat4.o
test/gltf-renderer: src/vec/view.o
test/gltf-renderer: src/window/alloc.o
test/gltf-renderer: src/window/vprintf.o
test/gltf-renderer: src/window/vprintf_append.o
test/gltf-renderer: src/range/range_streq_string.o
test/gltf-renderer: src/range/string.o

gltf-renderer-tests: test/load_GLfloat3
tests: gltf-renderer-tests

C_PROGRAMS += test/load_GLfloat3
C_PROGRAMS += test/gltf-renderer
