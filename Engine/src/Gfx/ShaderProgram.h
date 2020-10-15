/************************************************************************/
/*!
\file	  ShaderProgram.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  24/09/2020
\brief  ShaderProgram class declaration.

\log    15/10/2020 -> Changed member variable layout and naming.
*/
/************************************************************************/
#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Base.h"
#include "../Core/Rtti.h"
#include "Shader.h"

namespace Engine
{
  class ShaderProgram : public IBase
  {
    RTTI_DECL;
  private:
    u32 mGLHandle = 0;
    std::vector<u32> mShaders;

  public:
    ShaderProgram();
    ShaderProgram(Shader vertexShader, Shader fragmentShader);
    ShaderProgram(u32 vertexID, u32 fragmentID);

    void SetGLHandle();
    void AttachShader(u32 shader);
    void AttachShader(const Shader& shader);
    void Link();
    void Use() const;
    
    void SetBool(const std::string& name, bool val) const;
    void SetInt(const std::string& name, int val) const;
    void SetFloat(const std::string& name, float val) const;
    void SetVec2(const std::string& name, const vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const mat2& mat) const;
    void SetMat3(const std::string& name, const mat3& mat) const;
    void SetMat4(const std::string& name, const mat4& mat) const;

    u32 GetGLHandle() const { return mGLHandle; };
  };
}