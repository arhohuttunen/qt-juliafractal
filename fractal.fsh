#ifdef GL_ES
precision mediump float;
#endif
varying mediump vec2 texc;
uniform mediump float aspect;
uniform mediump float zoom;
uniform mediump vec2 pan;
uniform mediump vec2 seed;

float computeValue(vec2 v, vec2 offset)
{
    int iterations = 128;
    float vxsquare = 0.0;
    float vysquare = 0.0;
    int iteration = 0;
    int lastIteration = iterations;

    do
    {
        vxsquare = v.x * v.x;
        vysquare = v.y * v.y;

        v = vec2(vxsquare - vysquare, v.x * v.y * 2.0) + offset;

        iteration++;

        if ((lastIteration == iterations) && (vxsquare + vysquare) > 4.0)
            lastIteration = iteration + 1;
    }
    while (iteration < lastIteration);

    return (float(iteration) - (log(log(sqrt(vxsquare + vysquare))) / log(2.0))) / float(iterations);
}

void main()
{
    vec3 colorScale = vec3(4.0, 5.0, 6.0);

    vec2 v = (texc - 0.5) * zoom * vec2(1, aspect) - pan;
    float val = computeValue(v, seed);
    gl_FragColor = vec4(sin(val * colorScale.x), sin(val * colorScale.y), sin (val * colorScale.z), 1);
}
