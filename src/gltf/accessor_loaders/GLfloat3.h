#ifndef FLAT_INCLUDES
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../range/def.h"
#include "../../window/def.h"
#endif

typedef vec3(GLfloat) GLfloat3;
typedef vec3(GLshort) GLshort3;
typedef vec3(GLushort) GLushort3;
    
range_typedef(GLfloat3, GLfloat3);
window_typedef(GLfloat3, GLfloat3);

range_typedef(GLshort3, GLshort3);
window_typedef(GLshort3, GLshort3);

range_typedef(GLushort3, GLushort3);
window_typedef(GLushort3, GLushort3);

range_typedef(GLuint, GLuint);
window_typedef(GLuint, GLuint);
