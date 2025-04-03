#pragma once

#include <string>
#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>

class shader
{
public:
    // the program ID
    unsigned int id_;

    // constructor reads and builds the shader
    shader() = default;
    shader(const char* vertexPath, const char* fragmentPath);
    ~shader();
    shader(const shader& other);
    shader& operator=(const shader& other);
    // use/activate the shader
    void use();
    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const glm::mat2& value) const;
    void SetMat3(const std::string& name, const glm::mat3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;

    bool operator==(const shader& rhs) const { return id_ == rhs.id_; }
    bool operator!=(const shader& rhs) const { return !(*this == rhs); }

private:
    void CheckCompileErrors(GLuint shader, std::string type);
};
