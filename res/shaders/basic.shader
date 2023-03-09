#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

out vec3 skyboxCoord;
uniform mat4 u_MVP;
uniform mat4 u_View;
uniform mat4 u_Projection;
void main()
{
    
    gl_Position =u_Projection*u_View*u_MVP*vec4(position, 1.0f);
   
    v_TexCoord = texCoord;
    skyboxCoord= position;
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;
in vec3 skyboxCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;
uniform samplerCube skybox;
uniform int flag;
void main()
{   
    
    if (flag==0){
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (texColor ==vec4(1)){
        color=u_Color;
    }
    else{
    color =texColor;
    }
    }
    else if (flag==1){
        vec4 texColor = texture(u_Texture1, v_TexCoord);
        if (texColor ==vec4(1)){
        color=u_Color;
        }
        else{
        color =texColor;
    }

    }
    else if (flag==2){
        vec4 texColor = texture(skybox, skyboxCoord);
        if (texColor ==vec4(1)){
        color=u_Color;
        }
        else{
        color =texColor;
    }

    }
}