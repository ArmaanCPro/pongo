#include "shader.h"

#include <fstream>
#include <sstream>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(shaders);

namespace Utility
{
	// internal linkage is intentional. shader.cpp should be the only file even using this function for now
	static std::string remove_bom(const std::string& str)
	{
		if (str.size() >= 3 && 
			static_cast<unsigned char>(str[0]) == 0xEF &&
			static_cast<unsigned char>(str[1]) == 0xBB &&
			static_cast<unsigned char>(str[2]) == 0xBF) {
			return str.substr(3); // Skip the BOM
		}
		return str;
	}
}

shader::shader(const char* vertexPath, const char* fragmentPath)
{
	// retrive the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	auto vshaderFile = cmrc::shaders::get_filesystem().open(vertexPath);
	auto fshaderFile = cmrc::shaders::get_filesystem().open(fragmentPath);
	try
	{
		std::string vshaderSource(vshaderFile.begin(), vshaderFile.end());
	    std::string fshaderSource(fshaderFile.begin(), fshaderFile.end());

		vertexCode = Utility::remove_bom(vshaderSource);
		fragmentCode = Utility::remove_bom(fshaderSource);
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
	}
	const char* vshaderCode = vertexCode.c_str();
	const char* fshaderCode = fragmentCode.c_str();

	// declare shaders
	unsigned int vertex, fragment;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vshaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fshaderCode, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");

	// shader program
	id_ = glCreateProgram();
	glAttachShader(id_, vertex);
	glAttachShader(id_, fragment);
	glLinkProgram(id_);
	CheckCompileErrors(id_, "PROGRAM");

	// delete the shaders as they're linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

shader::~shader()
{
	glDeleteProgram(id_);
}

shader::shader(const shader& other)
{
	id_ = other.id_;
}

shader& shader::operator=(const shader& other)
{
	if (*this == other)
		return *this;

	id_ = other.id_;
	return *this;
}

void shader::use()
{
	glUseProgram(id_);
}

void shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}

void shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(id_, name.c_str()), x, y);

}

void shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}

void shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z);
}

void shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}

void shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id_, name.c_str()), x, y, z, w);
}

void shader::SetMat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void shader::SetMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void shader::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
