#include <iostream>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

namespace Engine
{
  RTTI_IMPL(Shader, IBase);

  Shader::Shader(const char* filename, ShaderType shaderType = ShaderType::vertex) : filename_(filename), shaderType_(shaderType) {
    SetShaderType(shaderType, true);
    ReadFile(filename);
    Compile();
  }

  const char* Shader::ReadFile(std::string filename) {  
    std::ifstream shader(filename);

    if (shader.is_open()) {
      getline(shader, shaderString_, '\0');
    }
    shader.close();

    return shaderString_.c_str();
  }

  void Shader::Compile() {
    const char* buffer;
    if(shaderString_.empty())
      buffer = ReadFile(filename_);
    else
      buffer = shaderString_.c_str();

    glShaderSource(glHandle_, 1, &buffer, NULL);
    glCompileShader(glHandle_);
    //Check vertex shader compilation
    int  success;
    char infoLog[512];
    glGetShaderiv(glHandle_, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(glHandle_, 512, NULL, infoLog);
      switch (shaderType_) {
      case ShaderType::vertex:
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        break;
      case ShaderType::fragment:
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        break;
      case ShaderType::geometry:
        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        break;
      default:
        return;
      }
    }
  }
  
  void Shader::SetShaderType(ShaderType shaderType, bool createGLHandle) {
    shaderType_ = shaderType;

    if(createGLHandle) {
      switch (shaderType) {
      case ShaderType::vertex:
        glHandle_ = glCreateShader(GL_VERTEX_SHADER);
        break;
      case ShaderType::fragment:
        glHandle_ = glCreateShader(GL_FRAGMENT_SHADER);
        break;
      case ShaderType::geometry:
        glHandle_ = glCreateShader(GL_GEOMETRY_SHADER);
        break;
      default:
        return;
      }
    }
  }

  std::string Shader::GetShaderString() const {
    return shaderString_;
  }

  u32 Shader::GetShaderHandle() const {
    return glHandle_; 
  };
}
