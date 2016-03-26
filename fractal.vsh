attribute highp vec4 vertex;
attribute mediump vec2 texCoord;
varying mediump vec2 texc;
uniform mediump mat4 matrix;

void main(void)
{
    gl_Position = matrix * vertex;
    texc = texCoord;
}
