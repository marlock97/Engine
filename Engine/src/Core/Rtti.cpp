/************************************************************************/
/*!
\file	  Rtti.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  31/08/2020
\brief  Run-time type information, provides methods for class identificantion
        and comparison.

\log    31/08/2020 -> Initial version.
*/
/************************************************************************/
#include <typeinfo>
#include "Rtti.h"

namespace Engine
{
  //! Rtti custom constructor
  /*!
    \param name Type name name of the class
    \param pbaseType Rtti type pointer of the base class
  */
  Rtti::Rtti(std::string name, const Rtti* baseType) : name_(name), baseType_(baseType) {
    //Remove class substring
    name_ = name_.substr(name_.find_first_of(" ") + 1);
  }

  //! Name getter
  /*!
    \return The name of the class
  */
  std::string Rtti::getName() const {
    return name_;
  }
  
  //! Comparison method
  /*!
    \param otheType Type to compare with
    \return True if the type is the same
  */
  bool Rtti::isExactly(const Rtti& otherType) const {
    return this == &otherType;
  }

  //! Checks inheritance
  /*!
    \param otheType Type to check
    \return True if the type is derived
  */
  bool Rtti::isDerived(const Rtti& otherType) const {
    const Rtti* it = this;
    while(it) { 
      if(it == &otherType) {
        return true;
      }
      it  = it->baseType_;
    }
    return false;
  }
}
