/************************************************************************/
/*!
\file	  Rtti.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  31/08/2020
\brief  IBase class declaration.

\log    31/08/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include <string>
#include "DataTypes.h"
#include "Rtti.h"

namespace Engine
{
  class IBase
  {
  public:
    static const Rtti TYPE;
    virtual const Rtti& getType() const { return TYPE; }

    bool isExactly(const Rtti& otherType) const;
    bool isDerived(const Rtti& otherType) const;
    bool isExactly(const IBase& otherObj) const;
    bool isDerived(const IBase& otherObj) const;

    std::string getName();
    void setName(const char* name);
    u32 getUID() const;

  protected:
    std::string name_;
    u32 UID_ = 0;
    IBase();
    virtual ~IBase() = 0;
  };
}