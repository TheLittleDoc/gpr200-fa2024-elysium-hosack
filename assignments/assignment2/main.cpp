/******************************************************************************
* File name: main.cpp       File author(s): Professor Winebrenner             *
*                                           Mod. by Elysium Hosack            *
* File description:                                                           *
* Duplicated helloTriangle to use as the basis of assignment 2. REMEMBER TO   *
* UPDATE AS YOU MAKE PROGRESS                                                 *
*                                                                             *
* Cloned: 9/6/2024          Edited last: 9/17/2024                            *
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

constexpr int SCREEN_WIDTH = 540;
constexpr int SCREEN_HEIGHT = 540;

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


	stbi_set_flip_vertically_on_load(true);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );



	float vertices[] = {
		0.5f, 0.5f, 0.0f,	1, 0, 0, 1,	1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,	0, 1, 0, 1,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0, 0, 1, 1,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	1, 1, 1, 1, 0.0f, 1.0f
	};

	unsigned char indices [] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO;
	unsigned int EBO;
	unsigned int VBO;

	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//UV attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(7*sizeof(float)));
	glEnableVertexAttribArray(2);


	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("assets/AverageNebraskaResident.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	// Using my shader class
	serinity::Shader serinityTest("assets/hellotriangle.vert", "assets/hellotriangle.frag");

	serinityTest.use();
	serinityTest.setInt("uTexture", 0);



	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float timeValue = glfwGetTime();
		constexpr float rValue = .02f, gValue = .03f, bValue = .3f;


		glClear(GL_COLOR_BUFFER_BIT);

		serinityTest.setFloat("uTime", timeValue);
		serinityTest.setFloat("uSpeed", 6.0f);
		serinityTest.setFloat("uHeight", 1.8f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		glfwSwapBuffers(window);
		glClearColor(rValue, gValue, bValue, 1.0f);
	}
	printf("Shutting down...");
	return 0;
}
