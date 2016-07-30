#version 330 core 
in vec3 ourColor;
in vec2 TexCoord;//新增的纹理
out vec4 color; 
uniform sampler2D ourTexture1;//新增的纹理采样器
uniform sampler2D ourTexture2;//第二个纹理
void main() 
{ 
//图片混合
color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.8);
}
