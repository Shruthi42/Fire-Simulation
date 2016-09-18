#pragma once
#include <iostream>
// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GLU.h>
// GLFW
#include <GLFW/glfw3.h>


#include "DrawParticles.h"
#include "Gauss.h"
#include "Comparisons.h"
#include  "Constants.h"

namespace FLAME {


	class Flame;

	struct particle {
		glm::vec3 position, nextPosition;
		glm::vec3 u0, u1;
		double particleSize; //Stores the measure of particle size compared to its original size
		double distance;
		glm::vec3 color;
		void setdefault();
		bool used;
	};


	class Flame
	{
	private:
		particle p[NUMPART];
		int  p0[SIZEX][SIZEY][SIZEZ], p1[SIZEX][SIZEY][SIZEZ];
		glm::vec3 u0[SIZEX][SIZEY][SIZEZ], u1[SIZEX][SIZEY][SIZEZ];
		glm::vec3 force[SIZEX][SIZEY][SIZEZ];
		glm::vec3 visc[SIZEX][SIZEY][SIZEZ];
		double extinction = 0.0;
		GLuint texture, transparency;
		GLuint VBO, particleVAO;

	public:
		void Init();
		void Move(float dt);
		void Draw(GLint modelLoc, glm::mat4 model, GLint objectColorLoc, Shader lightingShader);
		static glm::vec3 source();
		void setSize(particle& p);
		void setColor(particle& p);
		void loadParticleTexture();
		void decreaseExtinction();
		void increaseExtinction();
	};

	glm::vec3 Flame::source()
	{
		glm::vec3 result;
		result.x = (SIZEX / 2) + (fmod(rand(), SIZEX / 1) - SIZEX / 2);
		result.y = fmod(rand(), SIZEY / 4);
		result.z = (SIZEZ / 2) + (fmod(rand(), SIZEZ / 1) - SIZEZ / 2);
		return result;
	}

	void Flame::Init()
	{
		for (int i = 0; i < NUMPART; i++)
		{
			p[i].setdefault();
			p[i].used = true;
		}

		for (int i = 0; i < SIZEX; i++)
			for (int j = 0; j < SIZEY; j++)
				for (int k = 0; k < SIZEZ; k++)
				{
					force[i][j][k].x = pow((1 / (abs((SIZEX / 2) - i) + 1)), 2);
					force[i][j][k].y = 4 * gaussian(j, 0, SIZEY / 2) + 0.5;
					force[i][j][k].z = pow((1 / (abs((SIZEZ / 2) - i) + 1)), 2);
					visc[i][j][k] = glm::vec3(0.5, 0.0, 0.5);
				}

		loadParticleTexture();
		// Set up vertex data (and buffer(s)) and attribute pointers
		OTHERDRAW::initBuffer(VBO, particleVAO);
	}

	void Flame::Move(float dt)
	{
		for (int i = 0; i < NUMPART; i++)
		{
			if (!p[i].used) continue;
			p[i].u1 = p[i].u0 + dt * force[(int)p[i].position.x][(int)p[i].position.y][(int)p[i].position.z];
			p[i].u1 = cutAtZero(p[i].u1 - visc[(int)p[i].position.x][(int)p[i].position.y][(int)p[i].position.z]);
		}

		glm::vec3 distance;

		for (int i = 0; i < NUMPART; i++)

		{
			if (!p[i].used) continue;

			distance = dt*p[i].u1;
			p[i].distance = p[i].distance + distance;
			/*
			int xIndex = fmod((p[i].position.x + distance.x), SIZEX);
			int yIndex = fmod((p[i].position.y + distance.y), SIZEY);
			int zIndex = fmod((p[i].position.z + distance.z), SIZEZ);
			*/
			int xIndex = p[i].position.x + distance.x;
			int yIndex = p[i].position.y + distance.y;
			int zIndex = p[i].position.z + distance.z;

			p[i].nextPosition = boundToZero(glm::vec3(xIndex, yIndex, zIndex), Flame::source, SIZEX, SIZEY, SIZEZ);
			if (!(p[i].nextPosition>glm::vec3(0, 0, 0)))
			{
				force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] = force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] - glm::vec3(extinction, extinction, extinction);
				p[i].setdefault();
			}

			force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] = force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] - glm::vec3(extinction, extinction, extinction);
			force[(int)p[i].nextPosition.x][(int)p[i].nextPosition.x][(int)p[i].nextPosition.x] = force[(int)p[i].nextPosition.x][(int)p[i].nextPosition.x][(int)p[i].nextPosition.x] + glm::vec3(extinction, extinction, extinction);
		}

		for (int i = 0; i < NUMPART; i++)
		{
			if (!p[i].used) continue;

			p[i].position = p[i].nextPosition;
			p[i].u0 = p[i].u1;
			p[i].nextPosition = glm::vec3(0, 0, 0);
			setSize(p[i]);
			setColor(p[i]);
		}
		/*
		//Add a few particles to compensate
		for (int i = 0; i < SIZEX; i++)
		for (int j = 0; j < SIZEY; j++)
		for (int k = 0; k < SIZEZ; k++)
		{
		p0[i][0][k] = gaussian(i, (double)(SIZEX / 2), SIZEX)*(((rand() % 3) % 2) - 1);
		p0[i][1][k] = gaussian(i, (double)(SIZEY / 2), SIZEY)*(((rand() % 3) % 2) - 1);
		}
		*/
	}

	void Flame::Draw(GLint modelLoc, glm::mat4 model, GLint objectColorLoc, Shader lightingShader)
	{


		glm::mat4 model1;


		for (int i = 0; i < NUMPART; i++)
		{
			if (!p[i].used) continue;
			model1 = glm::translate(model, glm::vec3(GRIDSIZE*(p[i].position.x - SIZEX / 2), GRIDSIZE*(p[i].position.y - SIZEY / 2), GRIDSIZE*(p[i].position.z - SIZEZ / 2)));
			model1 = glm::scale(model1, glm::vec3(p[i].particleSize, p[i].particleSize, p[i].particleSize));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

			OTHERDRAW::DrawParticles(particleVAO, objectColorLoc, p[i].color, texture, transparency, lightingShader);

		}

	}

	void Flame::setSize(particle &p)
	{
		p.particleSize = p.particleSize / (1.01 + 0.0005*p.distance);
	}

	void Flame::setColor(particle &p)
	{
		p.color.r = p.color.r>0.1 ? p.color.r - 0.01 : 0.1;
		p.color.g = p.color.g < 0.2 ? p.color.g + 0.01 : 0.2;
		p.color.g = p.color.g < 0.1 ? p.color.g + 0.005 : 0.1;
	}

	void particle::setdefault()
	{
		position = Flame::source();
		u0 = glm::vec3(0, 0, 0);// glm::vec3((rand() % 1000) - 500, 3, rand() % 1000000);
		u1 = glm::vec3(0, 0, 0);
		particleSize = 10;
		distance = 0;
		color = glm::vec3(1, 0, 0);
		bool used = false;
	}

	void Flame::loadParticleTexture()
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* text = SOIL_load_image("FireImage.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at FireImage.jpg";
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(text);
		glBindTexture(GL_TEXTURE_2D, 0);


		glGenTextures(1, &transparency);
		glBindTexture(GL_TEXTURE_2D, transparency);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//int width, height;
		text = SOIL_load_image("TransparencyValue3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at TransparencyValue2.jpg";
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(text);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void Flame::decreaseExtinction()
	{
		extinction = extinction > 0.01 ? extinction - 0.01 : 0;
		for (int i = 0; i < SIZEX; i++)
			for (int j = 0; j < SIZEY; j++)
				for (int k = 0; k < SIZEZ; k++)
				{
					force[i][j][k] = (force[i][j][k]>glm::vec3(1, 1, 1)) ? force[i][j][k] - glm::vec3(0.1, 0.1, 0.1) : force[i][j][k] + glm::vec3(0, 0.1, 0);

				}
	}

	void Flame::increaseExtinction()
	{
		extinction += 0.01;

	}

}
