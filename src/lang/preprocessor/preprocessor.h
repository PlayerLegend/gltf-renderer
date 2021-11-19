#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../convert/def.h"
#include "../error/error.h"
#include "../tree/tree.h"
#endif

lang_tree_node * lang_preprocessor_load (const char * uri);
