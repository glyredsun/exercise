#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <cstdio>
#include <cstdlib>

#include <vector>

using namespace std;
using namespace glm;

void error_callback(int error, const char *message)
{
	fprintf(stderr, "glfw error : %s\n", message);
}

void reshape(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GL_TRUE) {
		return EXIT_FAILURE;
	}

	int width = 1024;
	int height = 768;
	GLFWwindow *window = glfwCreateWindow(width, height, "", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(window, reshape);
	reshape(window, width, height);

	static const char *vertex_shader_code =
		"#version 430 core								\n"
		"layout(location = 0) in vec3 vPosition;		\n"
		"layout(location = 1) in vec4 vColor;			\n"
		"out vec4 fColor;								\n"
		"void main()									\n"
		"{												\n"
		"	gl_Position.xyz = vPosition;				\n"
		"	fColor = vColor;							\n"
		"}												\n";
		
	static const char *fragment_shader_code =
		"#version 430 core								\n"
		"in vec4 fColor;								\n"
		"out vec4 color;								\n"
		"void main()									\n"
		"{												\n"
		"	color = fColor;								\n"
		"}												\n";
	

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	GLint status;
	GLint len;
	std::vector<char> logBuf;
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &len);
	logBuf.resize(len);
	glGetShaderInfoLog(vertex_shader, len, nullptr, logBuf.data());
	fprintf(stderr, "%s", logBuf.data());

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &len);
	logBuf.resize(len);
	glGetShaderInfoLog(fragment_shader, len, nullptr, logBuf.data());
	fprintf(stderr, "%s", logBuf.data());
	
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	logBuf.resize(len);
	glGetProgramInfoLog(program, len, nullptr, logBuf.data());
	fprintf(stderr, "%s", logBuf.data());
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	static struct Vertex {
		vec3 pos;
		vec4 color;
	} vertices[] = {
		{ vec3(-1.0f, -1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ vec3(1.0f, -1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ vec3(0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) }
	};
	
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	while (glfwWindowShouldClose(window) != GL_TRUE) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteProgram(program);

	glfwTerminate();

	return EXIT_SUCCESS;
}