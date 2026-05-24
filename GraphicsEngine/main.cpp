#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n" //specify a color output to the fragment shader
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n" //input variable from vertexShader (gets connected in programShader linking)
"void main()\n"
"{\n"
"	FragColor = vertexColor;\n"
"}\0";

const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = ourColor;\n"
"}\0";

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

	//Create shader object
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//Check if shader compilation successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//create fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	//Check if shader compilation successful
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, nullptr);
	glCompileShader(fragmentShaderYellow);

	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderYellow, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Shader program (link all shaders together)
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check if shader program failed
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//After shader objects have been linked, they can be safely deleted
	//glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShaderYellow);
	glLinkProgram(shaderProgram2);

	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderYellow);

	//Setup vertex data
	//x, y, z
	float vertices[] = {
		//First triangle
		0.45f, 0.5f, 0.0f, // Top
		0.9f, -0.5f, 0.0f, //Bottom right
		0.0f, -0.5f, 0.0f, //Bottom left
	};

	float verticesYellow[] = {
		//Second triangle
		-0.45f, 0.5f, 0.0f, // Top
		0.0f, -0.5f, 0.0f, //Bottom right
		-0.9f, -0.5f, 0.0f, //Bottom left
	};

	unsigned int indices[] = {
		0, 1, 3, //First triangle
		1, 2, 3 //Second triangle
	};

	//vertex buffer object (VBO)
	unsigned int VBOs[2], VAOs[2];// , EBO;
	glGenVertexArrays(2, VAOs); //Generate a VAO and give ID
	//generate buffer ID
	glGenBuffers(2, VBOs);
	//glGenBuffers(1, &EBO);

	//Bind Vertex Array Object (VAO)
	glBindVertexArray(VAOs[0]);

	//bind the buffer (ARRAY_BUFFER for VBOs)
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//copy vertex data into memory (copies user defined data into currently bound buffer)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since the position of the triangle isn't going to move, and is used alot, thus is static_draw.

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Link vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Tells VAO how to interpret raw vertex data
	glEnableVertexAttribArray(0); //Enable vertex attribute so it gets used in rendering

	//unbind stuff
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesYellow), verticesYellow, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind stuff
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Render loop (iterations = frames)
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Sets color used when clearing the screen
		glClear(GL_COLOR_BUFFER_BIT); //Clears screen with the set clear color

		float timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0f + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glUseProgram(shaderProgram2);

		//draw first triangle
		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAOs[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//draw second triangle
		//glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//check & call events & swap buffers
		glfwSwapBuffers(window); //Swaps front and back buffers to display the rendered frame
		glfwPollEvents();//Checks for any events (IO, etc)
	}

	//Deallocate resources
	glDeleteVertexArrays(2, VAOs); //frees VAO memory
	glDeleteBuffers(2, VBOs); //frees VBO memory
	//glDeleteBuffers(1, &EBO); //frees EBO memory
	glDeleteProgram(shaderProgram); //frees shader program memory
	glDeleteProgram(shaderProgram2);

	glfwTerminate();
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
}