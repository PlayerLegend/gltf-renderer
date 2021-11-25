#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/range_vec3.h"
#include "../../convert/def.h"
#include "def.h"
#endif

void phys_tri_load (window_phys_mesh_tri * result, convert_interface * interface);
