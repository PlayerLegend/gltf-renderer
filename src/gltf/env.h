#ifndef FLAT_INCLUDES
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#endif

bool gltf_accessor_env_setup (gltf_accessor_env * env, const glb_toc * toc, gltf_accessor * import_accessor);
