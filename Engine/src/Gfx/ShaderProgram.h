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
      void AttachShader(u32 shader);
      void AttachShader(const Shader& shader);
      void Link();
      void Use() const;
      
      void SetBool(const std::string& name, bool val) const;
      void SetInt(const std::string& name, int val) const;
      void SetFloat(const std::string& name, float val) const;

      u32 GetGLHandle() const { return glHandle_; };
    private:
    u32 glHandle_ = 0;
    std::vector<u32> shaders_;
  };
}