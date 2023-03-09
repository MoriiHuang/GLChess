#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

layout(location = 1) in vec2 texCoord;
uniform mat4 u_MVP;
out vec2 TexCoords;
void main()
{
    TexCoords = texCoord;
    gl_Position = u_MVP*vec4(aPos, 1.0);

}

#shader fragment
#version 330 core
out vec4 color;

in vec2 TexCoords;
uniform vec4 u_Color;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture_2;
uniform sampler2D u_Chess_Black;
uniform sampler2D u_Chess_White;
uniform int flag;
uniform vec3 iResolution;
uniform float iTime;
void main()
{    
    vec2 uv =gl_FragCoord.xy/iResolution.xy;
    if (flag==0){
    vec4 texColor = texture(u_Texture, TexCoords);
    vec4 texColor2 = texture(u_Texture_2,TexCoords);
    if (texColor ==vec4(1)){
        color=u_Color;
    }
    else if (texColor2 ==vec4(1)){
        color=u_Color;
    }
    else{
    color =mix(texColor2,texColor,iTime);
    }
    }
    else if (flag==1){
        vec4 texColor = texture(u_Chess_Black,TexCoords);
        if (texColor ==vec4(1)){
        color=u_Color;
        }
        else{
        color =texColor;
        }
    }
    else if (flag==2){
        vec4 texColor = texture(u_Chess_White,TexCoords);
        if (texColor ==vec4(1)){
        color=u_Color;
        }
        else{
        color =texColor;
        }
    }
}