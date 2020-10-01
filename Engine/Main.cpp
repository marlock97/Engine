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
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //Remove console window, more info: https://learnopengl.com/Getting-started/Creating-a-window
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>
#include <fstream>

#include "src/Gfx/GfxSystem.h"
#include "src/Gfx/Shader.h"
#include "src/Gfx/ShaderProgram.h"
#include "src/Gfx/Window.h"
#include "src/Gfx/Texture.h"
#include "src/Gfx/Camera.h"

/*TODO:
 *   -Add Texture class.
 */

//Time
f32 deltaTime = 0.0f;	// Time between current frame and last frame
f32 lastFrame = 0.0f; // Time of last frame

//Camera
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
f32 lastX = WINDOW_WIDTH / 2.0f;
f32 lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

//Input
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos);
void scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset);

int main()
{
  //Init
  Engine::GfxSystem gfx;
  gfx.Initialize();
  stbi_set_flip_vertically_on_load(true);
  Engine::Window window;
  window.CreateWindow();
  gfx.InitGLAD();
  glEnable(GL_DEPTH_TEST);
  
  //Input
  glfwSetInputMode(window.GetGLFWHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window.GetGLFWHandle(), mouse_callback);
  glfwSetScrollCallback(window.GetGLFWHandle(), scroll_callback);

  //Graphics
  Engine::Shader vertexShader("src/Gfx/shaders/vertex.shader", Engine::Shader::ShaderType::vertex);
  Engine::Shader fragmentShader("src/Gfx/shaders/fragment.shader", Engine::Shader::ShaderType::fragment);
  
  Engine::ShaderProgram shaderProgram;
  shaderProgram.SetGLHandle();
  shaderProgram.AttachShader(vertexShader);
  shaderProgram.AttachShader(fragmentShader);
  shaderProgram.Link();
  
  /*
  //Vertex data
  float vertices[] = {
      //Position          //Color           //Texture coords
       0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left 
  };

  unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
  };
  */

  // set up vertex data (and buffer(s)) and configure vertex attributes
  f32 cubeVtx[] = {
      //Position          //Color           //Texture coords
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  // world space positions of our cubes
  vec3 cubePositions[] = {
      vec3(0.0f,  0.0f,  0.0f),
      vec3(2.0f,  5.0f, -15.0f),
      vec3(-1.5f, -2.2f, -2.5f),
      vec3(-3.8f, -2.0f, -12.3f),
      vec3(2.4f, -0.4f, -3.5f),
      vec3(-1.7f,  3.0f, -7.5f),
      vec3(1.3f, -2.0f, -2.5f),
      vec3(1.5f,  2.0f, -2.5f),
      vec3(1.5f,  0.2f, -1.5f),
      vec3(-1.3f,  1.0f, -1.5f)
  };

  //Create VBO, VAO, EBO
  u32 VBO, VAO;//, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  //glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVtx), cubeVtx, GL_STATIC_DRAW);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);

  /*
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  */

  Engine::Texture texture0("data/textures/container.jpg");
  Engine::Texture texture1("data/textures/awesomeface.png");

  /*
  //Load and create texture
  unsigned int texture0, texture1;

  //Texture 1
  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and generate the texture
  int width, height, nrChannels;

  unsigned char* data = stbi_load("data/textures/container.jpg", &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  //Texture 2
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and generate the texture
  data = stbi_load("data/textures/awesomeface.png", &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  */

  shaderProgram.Use(); // don't forget to activate/use the shader before setting uniforms!
  shaderProgram.SetInt("texture0", 0);
  shaderProgram.SetInt("texture1", 1);

  //Render loop
  while (!glfwWindowShouldClose(window.GetGLFWHandle())) {
    
    //Time
    f64 currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //Input
    processInput(window.GetGLFWHandle());

    //Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Textures
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture0.GetGLHandle());
    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture1.GetGLHandle());

    //Activate shaderProgram
    shaderProgram.Use();

    //Create transformations
    // pass projection matrix to shader (note that in this case it could change every frame)
    mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (f32)WINDOW_WIDTH / (f32)WINDOW_HEIGHT, 0.1f, 100.0f);
    shaderProgram.SetMat4("projection", projection);

    // camera/view transformation
    mat4 view = camera.GetViewMatrix();
    shaderProgram.SetMat4("view", view);

    //Render boxes
    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time 

    //glDrawArrays(GL_TRIANGLES, 0, 36);

    for (u32 i = 0; i < 10; i++)
    {
      // calculate the model matrix for each object and pass it to shader before drawing
      glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shaderProgram.SetMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //Check events and swap buffers
    glfwSwapBuffers(window.GetGLFWHandle());
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //glDeleteBuffers(1, &EBO);
  //glDeleteProgram(shaderProgram.GetGLHandle());

  //Terminate glfw
  glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos)
{
  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  f32 xoffset = xpos - lastX;
  f32 yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
  camera.ProcessMouseScroll(yoffset);
}