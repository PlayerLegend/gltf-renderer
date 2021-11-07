#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../keyargs/keyargs.h"
#include "../json/json.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "../convert/def.h"
#include "gltf.h"

bool glb_toc_load_from_interface (glb_toc * toc, convert_interface * interface)
{
    bool error = false;

    window_unsigned_char contents = {0};
    
    if (!convert_load_all (&error, &contents, interface))
    {
	return false;
    }

    if (!glb_toc_load_memory (toc, contents.region.begin, range_count(contents.region)))
    {
	free (contents.alloc.begin);
	return false;
    }
    else
    {
	return true;
    }
}
