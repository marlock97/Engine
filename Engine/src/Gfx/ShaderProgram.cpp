#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"

namespace Engine
{
  RTTI_IMPL(ShaderProgram, IBase);

  ShaderProgram::ShaderProgram() {
    SetGLHandle();
  }
  
  ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader) {
    SetGLHandle();
    AttachShader(vertexShader.GetGLHandle());
    AttachShader(fragmentShader.GetGLHandle());
    Link();
  }

  ShaderProgram::ShaderProgram(u32 vertexID, u32 fragmentID) {
    SetGLHandle();
    AttachShader(vertexID);
    AttachShader(fragmentID);
    Link();
  }

  void ShaderProgram::SetGLHandle() {
    glHandle_ = glCreateProgram();
  }

  void ShaderProgram::AttachShader(u32 shaderID) {
    glAttachShader(glHandle_, shaderID);
    shaders_.push_back(shaderID);
  }

  void ShaderProgram::AttachShader(const Shader& shader) {
    glAttachShader(glHandle_, shader.GetGLHandle());
    shaders_.push_back(shader.GetGLHandle());
  }

  void ShaderProgram::Link() {
    glLinkProgram(glHandle_);

    //Check linking
    int  success;
    char infoLog[512];
    success = 0;
    glGetProgramiv(glHandle_, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(glHandle_, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //Delete shader objects
    for(u32 i = 0; i < shaders_.size(); ++i) {
      glDeleteShader(shaders_[i]);
    }
  }

  void ShaderProgram::Use() const {
    glUseProgram(glHandle_);
  }

  void ShaderProgram::SetBool(const std::string& name, bool val) const {
    glUniform1i(glGetUniformLocation(glHandle_, name.c_str()), static_cast<int>(val));
  }
  void ShaderProgram::SetInt(const std::string& name, int val) const {
    glUniform1i(glGetUniformLocation(glHandle_, name.c_str()), val);
  }
  void ShaderProgram::SetFloat(const std::string& name, float val) const {
    glUniform1f(glGetUniformLocation(glHandle_, name.c_str()), val);
  }
  void ShaderProgram::SetVec2(const std::string& name, const vec2& value) const {
    glUniform2fv(glGetUniformLocation(glHandle_, name.c_str()), 1, &value[0]);
  }
  void ShaderProgram::SetVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(glHandle_, name.c_str()), x, y);
  }
  void ShaderProgram::SetVec3(const std::string& name, const vec3& value) const {
    glUniform3fv(glGetUniformLocation(glHandle_, name.c_str()), 1, &value[0]);
  }
  void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(glHandle_, name.c_str()), x, y, z);
  }
  void ShaderProgram::SetVec4(const std::string& name, const vec4& value) const {
    glUniform4fv(glGetUniformLocation(glHandle_, name.c_str()), 1, &value[0]);
  }
  void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(glHandle_, name.c_str()), x, y, z, w);
  }
  void ShaderProgram::SetMat2(const std::string& name, const mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(glHandle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void ShaderProgram::SetMat3(const std::string& name, const mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(glHandle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void ShaderProgram::SetMat4(const std::string& name, const mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(glHandle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
}
