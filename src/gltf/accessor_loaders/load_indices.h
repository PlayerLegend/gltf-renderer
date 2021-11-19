#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../range/def.h"
#include "../../window/def.h"
#include "GLfloat3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#endif

range_typedef(uint32_t, uint32_t);
window_typedef(uint32_t, uint32_t);

bool load_indices (window_uint32_t * load_indices, gltf_accessor_env * env);
