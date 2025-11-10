#version 330
in vec3 TexCoords;
out vec4 color;
uniform samplerCube skybox;
uniform vec4 colorMod;
void main()
{
    vec4 origColor = texture(skybox,TexCoords);

    color = vec4(origColor.rgb*colorMod.rgb, origColor.a);
}
