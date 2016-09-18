#pragma once

#include <glm/glm.hpp>

#include  "Constants.h"


glm::vec3 cutAtZero2(glm::vec3 a)
{/*
	glm::vec3 result;
	if (a.x > 0)
		result.x = a.x;
	else result.x = 0;

	if (a.y > 0)
		result.y = a.y;
	else result.y = 0;

	if (a.z > 0)
		result.z = a.z;
	else result.z = 0;*/

	glm::vec3 result;
		result.x = a.x;

	if (a.y > 0)
		result.y = a.y;
	else result.y = 0;
	
		result.z = a.z;
	

	return result;
}
glm::vec3 cutAtZero(glm::vec3 a)
{
 glm::vec3 result;
 if (a.x > 0)
 result.x = a.x;
 else result.x = 0;

 if (a.y > 0)
 result.y = a.y;
 else result.y = 0;

 if (a.z > 0)
 result.z = a.z;
 else result.z = 0;

 return result;
	
}

glm::vec3 boundToZero(glm::vec3 a, glm::vec3 (*generator)(void),int sizex,int sizey,int sizez)
{
	if ((a.x > 0 && a.x < sizex) && (a.y > 0 && a.y < sizey) && (a.z > 0 && a.z < sizez))
		return a;
	else return generator();
}

bool operator>(glm::vec3 a, glm::vec3 b)
{
	if ((a.x > b.x) && (a.y > b.y) && (a.z > b.z))
		return true;
	else return false;
}

double operator+(double a, glm::vec3 b)
{
	double dist = sqrt((b.x*b.x)+ (b.y*b.y)+ (b.z*b.z));
	return a + dist;
}

double mod(glm::vec3 a)
{
	return sqrt((a.x*a.x) + (a.y*a.y) + (a.z*a.z));
}