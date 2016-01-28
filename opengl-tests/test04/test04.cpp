#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>

#include <vector>
#include <iostream>

static const char *vertex_shader_code = R"(
#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 fColor;
uniform mat4 MVP;
void main()
{
	gl_Position = MVP * vec4(vPosition, 1);
	fColor = vColor;
}
)";

static const char *fragment_shader_code = R"(
#version 430 core
in vec4 fColor;
out vec4 color;
void main()
{
	color = fColor;
}
)";

static void error_callback(int error, const char *message)
{
	std::cerr << "glfw error : " << message << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scankey, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	}
	default:
		break;
	}
}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	if (glfwInit() != GL_TRUE) {
		return EXIT_FAILURE;
	}

	GLFWwindow *window = glfwCreateWindow(1024, 768, "test04", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	GLenum error;
	if ((error = glewInit()) != GLEW_OK) {
		std::cerr << "glew error : " << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	
	GLuint vertex_shader, fragment_shader, program;
	GLint status, len;
	std::vector<char> logBuf;

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &len);
	logBuf.resize(len);
	glGetShaderInfoLog(vertex_shader, len, nullptr, logBuf.data());
	std::cerr << "vertex shader info log : " << std::endl << logBuf.data();

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &len);
	logBuf.resize(len);
	glGetShaderInfoLog(fragment_shader, len, nullptr, logBuf.data());
	std::cerr << "fragment shader info log : " << std::endl << logBuf.data();

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	std::cerr << "program info log : " << std::endl << logBuf.data();

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	
	struct Vertex {
		glm::vec3 pos;
		glm::vec4 color;
	} vertices[] = {
		{{-1.0f,-1.0f,-1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		{ { -1.0f,-1.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 1.0f, 1.0f,-1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -1.0f,-1.0f,-1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -1.0f, 1.0f,-1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -1.0f,-1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f, 1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -1.0f,-1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -1.0f,-1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f,-1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f,-1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f,-1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { -1.0f,-1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ {1.0f, 1.0f,-1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		{ { 1.0f,-1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f,-1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f,-1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f,-1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		{ { 1.0f,-1.0f, 1.0 },{ 0.0f, 1.0f, 1.0f, 1.0f } },
	};

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLint mvpLocation = glGetUniformLocation(program, "MVP");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	while (glfwWindowShouldClose(window) != GL_TRUE) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/height, 0.1f, 100.0f);
		glm::mat4 view = glm::rotate(glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 1.0f));
		glm::mat4 model1(1.0f);
		glm::mat4 model2 = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)), glm::vec3(0.0f, 0.0f, -2.0f));
		glm::mat4 mvp1 = projection * view * model1;
		glm::mat4 mvp2 = projection * view * model2;

		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)sizeof(glm::vec3));

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp1));
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp2));
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer);

	glUseProgram(0);
	glDeleteProgram(program);

	glfwTerminate();
	return EXIT_SUCCESS;
}
