#version 120

uniform sampler2D texture;
varying vec2 texCoord;

void main(void)
{
    vec4 texColor = texture2D(texture, texCoord);
    gl_FragColor = texColor * vec4(1.0, 0.0, 0.0, 1.0);
}
