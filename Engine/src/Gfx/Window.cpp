#include <iostream>
#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace Engine
{
  RTTI_IMPL(Window, IBase);

  void Window::CreateWindow() {
    //Create window
    mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Engine", nullptr, nullptr);
    if (!mWindow) {
      std::cout << "Failed to create GLFW window." << std::endl;
      glfwTerminate();
    return;
    }
    glfwMakeContextCurrent(mWindow);
    //Adjust vieport on window resize
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
  }
  
  u32 Window::GetWidth() const {
    return mWidth;
  }

  void Window::setWidth(u32 width) {
    mWidth = width;
  }

  u32 Window::GetHeight() const {
    return mHeight;
  }

  void Window::setHeight(u32 height) {
    mHeight = height;
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}