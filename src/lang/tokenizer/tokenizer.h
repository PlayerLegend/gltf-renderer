#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../convert/def.h"
#include "../error/error.h"
#endif

typedef struct {
    lang_token_position input_position;
    lang_token_position token_position;
    window_unsigned_char buffer;
    window_char token_contents;
}
    lang_tokenizer_state;

bool tokenizer_read (bool * error, lang_tokenizer_state * state, convert_interface * source);
void tokenizer_clear (lang_tokenizer_state * state);
