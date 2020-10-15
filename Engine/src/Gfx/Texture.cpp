/************************************************************************/
/*!
\file	  Texture.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  24/09/2020
\brief  Texture class declaration.

\log    24/09/2020 -> Initial version.
        15/10/2020 -> Changed member variable layout and naming.
*/
/************************************************************************/
#include <iostream>
#include <stb/stb_image.h>
#include "GfxSystem.h"
#include "Texture.h"

namespace Engine
{
  RTTI_IMPL(Texture, IBase);

  Texture::Texture(std::string filename) {
    //Load and create texture
    glGenTextures(1, &mGLHandle);
    glBindTexture(GL_TEXTURE_2D, mGLHandle);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load the data
    unsigned char* data = stbi_load(filename.c_str(), &mWidth, &mHeight, &mNRChannels, 0);

    if (mNRChannels == 1)
      mType = GL_RED;
    else if (mNRChannels == 3)
      mType = GL_RGB;
    else if (mNRChannels == 4)
      mType = GL_RGBA;

    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, mType, mWidth, mHeight, 0, mType, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  }
}