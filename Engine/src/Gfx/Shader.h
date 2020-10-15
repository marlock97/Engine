/************************************************************************/
/*!
\file	  Shader.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  05/09/2020
\brief  Shader class declaration.

\log    05/09/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include "../Core/Base.h"

namespace Engine
{
  class Shader : public IBase
  {
    RTTI_DECL;    
    enum class ShaderType { vertex, fragment, geometry, typeCount };
  private:
    u32 mGLHandle = 0;
    ShaderType mShaderType;
    std::string mShaderString;
    std::string mFilename;

  public:
    Shader(const char* filename, ShaderType shaderType);
    const char* ReadFile(std::string filename);
    void Compile();
    void SetShaderType(ShaderType shadertype, bool setGLHandle);

    std::string GetShaderString() const;
    u32 GetGLHandle() const;
  };
}
