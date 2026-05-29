#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//uniform float xOffset;
//out vec4 ourPosition;

//uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//transform * vec4(aPos, 1.0f);
	//vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
	//ourColor = aColor;
	//ourPosition = gl_Position;
	TexCoord = aTexCoord;
}