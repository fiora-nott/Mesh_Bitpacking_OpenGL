#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float lightValue;

out vec2 v_TexCoord;
out float v_lightValue;
//out vec4 v_WorldPosition;

uniform mat4 u_MVP; //model-view-projection matrix

void main() {
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
    v_lightValue = lightValue;
    //v_WorldPosition = position;
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_lightValue;
//in vec4 v_WorldPosition;

uniform vec4 u_Albedo_Color;
uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (texColor.a == 0)
        discard;
    //color = vec4(0.35, 0.7, 0.2, 1.0) * u_Albedo_Color;
    /*
    vec4 modAlbedo = vec4(
        mod(u_Albedo_Color.x + v_WorldPosition.x/10, 1.0),
        mod(u_Albedo_Color.y + v_WorldPosition.y / 10, 1.0),
        mod(u_Albedo_Color.z + v_WorldPosition.z / 10, 1.0),
        1.0);*/
    //color = texColor * modAlbedo;
    color = (texColor * u_Albedo_Color) * v_lightValue;

    /*
    //ADD A BORDER TO EVERY TEXTURE
    float borderWidth = 0.04;
    if (v_TexCoord.x < borderWidth || v_TexCoord.y < borderWidth ||
        v_TexCoord.x > 1 - borderWidth || v_TexCoord.y > 1 - borderWidth)
    {
        color *= 0.4;
        return;
    }*/
}
