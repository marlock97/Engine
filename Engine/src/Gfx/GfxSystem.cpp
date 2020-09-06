#include <iostream>
#include "GfxSystem.h"

namespace Engine
{
  RTTI_IMPL(GfxSystem, ISystem);

  void GfxSystem::Initialize() {
    //Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
  }

  void GfxSystem::Update() {

  }

  void GfxSystem::Shutdown() {

  } 

  void GfxSystem::InitGLAD() {
    //Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
    }
  }
}
  