/******************************************************************************
* File name: main.cpp       File author(s): Professor Winebrenner             *
*                                           Mod. by Elysium Hosack            *
* File description:                                                           *
* Duplicated helloTriangle to use as the basis of assignment 2. REMEMBER TO   *
* UPDATE AS YOU MAKE PROGRESS                                                 *
*                                                                             *
* Cloned: 9/6/2024          Edited last: 9/10/2024                            *
*                                                                             *
******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include <ew/external/stb_image.h>


#include <serinity/Shader.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 960;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Serinity - Hello Triangle", nullptr, nullptr);
	if (window == nullptr) {
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
		0.5f, 0.5f, 0.0f, 1, 0, 0, 1,
		0.5f, -0.5f, 0.0f, 0, 1, 0, 1,
		-0.5f, -0.5f, 0.0f, 0, 0, 1, 1,
		-0.5f, 0.5f, 0.0f, 1, 1, 1, 1
	};

	unsigned char indices [] = {
		0, 1, 3,
		1, 2, 3
	};

	float textureCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};


	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//texture setup
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// Using my shader class
	serinity::Shader serinityTest("assets/hellotriangle.vert", "assets/hellotriangle.frag");
	
	// Creating VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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

		float timeValue = glfwGetTime();
		const float rValue = .3f, gValue = .6f, bValue = .3f;

		glClearColor(rValue, gValue, bValue, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		serinityTest.use();
		serinityTest.setFloat("uTime", timeValue);
		serinityTest.setFloat("uSpeed", 2.0f);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
	return 0;
}