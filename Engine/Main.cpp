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
  
  //Input
  glfwSetInputMode(window.GetGLFWHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window.GetGLFWHandle(), mouse_callback);
  glfwSetScrollCallback(window.GetGLFWHandle(), scroll_callback);

  //Graphics
  Engine::Shader lightingVertex("src/Gfx/shaders/LightBox.vertex", Engine::Shader::ShaderType::vertex);
  Engine::Shader lightingFragment("src/Gfx/shaders/LightBox.fragment", Engine::Shader::ShaderType::fragment);
  //Engine::ShaderProgram lightingShader(lightingVertex.getUID(), lightingFragment.getUID());
  Engine::ShaderProgram lightingShader;
  lightingShader.AttachShader(lightingVertex);
  lightingShader.AttachShader(lightingFragment);
  lightingShader.Link();

  Engine::Shader colorVertex("src/Gfx/shaders/ColorBox.vertex", Engine::Shader::ShaderType::vertex);
  Engine::Shader colorFragment("src/Gfx/shaders/ColorBox.fragment", Engine::Shader::ShaderType::fragment);
  Engine::ShaderProgram colorShader;
  colorShader.AttachShader(colorVertex);
  colorShader.AttachShader(colorFragment);
  colorShader.Link();

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
      //Position          
      -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  //1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,
                            //
      -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  //0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
                            //
      -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
                            //
       0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
                            //
      -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  //1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
                            //
      -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  //0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f   //0.0f, 1.0f
  };

  // world space positions of our cubes
  /*
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
  */
  /*
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);
  */
  /*Pos-Col-UVs
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  */

  //Engine::Texture texture0("data/textures/container.jpg");
  //Engine::Texture texture1("data/textures/awesomeface.png");
  //shaderProgram.Use(); // don't forget to activate/use the shader before setting uniforms!
  //shaderProgram.SetInt("texture0", 0);
  //shaderProgram.SetInt("texture1", 1);

  // first, configure the cube's VAO (and VBO)
  unsigned int VBO, cubeVAO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVtx), cubeVtx, GL_STATIC_DRAW);

  glBindVertexArray(cubeVAO);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);

  // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
  unsigned int lightCubeVAO;
  glGenVertexArrays(1, &lightCubeVAO);
  glBindVertexArray(lightCubeVAO);

  // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);

  vec3 lightColor(1.0f, 1.0f, 1.0f);
  vec3 objectColor(1.0f, 0.5f, 0.31f);
  vec3 lightPos(1.2f, 1.0f, 2.0f);

  //Render loop
  while (!glfwWindowShouldClose(window.GetGLFWHandle())) {
    
    //Time
    f64 currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //Input
    processInput(window.GetGLFWHandle());

    //Render
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Textures
    //glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    //glBindTexture(GL_TEXTURE_2D, texture0.GetGLHandle());
    //glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    //glBindTexture(GL_TEXTURE_2D, texture1.GetGLHandle());

    //Activate shaderProgram

    //Create transformations
    // pass projection matrix to shader (note that in this case it could change every frame)
    //mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (f32)WINDOW_WIDTH / (f32)WINDOW_HEIGHT, 0.1f, 100.0f);
    //shaderProgram.SetMat4("projection", projection);
    // camera/view transformation
    //mat4 view = camera.GetViewMatrix();
    //shaderProgram.SetMat4("view", view);

    //Render boxes
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time 

    //glDrawArrays(GL_TRIANGLES, 0, 36);

    /*
    for (u32 i = 0; i < 10; i++) {
      // calculate the model matrix for each object and pass it to shader before drawing
      mat4 model = mat4(1.0f); // make sure to initialize matrix to identity matrix first
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
      shaderProgram.SetMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    */

    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader.Use();
    lightingShader.SetVec3("objectColor", objectColor);
    lightingShader.SetVec3("lightColor", lightColor);

    // view/projection transformations
    mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (f32)WINDOW_WIDTH / (f32)WINDOW_HEIGHT, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    lightingShader.SetMat4("projection", projection);
    lightingShader.SetMat4("view", view);

    // world transformation
    mat4 model = mat4(1.0f);
    lightingShader.SetMat4("model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // also draw the lamp object
    colorShader.Use();
    colorShader.SetMat4("projection", projection);
    colorShader.SetMat4("view", view);
    model = mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, vec3(0.2f)); // a smaller cube
    colorShader.SetMat4("model", model);

    //Render light object
    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Check events and swap buffers
    glfwSwapBuffers(window.GetGLFWHandle());
    glfwPollEvents();
  }
  
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteVertexArrays(1, &lightCubeVAO);
  glDeleteBuffers(1, &VBO);
  //glDeleteBuffers(1, &EBO);
  //glDeleteProgram(shaderProgram.GetGLHandle());

  //Terminate glfw
  glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
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
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::UP, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.ProcessKeyboard(Engine::Camera::CameraMovement::DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
  if (firstMouse) {
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

void scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset) {
  camera.ProcessMouseScroll(yoffset);
}