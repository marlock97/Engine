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
  
  u32 Window::GetWidth() const {
    return width_;
  }

  void Window::setWidth(u32 width) {
    width_ = width;
  }

  u32 Window::GetHeight() const {
    return height_;
  }

  void Window::setHeight(u32 height) {
    height_ = height;
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}