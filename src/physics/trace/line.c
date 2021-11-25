#include <stdbool.h>
#include <stddef.h>
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "def.h"
#include "../../range/def.h"
#include "../mesh/def.h"
#include "line.h"

void phys_trace_line_tri (phys_trace_result * result, const phys_mesh_tri * tri, const phys_trace_arg * arg)
{
    // Moller-Trumbore algorithm - backface culling version

    fvec3 edge1 = vec3_subtract_init (tri->position[1], tri->position[0]);
    fvec3 edge2 = vec3_subtract_init (tri->position[2], tri->position[0]);
    fvec3 p = vec3_cross(arg->direction, edge2);
    fvec determinate = vec3_dot (edge1, p);

    if (determinate < FVEC_EPSILON)
    {
	goto miss;
    }
    
    fvec3 tvec = vec3_subtract_init(arg->origin, tri->position[0]);

    fvec u = vec3_dot (tvec, p);

    if (u < 0.0 || u > determinate)
    {
	goto miss;
    }

    fvec3 q = vec3_cross (tvec, edge1);

    fvec v = vec3_dot (arg->direction, q);

    if (v < 0.0 || u + v > determinate)
    {
	goto miss;
    }

    fvec t = vec3_dot (edge2, q) / determinate;
        
    *result = (phys_trace_result)
    {
	.is_hit = true,
	.distance = t,
	.hit_normal = tri->normal,
	.end = vec3_line_point_init(arg->origin, arg->direction, t),
    };
    
    return;

miss:
    *result = (phys_trace_result)
	{
	    .is_hit = false,
	    .distance = arg->distance,
	};
    return;
}

void phys_trace_line_mesh_subset (phys_trace_result * result, const range_const_phys_mesh_tri_p * set, const phys_trace_arg * arg)
{
    *result = (phys_trace_result)
    {
	.is_hit = false,
	.distance = arg->distance,
    };
    
    const phys_mesh_tri ** tri;
    phys_trace_result tri_result;

    for_range (tri, *set)
    {
	phys_trace_line_tri(&tri_result, *tri, arg);

	if (!tri_result.is_hit)
	{
	    continue;
	}

	if (result->distance > tri_result.distance)
	{
	    *result = tri_result;
	}
    }
}
