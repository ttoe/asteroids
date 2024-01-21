#version 330

precision highp float;

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform float seconds;

float sdBox(in vec2 p, in vec2 b)
{
    vec2 d = abs(p) - b;
    return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
}

void main()
{
#if 0
    vec2 center = vec2(.5, .5);
    float dist_from_center = distance(center, fragTexCoord);

    float red = pow(dist_from_center, 2);
    float alpha = seconds * red;
    finalColor = vec4(red, 0, 0, alpha);
#else
    float red = sdBox(fragTexCoord - .5, vec2(.25, .25));
    red = 1.2*(red);
    float alpha = 1.5 * (red * seconds);
    finalColor = vec4(red, 0, 0, alpha);
#endif
}
