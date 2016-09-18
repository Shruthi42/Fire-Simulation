#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1200,900,"Fire Simulation", nullptr, nullptr); //windowed mode, not sharing resources

	if (window == nullptr)
	{
		std::cout << "Failed to initialize glfw window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew\n";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();



		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}