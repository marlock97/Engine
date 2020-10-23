/************************************************************************/
/*!
\file	  Application.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  23/10/2020
\brief  Application class declaration.

\log    23/10/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include <string>
#include "Base.h"
#include "Rtti.h"

namespace Engine 
{
  class Application : public IBase 
  {
    RTTI_DECL;
  private:
    std::string name_;
  public:
    Application(std::string name, u32 width, u32 height);
    void Run();
    void Initialize();
    void Update();
    void Shutdown();
  };
}
