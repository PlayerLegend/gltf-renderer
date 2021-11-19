#ifndef FLAT_INCLUDES
#define FLAT_INCLUDES
#include "vec.h"
#include "vec3.h"
#endif

#define vec4(type) struct { type x; type y; type z; type w; }
#define vec4_add(a,b) { (a).x += (b).x; (a).y += (b).y; (a).z += (b).z; (a).w += (b).w; }
#define vec4_subtract(a,b) { (a).x -= (b).x; (a).y -= (b).y; (a).z -= (b).z; (a).w -= (b).w; }
#define vec4_scale(a,s) { (a).x *= s; (a).y *= s; (a).z *= s; (a).w *= s; }

typedef vec4(ivec) ivec4;
typedef vec4(fvec) fvec4;

void vec4_setup_rotation_quaternion (fvec4 * q, const fvec3 * axis);
void vec4_apply_rotation_quaternion (fvec4 * target, fvec4 * apply);
