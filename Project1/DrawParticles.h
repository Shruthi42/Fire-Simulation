#pragma once

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace OTHERDRAW {
	void initBuffer(GLuint &VBO, GLuint &particleVAO)
	{
		//glm::vec3 point1 = gaussian(1);

		GLfloat particles[] = {/*
			-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

			-0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f,
			0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,1.0f, 1.0f,
			0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,1.0f, 1.0f,
			-0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f,
			-0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f,

			-0.01f,  0.01f,  0.01f, -1.0f,  0.0f,  0.0f, 0.0f,1.0f,
			-0.01f,  0.01f, -0.01f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.01f, -0.01f, -0.01f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.01f, -0.01f, -0.01f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f,
			-0.01f, -0.01f,  0.01f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.01f,  0.01f,  0.01f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

			0.01f,  0.01f,  0.01f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			0.01f,  0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f,
			0.01f, -0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f,
			0.01f, -0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f,
			0.01f, -0.01f,  0.01f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f,
			0.01f,  0.01f,  0.01f,  1.0f,  0.0f,  0.0f,1.0f, 1.0f,

			-0.01f, -0.01f, -0.01f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			0.01f, -0.01f, -0.01f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-0.01f, -0.01f, -0.01f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

			-0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f,
			0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f,1.0f, 1.0f,
			0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f, 1.0f, 1.f,
			-0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f*/
			/*
					-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
					0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
					0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
					0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
					-0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
					-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,

					-0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.5f, 0.5f,
					0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f, 0.5f, 0.5f,
					0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.5f, 0.5f,
					0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.5f, 0.5f,
					-0.01f,  0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.5f, 0.5f,
					-0.01f, -0.01f,  0.01f,  0.0f,  0.0f,  1.0f,0.5f, 0.5f,

					-0.01f,  0.01f,  0.01f, -1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					-0.01f,  0.01f, -0.01f, -1.0f,  0.0f,  0.0f, 0.5f, 0.5f,
					-0.01f, -0.01f, -0.01f, -1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					-0.01f, -0.01f, -0.01f, -1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					-0.01f, -0.01f,  0.01f, -1.0f,  0.0f,  0.0f, 0.5f, 0.5f,
					-0.01f,  0.01f,  0.01f, -1.0f,  0.0f,  0.0f,0.5f, 0.5f,

					0.01f,  0.01f,  0.01f,  1.0f,  0.0f,  0.0f, 0.5f, 0.5f,
					0.01f,  0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					0.01f, -0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					0.01f, -0.01f, -0.01f,  1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					0.01f, -0.01f,  0.01f,  1.0f,  0.0f,  0.0f,0.5f, 0.5f,
					0.01f,  0.01f,  0.01f,  1.0f,  0.0f,  0.0f,0.5f, 0.5f,

					-0.01f, -0.01f, -0.01f,  0.0f, -1.0f,  0.0f, 0.5f, 0.5f,
					0.01f, -0.01f, -0.01f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,
					0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,
					0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,
					-0.01f, -0.01f, 0.01f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,
					-0.01f, -0.01f, -0.01f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,

					-0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f, 0.5f, 0.5f,
					0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f,0.5f, 0.5f,
					0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f,0.5f, 0.5f,
					0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f, 0.5f, 0.5f,
					-0.01f,  0.01f,  0.01f,  0.0f,  1.0f,  0.0f, 0.5f, 0.5f,
					-0.01f,  0.01f, -0.01f,  0.0f,  1.0f,  0.0f, 0.5f, 0.5f
					*/
					/*
							-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f,
							0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.8f, 0.2f,
							0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.8f, 0.8f,
							0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.8f, 0.8f,
							-0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.2f, 0.8f,
							-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f

							*/

							/*- 0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							-0.01f,  0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							-0.01f, -0.01f, -0.01f,  0.0f,  0.0f, -1.0f, 0.5f, 0.5f,
							*/

					-0.01f, -0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
					0.01f, -0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
					0.01f, 0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
					0.01f, 0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
					-0.01f, 0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
					-0.01f, -0.02f, -0.01f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		};
		// First, set the container's VAO (and VBO)
		glGenVertexArrays(1, &particleVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_STATIC_DRAW);

		glBindVertexArray(particleVAO);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//Texture attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}


	void DrawParticles(GLint particleVAO, GLint objectColorLoc, glm::vec3 color, GLuint texture, GLuint transparency, Shader lightingShader)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUniform3f(objectColorLoc, color.r, color.g, color.b);

		glDisable(GL_LIGHTING);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "text"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, transparency);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "trans"), 1);

		glBindVertexArray(particleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}