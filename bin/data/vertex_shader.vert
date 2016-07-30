#version 330 core 
layout (location = 0) in vec3 position; // 位置变量的属性position为 0 
layout (location = 2) in vec2 texCoord;//新增的纹理

out vec2 TexCoord;//新增的纹理
 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
void main() 
{ 
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoord = texCoord;//新增的纹理
}