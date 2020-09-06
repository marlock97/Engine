#pragma once
#include <vector>
#include "../Core/Base.h"
#include "../Core/Rtti.h"
#include "Shader.h"

namespace Engine
{
  class ShaderProgram : public IBase
  {
    RTTI_DECL;
    public:
      void SetGLHandle();
      void AttachShader(Shader shader);
      void Link();
      
      u32 GetGLHandle() { return glHandle_; };
    private:
    u32 glHandle_ = 0;
    std::vector<u32> shaders_;
  };
}