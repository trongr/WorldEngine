#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main(){

    vec4 textureColor = texture(mySampler, fragmentUV);

//    color = textureColor * fragmentColor;

    color = vec4(fragmentColor.r * 0.5 * (cos(fragmentPosition.x * 2.0 + time) + 1),
                 fragmentColor.g * 0.5 * (cos(fragmentPosition.y * 8.0 + time) + 1),
                 fragmentColor.b * 0.5 * (cos(fragmentPosition.x * 4.0 + time) + 1),
                 fragmentColor.b * 0.5 * (cos(fragmentPosition.x * 16.0 + time) + 1))
            * textureColor;
}