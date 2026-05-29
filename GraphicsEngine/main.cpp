#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

float mixValue = 0.2f;

int main() {
	//Init & Configure GLFW (OpenGL version 3.3, core profile)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window Creation
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//Register resize callback function
	//**Callback functions should be registered after window is created and before render loop is initialized**
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD (loads all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	//Build and compile our shader
	Shader ourShader("shader.vert", "shader.frag");

	//float vertices[] = {
	//	//First Triangle
	//	//Positions(x,y,z) //Colors
	//	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Top
	//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//Bottom right
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,//Bottom left
	//};

	//float vertices[] = {
	//	//positions(x,y,z)	//colors(R,G,B)		//texture coords(S,T)
	//	0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	2.0f, 2.0f,		//top right
	//	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	2.0f, 0.0f,		//bottom right
	//	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//bottom left
	//	-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 2.0f,		//top left
	//};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//vertex buffer object (VBO)
	unsigned int VBOs[2], VAOs[2];//, EBOs[2];
	glGenVertexArrays(2, VAOs); //Generate a VAO and give ID
	//generate buffer ID
	glGenBuffers(2, VBOs);
	//glGenBuffers(1, EBOs);

	//Bind Vertex Array Object (VAO)
	glBindVertexArray(VAOs[0]);

	//bind the buffer (ARRAY_BUFFER for VBOs)
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//copy vertex data into memory (copies user defined data into currently bound buffer)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since the position of the triangle isn't going to move, and is used alot, thus is static_draw.

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//Link vertex attributes
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Tells VAO how to interpret raw vertex data
	glEnableVertexAttribArray(0); //Enable vertex attribute so it gets used in rendering

	////color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	////unbind stuff
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//load & create texture
	unsigned int textures[2];
	glGenTextures(2, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);

	//texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, numberOfColorChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("container.jpg", &width, &height, &numberOfColorChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);

	//texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &numberOfColorChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture2", 1);

	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Render loop (iterations = frames)
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Sets color used when clearing the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears screen with the set clear color

		//bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		ourShader.setFloat("mixValue", mixValue);

		//create transformations
		//glm::mat4 trans = glm::mat4(1.0f);
		////trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

		ourShader.use();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		/*unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "t/*ransform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/


		//render container
		glBindVertexArray(VAOs[0]);

		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*float timeValue = glfwGetTime();
		float xOffset = static_cast<float>(sin(timeValue) / 2.0f);
		ourShader.setFloat("xOffset", xOffset);*/

		//check & call events & swap buffers
		glfwSwapBuffers(window); //Swaps front and back buffers to display the rendered frame
		glfwPollEvents();//Checks for any events (IO, etc)
	}

	//Deallocate resources
	glDeleteVertexArrays(2, VAOs); //frees VAO memory
	glDeleteBuffers(2, VBOs); //frees VBO memory
	//glDeleteBuffers(1, EBOs); //frees EBO memory

	glfwTerminate();

	//Initial vector
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

	////1. Start with identity matrix
	//glm::mat4 trans = glm::mat4(1.0f);
	//
	////2. Apply transformations (scale, rotate, translate) to identity matrix (becomes transformation matrix)
	////**NOTE** Because matrix multiplication is not communative (AB !+ BA), transformation order matters.
	//trans = glm::scale(trans, glm::vec3(2.0f));
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	////3. Multiply transformation matrix with vector
	//vec = trans * vec; //Output vector after applying transformation matrix
	//
	//std::cout << vec.x << vec.y << vec.z << std::endl;

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//First two params are lower left corner of window. Third and fourth are wdith and height in px (we set equal to GLFW's window size)
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (mixValue >= 1.0f) return;
		mixValue += 0.001f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (mixValue <= 0.0f) return;
		mixValue -= 0.001f;
	}
}