#include <string.h>
#include <math.h>
#define FLAT_INCLUDES
#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "../keyargs/keyargs.h"
#include "mat4.h"
#include "../log/log.h"

inline static fvec vlen (const fvec3 * a)
{
    return sqrt (a->x * a->x + a->y * a->y + a->z * a->z);
}

void apply_translation (mat4 input, fvec3 * tl)
{
#define tl_matrix_unwrap(row) input[12 + row] = input[0 + row]*tl->x + input[4 + row]*tl->y + input[8 + row]*tl->z + input[12 + row];
    tl_matrix_unwrap(0);
    tl_matrix_unwrap(1);
    tl_matrix_unwrap(2);
    tl_matrix_unwrap(3);
}
/*
typedef struct perspective_args perspective_args;
struct perspective_args {
    fvec fovy;
    fvec aspect;
    fvec near;
    fvec far;
};

typedef struct object_args object_args;
struct object_args {
    fvec3 origin;
    fvec3 rotation;
    };*/

void setup_rotation_quaternion (fvec4 * q, const fvec3 * axis)
{
    fvec length = (axis->x || axis->y || axis->z) ? vlen (axis) : 1;
    
    fvec3 axis_normal =
	{
	    .x = axis->x / length,
	    .y = axis->y / length,
	    .z = axis->z / length
	};

    float cos_angle_2 = cos(length / 2);
    float sin_angle_2 = sin(length / 2);

    q->x = sin_angle_2 * axis_normal.x;
    q->y = sin_angle_2 * axis_normal.y;
    q->z = sin_angle_2 * axis_normal.z;

    q->w = cos_angle_2;
}

keyargs_define(mat4_setup_rotation_matrix)
{
    fvec4 q;
    
    setup_rotation_quaternion (&q, &args.axis);
    
    // https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
    
    float s = 1 / (+ q.x * q.x
		   + q.y * q.y
		   + q.z * q.z
		   + q.w * q.w);

    float s2 = 2 * s;

    (*args.result)[0]  = 1 - s2 * (q.y * q.y + q.z * q.z);
    (*args.result)[1]  = s2 * (q.x * q.y + q.z * q.w);
    (*args.result)[2]  = s2 * (q.x * q.z - q.y * q.w);
    (*args.result)[3]  = 0;

    (*args.result)[4]  = s2 * (q.x * q.y - q.z * q.w);
    (*args.result)[5]  = 1 - s2 * (q.x * q.x + q.z * q.z);
    (*args.result)[6]  = s2 * (q.y * q.z + q.x * q.w);
    (*args.result)[7]  = 0;
    
    (*args.result)[8]  = s2 * (q.x * q.z + q.y * q.w);
    (*args.result)[9]  = s2 * (q.y * q.z - q.x * q.w);
    (*args.result)[10] = 1 - s2 * (q.x * q.x + q.y * q.y);
    (*args.result)[11] = 0;

    (*args.result)[12] = 0;
    (*args.result)[13] = 0;
    (*args.result)[14] = 0;
    (*args.result)[15] = 1;
}

keyargs_define(mat4_setup_projection_matrix)
{
    /* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml */

    float f = args.fovy / 2;
    f = cos (f) / sin (f);

    (*args.result)[0] = f / args.aspect;
    (*args.result)[1] = 0;
    (*args.result)[2] = 0;
    (*args.result)[3] = 0;

    (*args.result)[4] = 0;
    (*args.result)[5] = f;
    (*args.result)[6] = 0;
    (*args.result)[7] = 0;

    (*args.result)[8] = 0;
    (*args.result)[9] = 0;
    (*args.result)[10] = (args.far + args.near) / (args.near - args.far);
    (*args.result)[11] = -1;

    (*args.result)[12] = 0;
    (*args.result)[13] = 0;
    (*args.result)[14] = (2 * args.far * args.near) / (args.near - args.far);
    (*args.result)[15] = 0;
}

keyargs_define(mat4_setup_translation_matrix)
{
    (*args.result)[0] = 1;
    (*args.result)[1] = 0;
    (*args.result)[2] = 0;
    (*args.result)[3] = 0;

    (*args.result)[4] = 0;
    (*args.result)[5] = 1;
    (*args.result)[6] = 0;
    (*args.result)[7] = 0;

    (*args.result)[8] = 0;
    (*args.result)[9] = 0;
    (*args.result)[10] = 1;
    (*args.result)[11] = 0;

    (*args.result)[12] = args.translation.x;
    (*args.result)[13] = args.translation.y;
    (*args.result)[14] = args.translation.z;
    (*args.result)[15] = 1;
}

keyargs_define(mat4_setup_scale_matrix)
{
    (*args.result)[0] = args.scale.x;
    (*args.result)[1] = 0;
    (*args.result)[2] = 0;
    (*args.result)[3] = 0;

    (*args.result)[4] = 0;
    (*args.result)[5] = args.scale.y;
    (*args.result)[6] = 0;
    (*args.result)[7] = 0;

    (*args.result)[8] = 0;
    (*args.result)[9] = 0;
    (*args.result)[10] = args.scale.z;
    (*args.result)[11] = 0;

    (*args.result)[12] = 0;
    (*args.result)[13] = 0;
    (*args.result)[14] = 0;
    (*args.result)[15] = 1;
}

keyargs_define(mat4_setup_transform_matrix)
{
    mat4 a, b, c;

    mat4_setup_rotation_matrix(.result = &b, .axis = args.axis);
    mat4_setup_scale_matrix (.result = &c, .scale = args.scale);
    
    mat4_multiply (&a, &b, &c);

    mat4_setup_translation_matrix (.result = &c, .translation = args.translation);

    mat4_multiply (&b, &c, &a);

    mat4_setup_projection_matrix(.result = &a, .fovy = args.fovy, .aspect = 1, .near = 0.01, .far = 1);

    mat4_multiply (args.result, &a, &b);
}

void mat4_init_identity (mat4 mat)
{
    mat[0] = 1;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = 0;
    
    mat[4] = 0;
    mat[5] = 1;
    mat[6] = 0;
    mat[7] = 0;
    
    mat[8] = 0;
    mat[9] = 0;
    mat[10] = 1;
    mat[11] = 0;
    
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;
    
}

inline static float matrix_multiply_dot (int row_index, int col_index, const mat4 * a, const mat4 * b)
{
    const fvec * row = (*a) + row_index;
    const fvec * col = (*b) + 4 * col_index;

    /*log_normal ("(%d,%d) [%f, %f, %f, %f] * [%f, %f, %f, %f]",
		row_index,
		col_index,
		row[0],
		row[4],
		row[8],
		row[12],
		col[0],
		col[1],
		col[2],
		col[3]);*/
    
    return
	+ row[0] * col[0]
	+ row[4] * col[1]
	+ row[8] * col[2]
	+ row[12] * col[3];
}

void mat4_multiply (mat4 * result, const mat4 * a, const mat4 * b)
{
#define mat4_multiply_column(n)					\
    (*result)[0 + 4 * n] = matrix_multiply_dot(n, 0, a, b);	\
    (*result)[1 + 4 * n] = matrix_multiply_dot(n, 1, a, b);	\
    (*result)[2 + 4 * n] = matrix_multiply_dot(n, 2, a, b);	\
    (*result)[3 + 4 * n] = matrix_multiply_dot(n, 3, a, b);

    mat4_multiply_column(0);
    mat4_multiply_column(1);
    mat4_multiply_column(2);
    mat4_multiply_column(3);
}

void mat4_transpose (mat4 * a)
{
    float tmp;

    float * xp;
    float * yp;
    
    for (int x = 0; x < 4; x++)
    {
	for (int y = 0; y < x; y++)
	{
	    xp = (*a) + 4 * x + y;
	    yp = (*a) + 4 * y + x;

	    //log_debug("1 %f %f", *xp, *yp);
	    tmp = *xp;
	    *xp = *yp;
	    *yp = tmp;
	    //log_debug("2 %f %f", *xp, *yp);
	}
    }
}

/*void mat4_multiply (mat4 * out, const mat4 * a, const mat4 * b)
  {
  int row, col;

  for (row = 0; row < 4; row += 1)
  {
  for (col = 0; col < 16; col += 4)
  {
  (*out)[col + row]
  = (*a)[row] * (*b)[col]
  + (*a)[row + 4] * (*b)[col + 1]
  + (*a)[row + 8] * (*b)[col + 2]
  + (*a)[row + 12] * (*b)[col + 3];
  }
  }
  }
*/

void mat4_setup_identity_matrix (mat4 * a)
{
    (*a)[0] = 1;
    (*a)[1] = 0;
    (*a)[2] = 0;
    (*a)[3] = 0;
    
    (*a)[4] = 0;
    (*a)[5] = 1;
    (*a)[6] = 0;
    (*a)[7] = 0;
    
    (*a)[8] = 0;
    (*a)[9] = 0;
    (*a)[10] = 1;
    (*a)[11] = 0;
    
    (*a)[12] = 0;
    (*a)[13] = 0;
    (*a)[14] = 0;
    (*a)[15] = 1;
}
