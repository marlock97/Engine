/************************************************************************/
/*!
\file	  Base.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  31/08/2020
\brief  IBase class specification.

\log    31/08/2020 -> Initial version.
*/
/************************************************************************/
#include "Base.h"

namespace Engine
{
  RTTI_IMPL_BASE(IBase);

  IBase::IBase() {
  }
  IBase::~IBase() {
  }

  std::string IBase::getName() {
    return mName;
  }
  void IBase::setName(const char* name) {
    mName = name;
  }
  u32 IBase::getUID() const {
    return mUID;
  }

  bool IBase::isExactly(const Rtti& otherType) const {
    return getType().isExactly(otherType);
  }

  bool IBase::isDerived(const Rtti& otherType) const {
    return getType().isDerived(otherType);
  }
  
  bool IBase::isExactly(const IBase& otherObj) const {
    return getType().isExactly(otherObj.getType());
  }

  bool IBase::isDerived(const IBase& otherObj) const {
    return getType().isDerived(otherObj.getType());
  }
}
