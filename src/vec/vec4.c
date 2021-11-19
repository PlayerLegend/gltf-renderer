#include <math.h>
#define FLAT_INCLUDES
#include "vec.h"
#include "vec3.h"
#include "vec4.h"

void vec4_setup_rotation_quaternion (fvec4 * q, const fvec3 * axis)
{
    fvec length = (axis->x || axis->y || axis->z) ? fvec3_vlen (axis) : 1;
    
    fvec3 axis_normal =
	{
	    .x = axis->x / length,
	    .y = axis->y / length,
	    .z = axis->z / length
	};

    //float cos_angle_2 = cos(length / 2);
    float sin_angle_2 = sin(length / 2);

    q->x = sin_angle_2 * axis_normal.x;
    q->y = sin_angle_2 * axis_normal.y;
    q->z = sin_angle_2 * axis_normal.z;

    //q->w = cos_angle_2;
    q->w = 1;
}

void vec4_quaternion_multiply (fvec4 * result, const fvec4 * a, const fvec4 * b)
{
    result->w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
    result->x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
    result->y = a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x;
    result->z = a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w;
}

void vec4_apply_rotation_quaternion (fvec4 * target, fvec4 * apply)
{
    /*fvec4 apply_inverse =
	{
	    .w = target->w,
	    .x = -target->x,
	    .y = -target->y,
	    .z = -target->z,
	    };*/
    
    fvec4 tmp = *target;

    //vec4_quaternion_multiply(&tmp, apply, target);

    vec4_quaternion_multiply (target, apply, &tmp);
}
