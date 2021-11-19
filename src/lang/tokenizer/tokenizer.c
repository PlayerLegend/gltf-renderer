#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../table/table.h"
#include "../../table/table-string.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../convert/def.h"
#include "../../log/log.h"
#include "../error/error.h"
#include "tokenizer.h"

static void get_token_size (size_t * size, bool * quote, window_unsigned_char * window)
{
    const char * end = window->region.char_cast.const_cast.begin;
    
    if (!range_is_empty (window->region))
    {
	if (!*quote && (*end == '(' || *end == ')'))
	{
	    *size = 1;
	    return;
	}
	
	while (end < window->region.char_cast.const_cast.end)
	{
	    if (*end == '"')
	    {
		*quote = !*quote;
	    }
	    else if (!*quote)
	    {
		if (isspace (*end) || *end == '(' || *end == ')')
		{
		    break;
		}
	    }
	    
	    end++;
	}
    }
    
    *size = range_index (end, window->region.char_cast.const_cast);
}

static void update_position (lang_token_position * position, char c)
{
    if (c == '\n')
    {
	position->line++;
	position->col = 0;
    }
    else
    {
	position->col++;	
    }
}

bool tokenizer_read (bool * error, lang_tokenizer_state * state, convert_interface * source)
{
    window_alloc (state->buffer, 64);

    while (true)
    {
	while (state->buffer.region.begin < state->buffer.region.end && isspace (*state->buffer.region.begin))
	{
	    update_position (&state->input_position, *state->buffer.region.begin);
	    state->buffer.region.begin++;
	}

	if (range_is_empty (state->buffer.region))
	{
	    window_rewrite (state->buffer);
	    
	    if (!convert_fill(error, &state->buffer, source))
	    {
		return false;
	    }
	}
	else
	{
	    break;
	}
    }

    assert (!range_is_empty (state->buffer.region));
    assert (!isspace (*state->buffer.region.begin));

    size_t size = 0;
    bool quoted = false;
    char c;

    state->token_position = state->input_position;
    
    while (true)
    {
	get_token_size (&size, &quoted, &state->buffer);

	assert (size <= (size_t)range_count(state->buffer.region));

	if (size)
	{
	    c = *state->buffer.region.begin;
	    
	    window_append_bytes((window_unsigned_char*) &state->token_contents, state->buffer.region.begin, size);
	    state->buffer.region.begin += size;
	    
	    if (size == 1 && !quoted && (c == '(' || c == ')'))
	    {
		assert (size == 1);
		break;
	    }
	}
	
	if (range_is_empty(state->buffer.region))
	{
	    window_rewrite (state->buffer);
	    
	    if (!convert_fill(error, &state->buffer, source))
	    {
		if (quoted)
		{
		    lang_log_fatal(state->token_position, "Unterminated quoted string");
		}
		
		break;
	    }
	}
	else
	{
	    break;
	}
    }

    char * token_char;

    for_range(token_char, state->token_contents.region)
    {
	update_position (&state->input_position, *token_char);
    }

    *window_push (state->token_contents) = '\0';
    state->token_contents.region.end--;
    
    return true;

fail:
    *error = true;
    return false;
}

void tokenizer_clear (lang_tokenizer_state * state)
{
    free (state->buffer.alloc.begin);
    free (state->token_contents.alloc.begin);
}
