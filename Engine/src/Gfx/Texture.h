/************************************************************************/
/*!
\file	  Texture.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  24/09/2020
\brief  Texture class declaration.

\log    24/09/2020 -> Initial version.
        15/10/2020 -> Changed member variable layout and naming.
*/
/************************************************************************/
#pragma once
#include "../Core/Base.h"

namespace Engine
{
  class Texture : public IBase
  {
    RTTI_DECL;
  private:
    u32 mGLHandle;
    s32 mWidth;
    s32 mHeight;
    s32 mNRChannels;
    GLenum mType;
    std::string mFilename;
    u8 mData;

  public:
    Texture(std::string filename);

    u32 GetGLHandle() const { return mGLHandle; }
  };
}