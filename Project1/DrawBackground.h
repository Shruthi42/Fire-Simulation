#pragma once

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Background {

	GLuint VBO, particleVAO;
	GLuint texture, transparency;

public:


	void init()
	{
		//glm::vec3 point1 = gaussian(1);

		GLfloat particles[] = {

			-1.5f, -1.5f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			1.5f, -1.5f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
			1.5f, 1.5f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			1.5f, 1.5f, -1.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-1.5f, 1.5f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			-1.5f, -1.5f, -1.f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

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
	

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* text = SOIL_load_image("Background3.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at Background3.jpg";
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
		text = SOIL_load_image("Black.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		if (text == NULL)
		{
			std::cout << "Error loading texture at Black.jpg";
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(text);
		glBindTexture(GL_TEXTURE_2D, 0);
	
	}




	void DrawBackground(glm::mat4 model,GLuint modelLoc,  GLint objectColorLoc, Shader lightingShader)
	{
		

		glm::vec3 color = glm::vec3(1, 1, 1);

		glm::mat4 model1 = glm::translate(model,glm::vec3(0,0.37,-0.05) );
		//model1 = glm::scale(model1, glm::vec3(1.2,1.2,0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

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

};