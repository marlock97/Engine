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

  void ShaderProgram::AttachShader(Shader shader) {
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
}
