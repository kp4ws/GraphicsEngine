#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	//Program ID
	unsigned int ID;

	//constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//use/activate shader
	void use();

	//utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, float x, float y) const;
	//TODO: setVec3
	//TODO: setVec4
	//TODO: setMat2
	//TODO: setMat3
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};

#endif