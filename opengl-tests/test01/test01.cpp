
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

static void error_calback(int error, const char *message)
{

}

static void reshape(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	return;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
	default:
		break;
	}
}

static void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

int main(void)
{
	glfwSetErrorCallback(error_calback);

	if (!glfwInit()) {
		return EXIT_FAILURE;
	}

	GLFWwindow *window = glfwCreateWindow(1024, 768, "test01", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	reshape(window, width, height);

	GLenum error;
	if ((error = glewInit()) != GLEW_NO_ERROR) {
		fprintf(stderr, "glew init failed, %s", glewGetErrorString(error));
		glfwTerminate();
		return EXIT_FAILURE;
	}

	init();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
		//glfwWaitEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}