#version 330 core
layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform float uS;
uniform float uX;
uniform float uY;
uniform bool flipped;
uniform bool open;


void main()
{
    if (open){
        float bottomY = -0.85;
        float scaledY = bottomY + (inPos.y - bottomY) * 1.5f;
        gl_Position = vec4(inPos.x,scaledY, 0.0, 1.0);
    }else{
            gl_Position = vec4(inPos.x + uX,(inPos.y * uS + uY) , 0.0, 1.0);
    }
    TexCoord = aTex;
    if (flipped) {
        TexCoord.x = 1.0 - TexCoord.x;
    }

}
