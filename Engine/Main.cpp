/************************************************************************/
/*!
\file	Main.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	26/08/2020
\brief  Main script

\log  26/08/2020 -> Initial version
*/
/************************************************************************/
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") Remove console window
//More info: https://learnopengl.com/Getting-started/Creating-a-window
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/Gfx/GfxSystem.h"
#include "src/Gfx/Shader.h"
#include "src/Gfx/ShaderProgram.h"
#include "src/Gfx/Window.h"

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
/*
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
*/

int main()
{
  Engine::GfxSystem gfx;
  gfx.Initialize();
  Engine::Window window;
  window.CreateWindow();
  gfx.InitGLAD();
  /*
  //Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //Create window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
  if(!window)
  {
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  //Adjust vieport on window resize
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  /*
  //Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  */
  Engine::Shader vertexShader("src/Gfx/shaders/vertex.shader", Engine::Shader::ShaderType::vertex);
  Engine::Shader fragmentShader("src/Gfx/shaders/fragment.shader", Engine::Shader::ShaderType::fragment);
  /*
  //Create vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  //Check vertex shader compilation
  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  //Check fragment shader compilation
  success = 0;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  */
  Engine::ShaderProgram shaderProgram;
  shaderProgram.SetGLHandle();
  shaderProgram.AttachShader(vertexShader);
  shaderProgram.AttachShader(fragmentShader);
  shaderProgram.Link();
  /*
  //Create shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  //Link shaders
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  //Check linking
  success = 0;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  //Delete shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  */
  //Vertex data
  float vertices[] = {
      //Position          //Color
       0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
  };
  unsigned int indices[] = {
          0, 1, 3,  // first Triangle
          1, 2, 3   // second Triangle
  };
  //Create VBO, VAO, EBO
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //Texture loading
  int width, height, nrChannels;
  //unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

  //Render loop
  while (!glfwWindowShouldClose(window.GetGLFWHandle()))
  {
    //Input  
    processInput(window.GetGLFWHandle());

    //Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw our first triangle
    shaderProgram.Use();

    //Dynamic color change using uniform
    /*
    f32 deltaTime = glfwGetTime();
    f32 colorValR = (sin(deltaTime) / 2.0f) + 0.5f;
    f32 colorValG = (sin(deltaTime + 1.0f) / 2.0f) + 0.5f;
    f32 colorValB = (sin(deltaTime + 2.0f) / 2.0f) + 0.5f;
    s32 vertexColorLocation = glGetUniformLocation(shaderProgram.GetGLHandle(), "vertexColor");
    glUniform4f(vertexColorLocation, colorValR, colorValG, colorValB, 1.0);
    */
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time 

    //Check events and swap buffers
    glfwSwapBuffers(window.GetGLFWHandle());
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram.GetGLHandle());

  //Terminate glfw
  glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
*/