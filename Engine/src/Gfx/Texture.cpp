/************************************************************************/
/*!
\file	  Texture.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  24/09/2020
\brief  Texture class declaration.

\log    24/09/2020 -> Initial version.
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
    glGenTextures(1, &glHandle_);
    glBindTexture(GL_TEXTURE_2D, glHandle_);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load the data
    unsigned char* data = stbi_load(filename.c_str(), &width_, &height_, &nrChannels_, 0);

    if (nrChannels_ == 1)
      type_ = GL_RED;
    else if (nrChannels_ == 3)
      type_ = GL_RGB;
    else if (nrChannels_ == 4)
      type_ = GL_RGBA;

    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, type_, width_, height_, 0, type_, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  }
}