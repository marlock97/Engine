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
//STB_IMAGE_IMPLEMENTAION has to be defined EXACTLY 1 time before using stb.
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
#include <map>

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
f64 deltaTime = 0.0f;	// Time between current frame and last frame
f64 lastFrame = 0.0f; // Time of last frame

//Camera
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

//Input
bool firstMouse = true;
f32 lastX = WINDOW_WIDTH / 2.0f;
f32 lastY = WINDOW_HEIGHT / 2.0f;
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos);
void scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset);

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

Material emerald;
Material jade;        
Material obsidian;	  
Material pearl;	      
Material ruby;	      
Material turquoise;	  
Material brass;       
Material bronze;	    
Material chrome;      
Material copper;      
Material gold;	      
Material silver;	    
Material blackPlastic;
Material cyanPlastic; 
Material greenPlastic;
Material redPlastic;
Material whitePlastic;
Material yellowPlastic;
Material blackRubber;
Material cyanRubber;
Material greenRubber; 
Material redRubber;
Material whiteRubber;	
Material yellowRubber;
std::map<std::string, Material> materials;

Light light;

int main()
{
  emerald.ambient = vec3(0.0215f, 0.1745f, 0.0215f);
  emerald.diffuse = vec3(0.07568f, 0.61424f, 0.07568f);
  emerald.specular = vec3(0.633f, 0.727811f, 0.633f);
  emerald.shininess = 0.1f;  
  jade.ambient = vec3(0.135f, 0.222f, 0.1575f);
  jade.diffuse = vec3(0.54f, 0.89f, 0.63f);
  jade.specular = vec3(0.316228f, 0.316228f, 0.316228f);
  jade.shininess = 0.1f;
  obsidian.ambient = vec3(0.05375f, 0.05f, 0.06625f);
  obsidian.diffuse = vec3(0.18275f, 0.17f, 0.22525f);
  obsidian.specular = vec3(0.332741f, 0.328634f, 0.346435f);
  obsidian.shininess = 0.3f;
  pearl.ambient = vec3(0.25f, 0.20725f, 0.20725f);
  pearl.diffuse = vec3(1.0f, 0.829f, 0.829f);
  pearl.specular = vec3(0.296648f, 0.296648f, 0.296648f);
  pearl.shininess = 0.088f;
  ruby.ambient = vec3(0.1745f, 0.01175f, 0.01175f);
  ruby.diffuse = vec3(0.61424f, 0.04136f, 0.04136f);
  ruby.specular = vec3(0.727811f, 0.626959f, 0.626959f);
  ruby.shininess = 0.6f;
  turquoise.ambient = vec3(0.1f, 0.18725f, 0.1745f);
  turquoise.diffuse = vec3(0.396f, 0.74151f, 0.69102f);
  turquoise.specular = vec3(0.297254f, 0.30829f, 0.306678f);
  turquoise.shininess = 0.1f;
  brass.ambient = vec3(0.329412f, 0.223529f, 0.027451f);
  brass.diffuse = vec3(0.780392f, 0.568627f, 0.113725f);
  brass.specular = vec3(0.992157f, 0.941176f, 0.807843f);
  brass.shininess = 0.21794872f;
  bronze.ambient = vec3(0.2125f, 0.1275f, 0.054f);
  bronze.diffuse = vec3(0.714f, 0.4284f, 0.18144f);
  bronze.specular = vec3(0.393548f, 0.271906f, 0.166721f);
  bronze.shininess = 0.2f;
  chrome.ambient = vec3(0.25f, 0.25f, 0.25f);
  chrome.diffuse = vec3(0.4f, 0.4f, 0.4f);
  chrome.specular = vec3(0.774597f, 0.774597f, 0.774597f);
  chrome.shininess = 0.6f;
  copper.ambient = vec3(0.19125f, 0.0735f, 0.0225f);
  copper.diffuse = vec3(0.7038f, 0.27048f, 0.0828f);
  copper.specular = vec3(0.256777f, 0.137622f, 0.086014f);
  copper.shininess = 0.1f;
  gold.ambient = vec3(0.24725f, 0.1995f, 0.0745f);
  gold.diffuse = vec3(0.75164f, 0.60648f, 0.22648f);
  gold.specular = vec3(0.628281f, 0.555802f, 0.366065f);
  gold.shininess = 0.4f;
  silver.ambient = vec3(0.19225f, 0.19225f, 0.19225f);
  silver.diffuse = vec3(0.50754f, 0.50754f, 0.50754f);
  silver.specular = vec3(0.508273f, 0.508273f, 0.508273f);
  silver.shininess = 0.4f;
  blackPlastic.ambient = vec3(0.0f, 0.0f, 0.0f);
  blackPlastic.diffuse = vec3(0.01f, 0.01f, 0.01f);
  blackPlastic.specular = vec3(0.50f, 0.50f, 0.50f);
  blackPlastic.shininess = 0.25f;
  cyanPlastic.ambient = vec3(0.0f, 0.1f, 0.06f);
  cyanPlastic.diffuse = vec3(0.0f, 0.50980392f, 0.50980392f);
  cyanPlastic.specular = vec3(0.50196078f, 0.50196078f, 0.50196078f);
  cyanPlastic.shininess = 0.25f;
  greenPlastic.ambient = vec3(0.0f, 0.0f, 0.0f);
  greenPlastic.diffuse = vec3(0.1f, 0.35f, 0.1f);
  greenPlastic.specular = vec3(0.45f, 0.55f, 0.45f);
  greenPlastic.shininess = 0.25f;
  redPlastic.ambient = vec3(0.0f, 0.0f, 0.0f);
  redPlastic.diffuse = vec3(0.5f, 0.0f, 0.0f);
  redPlastic.specular = vec3(0.7f, 0.6f, 0.6f);
  redPlastic.shininess = 0.25f;
  whitePlastic.ambient = vec3(0.0f, 0.0f, 0.0f);
  whitePlastic.diffuse = vec3(0.55f, 0.55f, 0.55f);
  whitePlastic.specular = vec3(0.70f, 0.70f, 0.70f);
  whitePlastic.shininess = 0.25f; 
  yellowPlastic.ambient = vec3(0.0f, 0.0f, 0.0f);
  yellowPlastic.diffuse = vec3(0.5f, 0.5f, 0.0f);
  yellowPlastic.specular = vec3(0.60f, 0.60f, 0.50f);
  yellowPlastic.shininess = 0.25f;
  blackRubber.ambient = vec3(0.02f, 0.02f, 0.02f);
  blackRubber.diffuse = vec3(0.01f, 0.01f, 0.01f);
  blackRubber.specular = vec3(0.4f, 0.4f, 0.4f);
  blackRubber.shininess = 0.078125f;
  cyanRubber.ambient = vec3(0.0f, 0.05f, 0.05f);
  cyanRubber.diffuse = vec3(0.4f, 0.5f, 0.5f);
  cyanRubber.specular = vec3(0.04f, 0.7f, 0.7f);
  cyanRubber.shininess = 0.078125f;
  greenRubber.ambient = vec3(0.0f, 0.05f, 0.0f);
  greenRubber.diffuse = vec3(0.4f, 0.5f, 0.4f);
  greenRubber.specular = vec3(0.04f, 0.7f, 0.04f);
  greenRubber.shininess = 0.078125f;
  redRubber.ambient = vec3(0.05f, 0.0f, 0.0f);
  redRubber.diffuse = vec3(0.5f, 0.4f, 0.4f);
  redRubber.specular = vec3(0.7f, 0.04f, 0.04f);
  redRubber.shininess = 0.078125f;
  whiteRubber.ambient = vec3(0.05f, 0.05f, 0.05f);
  whiteRubber.diffuse = vec3(0.5f, 0.5f, 0.5f);
  whiteRubber.specular = vec3(0.7f, 0.7f, 0.7f);
  whiteRubber.shininess = 0.078125f;
  yellowRubber.ambient = vec3(0.05f, 0.05f, 0.0f);
  yellowRubber.diffuse = vec3(0.5f, 0.5f, 0.4f);
  yellowRubber.specular = vec3(0.7f, 0.7f, 0.04f);
  yellowRubber.shininess = 0.078125f;

  materials.insert(std::pair<std::string, Material>("Emerald", emerald));
  materials.insert(std::pair<std::string, Material>("Jade", jade));
  materials.insert(std::pair<std::string, Material>("Obsidian", obsidian));
  materials.insert(std::pair<std::string, Material>("Pearl", pearl));
  materials.insert(std::pair<std::string, Material>("Ruby", ruby));
  materials.insert(std::pair<std::string, Material>("Turquoise", turquoise));
  materials.insert(std::pair<std::string, Material>("Brass", brass));
  materials.insert(std::pair<std::string, Material>("Bronze", bronze));
  materials.insert(std::pair<std::string, Material>("Chrome", chrome));
  materials.insert(std::pair<std::string, Material>("Copper", copper));
  materials.insert(std::pair<std::string, Material>("Gold", gold));
  materials.insert(std::pair<std::string, Material>("Silver", silver));
  materials.insert(std::pair<std::string, Material>("BlackPlastic", blackPlastic));
  materials.insert(std::pair<std::string, Material>("CyanPlastic", cyanPlastic));
  materials.insert(std::pair<std::string, Material>("GreenPlastic", greenPlastic));
  materials.insert(std::pair<std::string, Material>("RedPlastic", redPlastic));
  materials.insert(std::pair<std::string, Material>("WhitePlastic", whitePlastic));
  materials.insert(std::pair<std::string, Material>("YellowPlastic", yellowPlastic));
  materials.insert(std::pair<std::string, Material>("BlackRubber", blackRubber));
  materials.insert(std::pair<std::string, Material>("CyanRubber", cyanRubber));
  materials.insert(std::pair<std::string, Material>("GreenRubber", greenRubber));
  materials.insert(std::pair<std::string, Material>("RedRubber", redRubber));
  materials.insert(std::pair<std::string, Material>("WhiteRubber", whiteRubber));
  materials.insert(std::pair<std::string, Material>("YellowRubber", yellowRubber));

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
  Engine::Shader lightBoxVertex("src/Gfx/shaders/LightBox.vert", Engine::Shader::ShaderType::vertex);
  Engine::Shader lightBoxFragment("src/Gfx/shaders/LightBox.frag", Engine::Shader::ShaderType::fragment);
  Engine::ShaderProgram lightBoxShader(lightBoxVertex.GetGLHandle(), lightBoxFragment.GetGLHandle());
  //lightBoxShader.AttachShader(lightBoxVertex);
  //lightBoxShader.AttachShader(lightBoxFragment);
  //lightBoxShader.Link();

  Engine::Shader lightingVertex("src/Gfx/shaders/Lighting.vert", Engine::Shader::ShaderType::vertex);
  Engine::Shader lightingFragment("src/Gfx/shaders/Lighting.frag", Engine::Shader::ShaderType::fragment);
  Engine::ShaderProgram lightingShader(lightingVertex.GetGLHandle(), lightingFragment.GetGLHandle());
  //lightingShader.AttachShader(lightingVertex);
  //lightingShader.AttachShader(lightingFragment);
  //lightingShader.Link();

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
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  //UVs
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
  unsigned int lightCubeVAO;
  glGenVertexArrays(1, &lightCubeVAO);
  glBindVertexArray(lightCubeVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // note that we update the lamp's position attribute's stride to reflect the updated buffer data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  vec3 lightColor(1.0f, 1.0f, 1.0f);
  //vec3 objectColor(1.0f, 0.5f, 0.3f);
  vec3 lightPos(0.0f, 0.0f, 1.0f);
  vec3 objectPos(0.0f, 0.0f, 0.0f);

  Engine::Texture diffuseMap("data/textures/container2.png");
  Engine::Texture specularMap("data/textures/container2_specular.png");
  Engine::Texture emissionMap("data/textures/matrix.jpg");
  lightingShader.Use(); // don't forget to activate/use the shader before setting uniforms!
  lightingShader.SetInt("material.diffuse", 0);
  lightingShader.SetInt("material.specular", 1);
  lightingShader.SetInt("material.emission", 2);

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

    // change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
    //lightPos.x = cos(glfwGetTime());
    //lightPos.y = sin(glfwGetTime());

    lightPos = camera.GetCamPosition() - (camera.GetCamForward() * 2.0f);
    
    //lightColor.x = sin(glfwGetTime() * 2.0f);
    //lightColor.y = sin(glfwGetTime() * 0.7f);
    //lightColor.z = sin(glfwGetTime() * 1.3f);

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
    lightingShader.SetVec3("viewPos", camera.GetCamPosition());
    lightingShader.SetVec3("light.position", lightPos);
    lightingShader.SetFloat("deltaTime", glfwGetTime());

    //Set light
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    lightingShader.SetVec3("light.ambient", ambientColor);
    lightingShader.SetVec3("light.diffuse", diffuseColor);
    lightingShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // view/projection transformations
    mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (f32)window.GetWidth() / (f32)window.GetHeight(), 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    lightingShader.SetMat4("projection", projection);
    lightingShader.SetMat4("view", view);

    mat4 model = mat4(1.0f);
    u32 cubeCounter = 0;
    for(auto& mat : materials) {
      //Set cube material
      Material cubeMaterial = mat.second;
      //lightingShader.SetVec3("material.ambient", cubeMaterial.ambient);
      lightingShader.SetInt("material.diffuse", 0);
      lightingShader.SetInt("material.specular", 1);// cubeMaterial.specular);
      lightingShader.SetFloat("material.shininess", 64.0f);// cubeMaterial.shininess * 128.0);

      // world transformation
      model = mat4(1.0f);
      model = glm::translate(model, objectPos + vec3(2 * cubeCounter, 0.0f, 0.0f));
      lightingShader.SetMat4("model", model);

      //Activate diffuse texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap.GetGLHandle());

      //Activate specular map
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap.GetGLHandle());

      //Activate emission texture
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, emissionMap.GetGLHandle());

      // render the cube
      glBindVertexArray(cubeVAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      ++cubeCounter;
    }

    // also draw the lamp object
    lightBoxShader.Use();
    lightBoxShader.SetVec3("lightColor", lightColor);
    lightBoxShader.SetMat4("projection", projection);
    lightBoxShader.SetMat4("view", view);
    model = mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, vec3(0.2f)); // a smaller cube
    lightBoxShader.SetMat4("model", model);

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

//Cube UVs
//0.0f, 0.0f,
//1.0f, 0.0f,
//1.0f, 1.0f,
//1.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 0.0f,
//
//0.0f, 0.0f,
//1.0f, 0.0f,
//1.0f, 1.0f,
//1.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 0.0f,
//
//1.0f, 0.0f,
//1.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 0.0f,
//1.0f, 0.0f,
//
//1.0f, 0.0f,
//1.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 1.0f,
//0.0f, 0.0f,
//1.0f, 0.0f,
//
//0.0f, 1.0f,
//1.0f, 1.0f,
//1.0f, 0.0f,
//1.0f, 0.0f,
//0.0f, 0.0f,
//0.0f, 1.0f,
//
//0.0f, 1.0f,
//1.0f, 1.0f,
//1.0f, 0.0f,
//1.0f, 0.0f,
//0.0f, 0.0f,
//0.0f, 1.0f