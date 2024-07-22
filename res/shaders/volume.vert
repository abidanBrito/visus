#version 400

in vec2 position;
// out vec2 fragPosition;

// NOTE(abi): we set depth to 0, so that the fullscreen quad is at the near plane.
void main()
{
    // fragPosition = position;
    gl_Position = vec4(position, 0.0, 1.0);
}
