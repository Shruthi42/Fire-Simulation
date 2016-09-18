// CS148 Summer 2016 Homework 3 - Shaders

#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal; 
in vec2 TextCoord; 
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D text;
uniform sampler2D trans;


void main()
{    
	/*
	e represents the vector from the point of incidence going toward our eye
	Basically, it is the direction in which our eye is located with respect to the point at FragPos
	In addition, we must normalize e to make it unit vector.
	We never use e independently except to derive h, the half angle
	*/
	vec3 e = normalize(viewPos-FragPos);	

	/*
	l is the direction in which light is incident at the point at FragPos.
	This vector points from the piont to the light source, i.e. in the direction opposite to the actual direction of propagation of light
	So, we take l = difference between light position and FragPos
	We normalize l  to make it a unit vector
	*/
	vec3 l = normalize(lightPos-FragPos);


	/*
	n is the normal to the surface. This is passed on from the vertex shader.
	We normalize it to get a unit vector before we use it further.
	*/
	vec3 n = normalize(Normal);

	/*
	This part of the code is used to add ambient lighting.
	In code, to add ambient light, we just add a constant light term.
	a determines the strength of this ambient light term.
	a*lightColor gives the ambient lighting.
	We multiply it with object color to get the color produced when this ambient light interacts with the object
	*/
	
	float a = 1.0f;
	vec3 ambient = a*lightColor*objectColor;	

	/*
	Diffuse lighting is independent of viewing angle.
	It depends only on the direction of the normal and the incident light.
	To obatin the diffuse term, we therefore take the dot product of the two.
	We multiply the incoming light with this term to determine the diffuse component.
	After this, we multiply with the object color to get the color of the light after it leaves the surface.
	
	The max() function is to ensure that there is no diffuse lighting observed when light strikes at an angle greater than 90 degrees, that is, from the back of the surface. The dot product in this case will be negative, and the max() will return 0 for the diffuse component. 
	*/
	vec3 diffuse = max(0.0f,dot(n,l))*objectColor*lightColor;

	/*
	We set the color of the fragment as the sum of the colors obtained due to the ambient, diffuse and specular components
	We also convert the result to the expected type for color, vec4.
	ambient, diffuse and specular are all vec3.
	*/
	//color = vec4(ambient + diffuse, texture(text,TextCoord).r);
	//color = vec4(ambient + diffuse,1.0f);
	
	//color = vec4(TextCoord.y,0.0f,0.0f,0.1f);
	//color = vec4(texture(text,TextCoord).rgb*(ambient + diffuse), texture(text,TextCoord).r);


	
	vec4 colorInt = vec4(texture(text,TextCoord).xyz,pow((1-texture(trans,TextCoord).b),2));
	if(colorInt.a<0.1)
	discard;

	color = colorInt;

} 