#version 400

// Flat uniforms
uniform sampler3D volumeTexture;

uniform mat4 MSVP;
uniform mat4 inverseMSVP;

uniform float tfMid;
uniform float tfRange;
uniform float densityFactor;
uniform float marchDistance;

// Varying uniforms
in vec2 fragPosition;
out vec4 fragColor;

float calcDepth(vec3 pos)
{
    // using calcDepth, you can convert a ray position to an OpenGL z-value, so that
    // intersections/occlusions with the model geometry are handled correctly, e.g.: gl_FragDepth =
    // calcDepth(nearestHit); in case there is no intersection, you should get gl_FragDepth to 1.0,
    // i.e., the output of the shader will be ignored

    float far = gl_DepthRange.far;
    float near = gl_DepthRange.near;
    vec4 clip_space_pos = MSVP * vec4(pos, 1.0);
    float ndc_depth = clip_space_pos.z / clip_space_pos.w;
    return (((far - near) * ndc_depth) + near + far) / 2.0;
}

// BEZIER INTERPOLATION

float tfInterpolateBezierCubic(float valueToMidLength, float totalLength)
{
    float t = 1.0 - (valueToMidLength / totalLength);
    return pow(t, 3.0) - (3.0 * pow(t, 2.0)) / 2.0 + (3.0 * t) / 2.0;
}

// TRANSFER FUNCTION

vec4 transferFunction(float dataValue)
{
    // SETUP

    // Need to divide by size of Uint (I dont remember exactly why. But, it will return a fractional
    // number)
    float sizeofUint = 65536.0;

    float midValue = tfMid;
    midValue = midValue / sizeofUint;

    float valueRange = tfRange;
    valueRange = valueRange / sizeofUint;

    float valueToMidLength = abs(dataValue - midValue);
    float totalRangeLength = valueRange / 2.0;

    // return blank (or context color value) if outside range
    if (valueToMidLength > totalRangeLength)
    {
        return vec4(0.0, 0.0, 0.0, 0.0);
    }

    // Return a focus color value if inside range
    else
    {
        // To get a smoother transfer between context and focus, we can use a bezier curve
        float totalInfluence = tfInterpolateBezierCubic(valueToMidLength, totalRangeLength);

        totalInfluence *= densityFactor;

        // Return a color using the interpolated value
        vec3 returnColor = vec3(totalInfluence, totalInfluence, totalInfluence);
        float returnAlpha = totalInfluence;
        return vec4(returnColor, returnAlpha);
    }
}

vec4 dvr(vec3 rayOrigin, vec3 rayDirection, vec3 enterPoint, vec3 exitPoint)
{
    float maxDistance = length(exitPoint - enterPoint);
    vec3 currentPosition;
    float totalDistanceTraveled = 0.0;

    vec3 currentColor = vec3(0.0);
    float currentAlpha = 0.0;

    vec3 accumulatedColor = vec3(0.0);
    float accumulatedAlpha = 0.0;

    // DVR loop
    while (totalDistanceTraveled < maxDistance)
    {
        currentPosition = enterPoint + totalDistanceTraveled * rayDirection;

        // Sample at march point
        float volumeTextureValue = texture(volumeTexture, currentPosition).r;

        // Map to RGBa (transfer function)
        vec4 currentSample = transferFunction(volumeTextureValue);
        currentColor = currentSample.xyz;
        currentAlpha = currentSample.w;

        // COMPOSITE
        float colorAlpha = currentAlpha - (currentAlpha * accumulatedAlpha);
        colorAlpha *= densityFactor;
        accumulatedAlpha += colorAlpha;
        accumulatedColor += currentColor * colorAlpha;

        // Early-ray termination (Krüger and Scharsach [KW03a, Sch05])
        // PERF(abi): stop evaluations for fragments that have reached opacity saturation.
        if (accumulatedAlpha > 0.99)
        {
            break;
        }

        // March along
        totalDistanceTraveled += marchDistance;
    }

    return vec4(accumulatedColor, accumulatedAlpha);
}

void main()
{
    // Ray origin & direction
    /* vec4 near = inverseMSVP * vec4(fragPosition, -1.0, 1.0); */
    /* near /= near.w; */

    /* vec4 far = inverseMSVP * vec4(fragPosition, 1.0, 1.0); */
    /* far /= far.w; */

    /* vec3 rayOrigin = near.xyz; */
    /* vec3 rayDirection = normalize((far - near).xyz); */

    /* // Ray segment */
    /* vec3 enterPoint = rayOrigin; */
    /* vec3 exitPoint = rayOrigin + (rayDirection * 5); */

    /* fragColor = dvr(rayOrigin, rayDirection, enterPoint, exitPoint); */

    fragColor = vec4(1.0, 0.5, 0.5, 1.0);
}
