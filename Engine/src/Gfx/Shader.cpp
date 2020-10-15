/************************************************************************/
/*!
\file	  Shader.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  05/09/2020
\brief  Shader class implementation.

\log    05/09/2020 -> Initial version.
*/
/************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

namespace Engine
{
  RTTI_IMPL(Shader, IBase);

  Shader::Shader(const char* filename, ShaderType shaderType = ShaderType::vertex) : mFilename(filename), mShaderType(shaderType) {
    SetShaderType(shaderType, true);
    ReadFile(filename);
    Compile();
  }

  const char* Shader::ReadFile(std::string filename) {  
    std::ifstream shader(filename);

    if (shader.is_open()) {
      getline(shader, mShaderString, '\0');
    }
    shader.close();

    return mShaderString.c_str();
  }

  void Shader::Compile() {
    const char* buffer;
    if(mShaderString.empty())
      buffer = ReadFile(mFilename);
    else
      buffer = mShaderString.c_str();

    glShaderSource(mGLHandle, 1, &buffer, NULL);
    glCompileShader(mGLHandle);
    //Check vertex shader compilation
    int  success;
    char infoLog[512];
    glGetShaderiv(mGLHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(mGLHandle, 512, NULL, infoLog);
      switch (mShaderType) {
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
    mShaderType = shaderType;

    if(createGLHandle) {
      switch (shaderType) {
      case ShaderType::vertex:
        mGLHandle = glCreateShader(GL_VERTEX_SHADER);
        break;
      case ShaderType::fragment:
        mGLHandle = glCreateShader(GL_FRAGMENT_SHADER);
        break;
      case ShaderType::geometry:
        mGLHandle = glCreateShader(GL_GEOMETRY_SHADER);
        break;
      default:
        return;
      }
    }
  }

  std::string Shader::GetShaderString() const {
    return mShaderString;
  }

  u32 Shader::GetGLHandle() const {
    return mGLHandle;
  }
}
