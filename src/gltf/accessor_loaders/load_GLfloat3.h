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
#include "load_indices.h"
#endif

bool load_GLfloat3 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env);
