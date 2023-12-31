#shader vertex
#version 410 core

layout(location = 0) in uint binVertex;

out vec2 v_TexCoord;
out float v_lightValue;

uniform vec3 u_ChunkPos;
uniform mat4 u_MVP; //model-view-projection matrix

vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 1.0f)
    );

void main() {
    float x = float((binVertex & 0x1Fu) >> 0u);
    float y = float((binVertex & 0x3E0u) >> 5u);
    float z = float((binVertex & 0x7C00u) >> 10u);

    x += u_ChunkPos.x;
    y += u_ChunkPos.y;
    z += u_ChunkPos.z;

    vec4 worldPos = vec4(x, y, z, 1.0);
    gl_Position = u_MVP * worldPos;

    uint uvID = (binVertex >> 15u) & 3;
    uint textureID = (binVertex >> 17u) & 1023;
    uint lightValue = ((binVertex >> 27u) & 7);
    float lightValueF = float(lightValue) / 7;

    v_TexCoord = texCoords[uvID];
    v_lightValue = lightValueF;
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

    color = (texColor * u_Albedo_Color) * v_lightValue;
}
