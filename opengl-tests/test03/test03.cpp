#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>

#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

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

static mat4 projection;

static void error_callback(int error, const char *message)
{
	std::cerr << "glfw error : " << message << std::endl;
}

static void reshape(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	projection = perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f);
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
	}
}

int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GL_TRUE) {
		return EXIT_FAILURE;
	}
	int width = 1024, height = 768;
	GLFWwindow *window = glfwCreateWindow(width, height, "", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwSetFramebufferSizeCallback(window, reshape);
	reshape(window, width, height);
	glfwSetKeyCallback(window, key_callback);

	GLint status, log_len;
	vector<char> logbuf;
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_len);
	logbuf.resize(log_len);
	glGetShaderInfoLog(vertex_shader, log_len, nullptr, logbuf.data());
	cerr << "vertex shader info log :" << endl
		<< logbuf.data() << endl;
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_len);
	glGetShaderInfoLog(fragment_shader, log_len, nullptr, logbuf.data());
	cerr << "fragment shader info log :" << endl
		<< logbuf.data();
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
	glGetProgramInfoLog(program, log_len, nullptr, logbuf.data());
	cerr << "program info log :" << endl
		<< logbuf.data();

	struct Vertex{
		vec3 pos;
		vec4 color;
	} vertices[] =
	{
		{ {-1, -1, 0 }, { 1, 0, 0, 1 } },
		{ { 1, -1, 0 }, { 0, 1, 0, 1 } },
		{ { 0, 1, 0 }, { 0, 0, 1, 1 } },
	};
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

		glUseProgram(program);

		mat4 view = glm::rotate(lookAt(vec3(0.0f, 0.0f, 4.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f)), static_cast<float>(glfwGetTime()), vec3(1.0f, 1.0f, 0.0f));
		mat4 model = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f));
		mat4 mvp = projection * view * model;
		GLuint mvpID = glGetUniformLocation(program, "MVP");
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, value_ptr(mvp));
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)sizeof(vec3));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer);
	glUseProgram(0);
	glDeleteProgram(program);

	glfwTerminate();
	return EXIT_SUCCESS;
}