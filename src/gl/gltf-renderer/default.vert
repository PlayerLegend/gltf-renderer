#version 330 core
layout (location = 0) in vec3 attribute_position;
layout (location = 1) in vec3 attribute_normal; // the color variable has attribute position 1

uniform mat4 uniform_model_rotation;
uniform mat4 uniform_model_translation;
uniform mat4 uniform_model_transform;

uniform mat4 uniform_view_rotation;
uniform mat4 uniform_view_translation;
uniform mat4 uniform_view_transform;

uniform mat4 uniform_mvp_rotation;
uniform mat4 uniform_mvp_transform;

uniform mat4 uniform_projection;

out vec3 result_color; // output a color to the fragment shader

void main()
{
    //gl_Position = uniform_mvp_transform * vec4(attribute_position, 1.0);
    gl_Position = uniform_projection * uniform_view_rotation * uniform_view_translation * uniform_model_rotation * uniform_model_translation * vec4(attribute_position, 1.0);
    //gl_Position = vec4(attribute_position, 1.0);
    
    vec3 transform_normal = vec3(uniform_model_rotation * uniform_view_rotation * vec4(attribute_normal, 1.0));
    //vec3 transform_normal = vec3(uniform_mvp_rotation * vec4(attribute_normal, 1.0));
    //vec3 transform_normal = vec3(vec4(attribute_normal, 1.0));
    
    result_color = dot(transform_normal, vec3(0,0,1)) * vec3(1,1,0);
}
