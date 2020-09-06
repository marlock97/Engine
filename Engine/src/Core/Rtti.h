/************************************************************************/
/*!
\file	  Rtti.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  31/08/2020
\brief  Run-time type information, provides methods for class identificantion
        and comparison. Every class in the Engine needs to include the macro 
        at the bottom.

\log    31/08/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include <memory>
#include <string>

class Rtti
{
public:
  Rtti(const char* name, const Rtti* baseType);
  const char* getName() const;

  bool isExactly(const Rtti& otherType) const;
  bool isDerived(const Rtti& otherType) const;

private:
  std::string name_;
  const Rtti* baseType_ = nullptr;
};

#define RTTI_DECL											\
	public:															\
		static const Rtti TYPE;									\
		virtual const Rtti& GetType() const						\
		{															\
			return TYPE;											\
		}	

#define RTTI_IMPL_BASE(thisType)							\
	const Rtti thisType::TYPE = Rtti(typeid(thisType).name(), NULL);	\

#define RTTI_IMPL(thisType, parentType)							\
	const Rtti thisType::TYPE = Rtti(typeid(thisType).name(), &parentType::TYPE);	\
