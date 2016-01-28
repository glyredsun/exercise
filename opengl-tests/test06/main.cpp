#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>

#include <iostream>
#include <vector>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

static const char *vertex_shader_code = R"(
#version 330 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTextureCoordinate;
out vec2 textureCoordinate;
uniform mat4 MVP;
void main()
{
	gl_Position = MVP * vec4(vPosition, 1);
	textureCoordinate = vTextureCoordinate;
}
)";

static const char *fragment_shader_code = R"(
#version 330 core
uniform sampler2D texture;
in vec2 textureCoordinate;
out vec4 color;
void main()
{
	color = texture2D(texture, textureCoordinate);
}
)";

struct Bitmap {


	int width;
	int height;
	short BitsPerPixel;
	std::vector<unsigned char> pixels;

	Bitmap(const char* FilePath) : width(0), height(0), BitsPerPixel(0) {
		load(FilePath);
	}

	//adapted from http://stackoverflow.com/questions/20595340/loading-a-tga-bmp-file-in-c-opengl
	void load(const char* FilePath)
	{
		std::fstream hFile;

		//search for file by going up file directory tree up to 5 times
		int attempts = 0;
		string nfilepath = FilePath;
		while (!hFile.is_open() && attempts < 5) {
			hFile.open(nfilepath.c_str(), std::ios::in | std::ios::binary);
			nfilepath = "../" + nfilepath;
			attempts += 1;
		}
		if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");

		hFile.seekg(0, std::ios::end);
		int Length = hFile.tellg();
		hFile.seekg(0, std::ios::beg);
		std::vector<uint8_t> FileInfo(Length);
		hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);

		if (FileInfo[0] != 'B' && FileInfo[1] != 'M')
		{
			hFile.close();
			throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
		}

		if (FileInfo[28] != 24 && FileInfo[28] != 32)
		{
			hFile.close();
			throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
		}

		BitsPerPixel = FileInfo[28];
		width = FileInfo[18] + (FileInfo[19] << 8);
		height = FileInfo[22] + (FileInfo[23] << 8);
		uint32_t pixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
		uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
		pixels.resize(size);

		hFile.seekg(pixelsOffset, std::ios::beg);
		hFile.read(reinterpret_cast<char*>(pixels.data()), size);
		hFile.close();
	}

};

void error_callback(int error, const char *message)
{
	std::cerr << "glfw error : " << message << std::endl;
}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	if (glfwInit() != GL_TRUE) {
		return EXIT_FAILURE;
	}

	GLFWwindow *window = glfwCreateWindow(1024, 768, "test05", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);

	GLenum error;
	if ((error = glewInit()) != GLEW_OK) {
		std::cerr << "glew error : " << glewGetErrorString(error) << std::endl;
		return EXIT_FAILURE;
	}

	GLint logLen;
	std::vector<char> logBuf;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLen);
	logBuf.resize(logLen);
	glGetShaderInfoLog(vertex_shader, logLen, nullptr, logBuf.data());
	std::cerr << "vertex shader info log : " << std::endl << logBuf.data() << std::endl;

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &logLen);
	logBuf.resize(logLen);
	glGetShaderInfoLog(fragment_shader, logLen, nullptr, logBuf.data());
	std::cerr << "fragment shader info log : " << std::endl << logBuf.data() << std::endl;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
	logBuf.resize(logLen);
	glGetProgramInfoLog(program, logLen, nullptr, logBuf.data());
	std::cerr << "program info log : " << std::endl << logBuf.data() << std::endl;
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	int tw = 40;
	int th = 40;
	std::vector<glm::vec4> texture_data;
	for (int i = 0; i < tw; i++) {
		for (int j = 0; j < th; j++) {
			texture_data.push_back(glm::vec4(static_cast<float>((i + j) % 2), 0.0f, static_cast<float>((i + j + 1) % 2), 1.0f));
		}
	}

	GLuint textureIDs[6];
	const char *images[] = { "front.bmp", "top.bmp", "back.bmp" , "bottom.bmp" , "left.bmp" , "right.bmp" };
	glGenTextures(6, textureIDs);
	for (size_t i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		Bitmap bm(images[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bm.width, bm.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, bm.width, bm.height, GL_BGR, GL_UNSIGNED_BYTE, bm.pixels.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	struct Vertex {
		glm::vec3 pos;
		glm::vec2 textCoor;
	} vertices[] = {
		// front
		{ { -1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, -1.0f, 1.0f },{ 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },

		// top
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f } },

		// back
		{ { 1.0f, -1.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { -1.0f, -1.0f, -1.0f },{ 1.0f, 0.0f } },
		{ { -1.0f, 1.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f } },

		// bottom
		{ { 1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f } },
		{ { -1.0f, -1.0f, 1.0f },{ 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { 1.0f, -1.0f, -1.0f },{ 0.0f, 1.0f } },

		// left
		{ { -1.0f, -1.0f, -1.0f },{ 0.0f, 0.0f } },
		{ { -1.0f, -1.0f, 1.0f },{ 1.0f, 0.0f } },
		{ { -1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f } },

		// right
		{ { 1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, -1.0f, -1.0f },{ 1.0f, 0.0f } },
		{ { 1.0f, 1.0f, -1.0f },{ 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },
	};

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint mvpID = glGetUniformLocation(program, "MVP");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	double lastTime = glfwGetTime();
	float horizontalAngle = M_PI;
	float verticalAngle = 0.0f;
	float speed = 3.0f;
	float mouseSpeed = 0.0005f;
	glm::vec3 eyePos(0.0f, 0.0f, 5.0f);
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)sizeof(glm::vec3));

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		double centerX, centerY;
		centerX = double(width) / 2;
		centerY = double(height) / 2;

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f);

		double cursorPosX, cursorPosY;
		glfwGetCursorPos(window, &cursorPosX, &cursorPosY);
		glfwSetCursorPos(window, centerX, centerY);

		horizontalAngle += mouseSpeed * (centerX - cursorPosX);
		verticalAngle += mouseSpeed * (centerY - cursorPosY);

		glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
		glm::vec3 right(sin(horizontalAngle - M_PI_2), 0, cos(horizontalAngle - M_PI_2));

		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		if ((glfwGetKey(window, GLFW_KEY_UP) | glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS) {
			eyePos += speed * deltaTime * direction;
		}

		if ((glfwGetKey(window, GLFW_KEY_DOWN) | glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS) {
			eyePos -= speed * deltaTime * direction;
		}

		if ((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) | glfwGetKey(window, GLFW_KEY_D)) {
			eyePos += speed * deltaTime * right;
		}

		if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) | glfwGetKey(window, GLFW_KEY_A)) {
			eyePos -= speed * deltaTime * right;
		}

		glm::mat4 view = glm::lookAt(eyePos, eyePos + direction, glm::cross(right, direction));
		glm::mat4 model;
		//model = glm::scale(model, glm::vec3(1.0f + cosf(static_cast<float>(glfwGetTime()))));
		//model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat4 mvp = projection * view * model;

		glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));

		for (size_t i = 0; i < 6; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
			glDrawArrays(GL_QUADS, 4 * i, 4);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwWindowShouldClose(window) != GL_TRUE && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteProgram(program);
	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}

