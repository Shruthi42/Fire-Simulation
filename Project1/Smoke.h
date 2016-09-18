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

namespace SMOKE {

class Smoke;

	struct particle {
		glm::vec3 position, nextPosition;
		glm::vec3 u0, u1;
		double particleSize; //Stores the measure of particle size compared to its original size
		double distance;
		glm::vec3 color;
		void setdefault();
		//bool used;
	};


	class Smoke
	{
	private:
		particle p[NUMPART];
		int  p0[SIZESX][SIZESY][SIZESZ], p1[SIZESX][SIZESY][SIZESZ];
		glm::vec3 u0[SIZESX][SIZESY][SIZESZ], u1[SIZESX][SIZESY][SIZESZ];
		glm::vec3 force[SIZESX][SIZESY][SIZESZ];
		glm::vec3 visc[SIZESX][SIZESY][SIZESZ];
		double extinction = 0.0;
		GLuint texture, transparency;
		int ParticlesInGrid[SIZESX][SIZESY][SIZESZ];
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
		void NumParticlesInGrid();
	};

	glm::vec3 Smoke::source()
	{
		static int a = 0;
		glm::vec3 result;
		result.x = ((double)(SIZESX-r) / 2) + (fmod(rand(), (double)(SIZESX-r) / 4) );
		result.y = fmod(rand(), (double)SIZESY / 4);
		result.z = ((double)SIZESZ / 2) + (fmod(rand(), (double)SIZESZ / 1) - (double)SIZESZ / 2);
		//std::cout << result.x << "   " << result.y << "   " << result.z <<"   "<<a++<<"\n";
		return result;
	}

	void Smoke::Init()
	{
		for (int i = 0; i < NUMPART; i++)
		{
			p[i].setdefault();
			//p[i].used = true;
		}

		for (int i = 0; i < SIZESX; i++)
			for (int j = 0; j < SIZESY; j++)
				for (int k = 0; k < SIZESZ; k++)
				{
					force[i][j][k].x = 10;// pow((1 / (abs((SIZESX / 2) - i) + 1)), 2);
					force[i][j][k].y = 500;
					force[i][j][k].z = 0;// pow((1 / (abs((SIZESZ / 2) - i) + 1)), 2);
					visc[i][j][k] = glm::vec3(0,0,0);
					ParticlesInGrid[i][j][k] = 0;
				}

		loadParticleTexture();

		// Set up vertex data (and buffer(s)) and attribute pointers
		OTHERDRAW::initBuffer(VBO, particleVAO);
	}

	void Smoke::Move(float dt)
	{
		for (int i = 0; i < NUMPART; i++)
		{
			//if (!p[i].used) continue;
			
			p[i].u1 = p[i].u0 +  dt * force[(int)p[i].position.x][(int)p[i].position.y][(int)p[i].position.z];
			p[i].u1 = cutAtZero2(p[i].u1 - visc[(int)p[i].position.x][(int)p[i].position.y][(int)p[i].position.z]);

			std::cout << "u1: " << p[i].u1.x<<"\n";

		}

		glm::vec3 distance;

		for (int i = 0; i < NUMPART; i++)

		{
			//if (!p[i].used) continue;

			distance = dt*p[i].u1;
			p[i].distance = p[i].distance + distance;

			//std::cout << "distance: " << distance.x << "\n";


			/*
			int xIndex = fmod((p[i].position.x + distance.x), SIZESX);
			int yIndex = fmod((p[i].position.y + distance.y), SIZESY);
			int zIndex = fmod((p[i].position.z + distance.z), SIZESZ);
			*/
			int xIndex = p[i].position.x + distance.x;
			int yIndex = p[i].position.y + distance.y;
			int zIndex = p[i].position.z + distance.z;

			p[i].nextPosition = boundToZero(glm::vec3(xIndex, yIndex, zIndex), Smoke::source,SIZESX,SIZESY,SIZESZ);
			if (!(p[i].nextPosition>glm::vec3(0, 0, 0)))
			{
				//force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] = force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] - glm::vec3(extinction, extinction, extinction);
				p[i].setdefault();
			}

			//force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] = force[(int)p[i].position.x][(int)p[i].position.x][(int)p[i].position.x] - glm::vec3(extinction, extinction, extinction);
			//force[(int)p[i].nextPosition.x][(int)p[i].nextPosition.x][(int)p[i].nextPosition.x] = force[(int)p[i].nextPosition.x][(int)p[i].nextPosition.x][(int)p[i].nextPosition.x] + glm::vec3(extinction, extinction, extinction);
		}

		for (int i = 0; i < NUMPART; i++)
		{
			//if (!p[i].used) continue;

			p[i].position = p[i].nextPosition;
			p[i].u0 = p[i].u1;
			p[i].nextPosition = glm::vec3(0, 0, 0);
			setSize(p[i]);
			setColor(p[i]);
		}
		/*
		//Add a few particles to compensate
		for (int i = 0; i < SIZESX; i++)
		for (int j = 0; j < SIZESY; j++)
		for (int k = 0; k < SIZESZ; k++)
		{
		p0[i][0][k] = gaussian(i, (double)(SIZESX / 2), SIZESX)*(((rand() % 3) % 2) - 1);
		p0[i][1][k] = gaussian(i, (double)(SIZESY / 2), SIZESY)*(((rand() % 3) % 2) - 1);
		}
		*/
	}

	void Smoke::NumParticlesInGrid()
	{
		for (int i = 0; i < SIZESX;i++)
			for (int j = 0; j < SIZESY; j++)
				for (int k = 0; k < SIZESZ; k++)
				{
					ParticlesInGrid[i][j][k] = 0;
				}
		for (int i = 0; i < NUMSPART; i++)
		{
			ParticlesInGrid[(int)(p[i].position.x+1)][(int)(p[i].position.y+1)][(int)(p[i].position.z+1)]++;
		}
	}

	void Smoke::Draw(GLint modelLoc, glm::mat4 model, GLint objectColorLoc, Shader lightingShader)
	{

		glm::mat4 model1;

		/*
		for (int i = 0; i < NUMPART; i++)
		{
			
			//if (!p[i].used) continue;
			model1 = glm::translate(model, glm::vec3(GRIDSIZE*(p[i].position.x - SIZESX / 2), GRIDSIZE*(p[i].position.y - SIZESY / 2), GRIDSIZE*(p[i].position.z - SIZESZ / 2)));
			model1 = glm::scale(model1, glm::vec3(p[i].particleSize, p[i].particleSize, p[i].particleSize));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

			DrawParticles(particleVAO, objectColorLoc, p[i].color, texture, transparency, lightingShader);

		}
		*/
		NumParticlesInGrid();
		
		double psize = p[0].particleSize;
		glm::vec3 pcolor = p[0].color;

		for (int i = 0; i < SIZESX; i++)
			for (int j = 0; j < SIZESY; j++)
				for (int k = 0; k < SIZESZ; k++)
				{
					//std::cout << ParticlesInGrid[i][j][k] << "\n";
					for (int n = 0; n < ParticlesInGrid[i][j][k]*10* ParticlesInGrid[i][j][k]; n++)
					{
						//psize = psize / (pow(j, 0.05));
						//if (!p[i].used) continue;
						double e1 = rand() % 10; e1 = (e1 - 5) / 50;
						double e2 = rand() % 10; e2 = (e2 - 5) / 50;
						double e3 = rand() % 10; e3 = (e3 - 5) / 50;
						model1 = glm::translate(model, glm::vec3(e1 + 2.5 * GRIDSIZE*(i - SIZESX / 2), e2 + 1.5 * GRIDSIZE*(j - SIZESY / 2), e3 + 2.5 * GRIDSIZE*(k - SIZESZ / 2)));
						model1 = glm::translate(model1, glm::vec3(-0.10,-0.10,0.01));
						model1 = glm::scale(model1, glm::vec3(psize, psize, psize));
						glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

						OTHERDRAW::DrawParticles(particleVAO, objectColorLoc, pcolor, texture, transparency, lightingShader);

					}
				}


	}

	void Smoke::setSize(particle &p)
	{
		p.particleSize = p.particleSize / (1.01 + 0.0005*p.distance);
	}

	void Smoke::setColor(particle &p)
	{
		p.color.r = p.color.r>0.1 ? p.color.r - 0.01 : 0.1;
		p.color.g = p.color.g < 0.2 ? p.color.g + 0.01 : 0.2;
		p.color.g = p.color.g < 0.1 ? p.color.g + 0.005 : 0.1;
	}

	void particle::setdefault()
	{
		static int b = 0;
		//std::cout << "\nB: "<<b++<<"\n";
		position = Smoke::source();
		u0 = glm::vec3(((b%2==0)?50:-50), 5, 0);// glm::vec3((rand() % 1000) - 500, 3, rand() % 1000000);
		u1 = u0;
		particleSize = 5;
		distance = 0;
		color = glm::vec3(1, 0, 0);
		//bool used = false;
	}

	void Smoke::loadParticleTexture()
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
		unsigned char* text = SOIL_load_image("Grey.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at Grey.jpg";
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
		text = SOIL_load_image("Transpp3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at Transpp3.jpg";
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(text);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void Smoke::decreaseExtinction()
	{
		extinction = extinction > 0.01 ? extinction - 0.01 : 0;
		for (int i = 0; i < SIZESX; i++)
			for (int j = 0; j < SIZESY; j++)
				for (int k = 0; k < SIZESZ; k++)
				{
					force[i][j][k] = (force[i][j][k]>glm::vec3(1, 1, 1)) ? force[i][j][k] - glm::vec3(0.1, 0.1, 0.1) : force[i][j][k] + glm::vec3(0, 0.1, 0);

				}
	}

	void Smoke::increaseExtinction()
	{
		extinction += 0.01;

	}
}