#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/System.h"
#include "ShaderProgram.h"

namespace Engine
{
  class GfxSystem : public ISystem
  {
  RTTI_DECL;
  public:
    void Initialize();
    void Update();
    void Shutdown();

    void InitGLAD();

  private:
    ShaderProgram* shaderProgram_ = nullptr;
  };
}
