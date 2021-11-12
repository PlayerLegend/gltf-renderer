#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include <unistd.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "../mesh/def.h"
#include "def.h"
#endif

gl_buffer * gl_buffer_load (int count, const char ** uris);

