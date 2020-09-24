/************************************************************************/
/*!
\file	  Texture.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  24/09/2020
\brief  Texture class declaration.

\log    24/09/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include "../Core/Base.h"

namespace Engine
{
  class Texture : public IBase
  {
    RTTI_DECL;
  public:
    Texture(std::string filename);

    u32 GetGLHandle() const { return glHandle_; }

  private:
    u32 glHandle_;
    std::string filename_;
    s32 width_;
    s32 height_;
    s32 nrChannels_;
    u8 data_;
    GLenum type_;
  };
}