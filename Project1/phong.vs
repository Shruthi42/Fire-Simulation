// CS148 Summer 2016 Homework 3 - Shaders

#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinate;


out vec3 Normal;
out vec3 FragPos;
out vec2 TextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	/*
	gl_Position is set by applying the model, view and matrix transformations
	in order to transform  the original coordinates to NDC
	*/
	gl_Position = projection * view * model * vec4(position,1.0f);

	/*
	We need to get the position of the fragment in world space
	We need this because all of the lighting calculations in the fragment shader were done using the world space coordinates.
	Therefore, to compute directions, we need fragment position in world space
	*/
	vec4 FP = model*vec4(position,1.0f);
	FragPos = FP.xyz; //Only x,y,z are stored in FragPos, which is type vec3

	/*
	We pass the normal to the fragment shader by setting variable Normal = normal.
	normal is defined for each vertex in main(),in the vertex data array.
	*/
	Normal = normal;
	TextCoord = textureCoordinate;
} 