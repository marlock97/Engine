/************************************************************************/
/*!
\file	  System.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  05/09/2020
\brief  IBase class declaration.

\log    05/09/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include "Base.h"
#include "Rtti.h"

namespace Engine
{
  class ISystem : IBase
  {
    RTTI_DECL;
  public:
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
  };
}
