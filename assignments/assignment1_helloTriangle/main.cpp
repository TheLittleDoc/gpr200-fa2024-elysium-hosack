/******************************************************************************
* File name: main.cpp       File author(s): Professor Winebrenner(?)          *
*                                           Mod. by Elysium Hosack            *
* File description:                                                           *
* Using Eric's framework from assignment 1. Goal is to render a classic Hello *
* Triangle window, plus our own little twist.                                 *
*                                                                             *
* Cloned: 9/6/2024          Edited last: 9/6/2024                             *
*                                                                             *
******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Serinity - Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1, 0, 0, 1,
		0.5f, -0.5f, 0.0f, 0, 1, 0, 1,
		0.0f, 0.5f, 0.0f, 0, 0, 1, 1
	};

	// Vertex Shader
	// from learnopengl.com

	const char *vertexShaderSourceold =	"#version 330 core										\n"
										"layout (location = 0) in vec3 aPos;					\n"
										"void main()											\n"
										"{														\n"
										"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
										"}														\0";

	const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 vertexColor;

uniform vec3 offset;

void main()
{
	gl_Position = vec4(aPos + offset, 1.0);
	vertexColor = aColor;

}

)";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	// from learnopengl.com


	const char *fragmentShaderSource = R"(

#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

void main()
{
	FragColor = vertexColor;
}

)";
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Shader program
	// also from learnopengl.com

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);





	// Creating VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//Creating VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);



	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float xValue = (sin(timeValue) / 6.0f) + 0.0f;
		float yValue = (sin(timeValue) / 6.0f) + 0.0f;
		float zValue = (sin(timeValue) / 6.0f) + 1.0f;



		int vertexColorLocation = glGetUniformLocation(shaderProgram, "offset");
		glUseProgram(shaderProgram);
		glUniform3f(vertexColorLocation, xValue, yValue, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
