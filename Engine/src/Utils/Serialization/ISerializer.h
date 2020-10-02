// ---------------------------------------------------------------------------
// Project Name		:	Neon Donkey
// File Name		:	ISerializer.h
// Author			:	Martin Angulo
// Creation Date	:	2016/09/16
// Purpose			:	ISerializer interface, it defines a number of functions
//						that every Serializer has to implement.(Sometimes we 
//						may not need a function in a certain serializer, just 
//						leave its impleentation empty)
// History			:
// ---------------------------------------------------------------------------
#pragma once
#include "../../Core/Base.h"
#include "../../Core/Rtti.h"
#include "../../Core/DataTypes.h"

namespace Engine
{
	class ISerializer : public IBase
	{
	RTTI_DECL;
	public:
		enum EMode { eRead, eWrite };
	public:
		ISerializer(EMode mode) :mMode(mode){}
		virtual ~ISerializer(){}

		virtual void StreamRead(const char * name, s32 & out) = 0;
		virtual void StreamRead(const char * name, u32 & out) = 0;
		virtual void StreamRead(const char * name, f32 & out) = 0;
		virtual void StreamRead(const char * name, bool & out) = 0;
		virtual void StreamRead(const char * name, std::string & out) = 0;
		//virtual void StreamRead(const char * name, Vec2 & out) = 0;
		//virtual void StreamRead(const char * name, Vec3 & out) = 0;
		//virtual void StreamRead(const char * name, Color & out){}
		//virtual void StreamRead(const char * name, Transform2D & out){}
		//virtual void StreamRead(const char * name, Transform3D & out){}

		virtual void StreamWrite(const char * name, const s32 & out) = 0;
		virtual void StreamWrite(const char * name, const u32 & out) = 0;
		virtual void StreamWrite(const char * name, const f32 & out) = 0;
		virtual void StreamWrite(const char * name, const bool & out) = 0;
		virtual void StreamWrite(const char * name, const std::string & out) = 0;
		//virtual void StreamWrite(const char * name, const Vec2 & out) = 0;
		//virtual void StreamWrite(const char * name, const Vec3 & out) = 0;
		//virtual void StreamWrite(const char * name, const Color & out){}
		//virtual void StreamWrite(const char * name, const Transform2D & out){}
		//virtual void StreamWrite(const char * name, const Transform3D & out){}

		virtual ISerializer* BeginNode(const char * name) = 0;
		virtual void EndNode(ISerializer * secSerializer) = 0;

		virtual ISerializer * FirstChildNode(const char * name = NULL) = 0;
		virtual ISerializer * NextSiblingNode() = 0;
		virtual ISerializer * ParentNode() = 0;

		virtual EMode GetMode()			{ return mMode; }
		virtual void SetMode(EMode mode){ mMode = mode; }

	protected:
		EMode mMode;
	};
}