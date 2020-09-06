#include <iostream>
#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace Engine
{
  RTTI_IMPL(Window, IBase);

  void Window::CreateWindow() {
    //Create window
    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Engine", nullptr, nullptr);
    if (!window_) {
      std::cout << "Failed to create GLFW window." << std::endl;
      glfwTerminate();
    return;
    }
    glfwMakeContextCurrent(window_);
    //Adjust vieport on window resize
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}