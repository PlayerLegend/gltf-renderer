#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../keyargs/keyargs.h"
#endif

typedef struct json_value json_value;

range_typedef(json_value, json_value);

typedef range_json_value json_array;

typedef struct json_object json_object;
typedef enum json_type json_type;

enum json_type {
    JSON_NULL,
    JSON_NUMBER,
    JSON_TRUE,
    JSON_FALSE,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT,
    JSON_BADTYPE,
};

struct json_value {
    json_type type;
    union {
	double number;
	char * string;
	json_array array;
	json_object * object;
    };
};

json_value * json_parse (const char * begin, const char * end);
json_value * json_lookup (const json_object * object, const char * key);
void json_free (json_value * value);
const char * json_type_name(json_type type);

#define json_get_number(...) keyargs_call(json_get_number, __VA_ARGS__)
keyargs_declare(double, json_get_number, 
		const json_object * parent;
		const char * key;
		bool * success;
		bool optional;
		double default_value;);

#define json_get_bool(...) keyargs_call(json_get_bool, __VA_ARGS__)
keyargs_declare(double, json_get_bool, 
		const json_object * parent;
		const char * key;
		bool * success;
		bool optional;
		bool default_value;);

#define json_get_string(...) keyargs_call(json_get_string, __VA_ARGS__)
keyargs_declare(const char*, json_get_string,
		const json_object * parent;
		const char * key;
		bool * success;
		bool optional;
		const char * default_value;);

#define json_get_array(...) keyargs_call(json_get_array, __VA_ARGS__)
keyargs_declare(const json_array*, json_get_array,
		const json_object * parent;
		const char * key;
		bool optional;
		bool * success;);

#define json_get_object(...) keyargs_call(json_get_object, __VA_ARGS__)
keyargs_declare(const json_object*, json_get_object,
		const json_object * parent;
		const char * key;
		bool * success;
		bool optional;);
	        
