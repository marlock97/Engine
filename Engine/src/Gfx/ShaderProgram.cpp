#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"

namespace Engine
{
  RTTI_IMPL(ShaderProgram, IBase);

  void ShaderProgram::SetGLHandle() {
    glHandle_ = glCreateProgram();
  }

  void ShaderProgram::AttachShader(u32 shaderID) {
    glAttachShader(glHandle_, shaderID);
    shaders_.push_back(shaderID);
  }

  void ShaderProgram::AttachShader(const Shader& shader) {
    glAttachShader(glHandle_, shader.GetShaderHandle());
    shaders_.push_back(shader.GetShaderHandle());
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

  void ShaderProgram::SetBool(const std::string& name, bool val) const {
    glUniform1i(glGetUniformLocation(glHandle_, name.c_str()), static_cast<int>(val));
  }

  void ShaderProgram::SetInt(const std::string& name, int val) const {
    glUniform1i(glGetUniformLocation(glHandle_, name.c_str()), val);
  }

  void ShaderProgram::SetFloat(const std::string& name, float val) const {
    glUniform1f(glGetUniformLocation(glHandle_, name.c_str()), val);
  }
  
  void ShaderProgram::Use() const {
    glUseProgram(glHandle_);
  }
}
