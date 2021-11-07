#ifndef FLAT_INCLUDES
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../keyargs/keyargs.h"
#include "../json/json.h"
#include "../window/def.h"
#include "../convert/def.h"
#include "gltf.h"
#endif

bool glb_toc_load_from_interface (glb_toc * toc, convert_interface * interface);
