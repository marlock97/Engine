/************************************************************************/
/*!
\file	  JSONSerializer.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  01/09/2020
\brief  JSON serialization.

\log    01/09/2020 -> Initial version.
*/
/************************************************************************/
#pragma once
#include <list>
#include <Json/json.h>
#include "../ISerializer.h" //Serializer Interface

//#pragma warning (disable:4251) // dll and STL
namespace Engine
{

	class JSONSerializer : public ISerializer
	{
		RTTI_DECL;
	public:
		JSONSerializer(EMode mode, JSONSerializer * parent = NULL);
		virtual ~JSONSerializer();

		virtual void StreamRead(const char * name, s32 & out);
		virtual void StreamRead(const char * name, u32 & out);
		virtual void StreamRead(const char * name, f32 & out);
		virtual void StreamRead(const char * name, bool & out);
		virtual void StreamRead(const char * name, std::string & out);
		virtual void StreamRead(const char * name, vec2 & out);
		virtual void StreamRead(const char * name, vec3 & out);
		//virtual void StreamRead(const char * name, Color & out);
		//virtual void StreamRead(const char * name, Transform2D & out);
		//virtual void StreamRead(const char * name, Transform3D & out);

		virtual void StreamWrite(const char * name, const s32 & in);
		virtual void StreamWrite(const char * name, const u32 & in);
		virtual void StreamWrite(const char * name, const f32 & in);
		virtual void StreamWrite(const char * name, const bool & in);
		virtual void StreamWrite(const char * name, const std::string & in);
		virtual void StreamWrite(const char * name, const vec2 & in);
		virtual void StreamWrite(const char * name, const vec3 & in);
		//virtual void StreamWrite(const char * name, const Color & in);
		//virtual void StreamWrite(const char * name, const Transform2D & in);
		//virtual void StreamWrite(const char * name, const Transform3D & in);

		virtual ISerializer * BeginNode(const char * name);
		virtual void EndNode(ISerializer * secSerializer);

		virtual ISerializer * FirstChildNode(const char * name = NULL);
		virtual ISerializer * NextSiblingNode();
		virtual ISerializer * ParentNode();

		/// \fn		LoadFile
		/// \brief	Opens a text file and reads all the data from it. 
		bool LoadFile(const char * filename);

		/// \fn		ReloadFile
		/// \brief	Re-Opens the preivous text file associted and 
		///			reads all the data from it.
		void ReloadFile();

		/// \fn		WriteToFile
		/// \brief	Writes the data stored in mSource to the provided
		///			text file.
		void WriteToFile(const char * filename = NULL);

		// --------------------------------------------------------------------
		// XML specific

		/// \fn		GetRootSerializer
		/// \brief	Walks up the hierachy to the root serialzier and returns it.
		JSONSerializer * GetRootSerializer();

	protected:
		std::string mFileName;	// text file associated with this serializer
		Json::Value mValue;

		JSONSerializer * mParentSerializer;
		std::list<JSONSerializer *> mChildNodes;
		void DeleteChildNodes();

		// friend class for re-creating the hierarchy when loading an json
		friend void ReadJSONChildNodesRec(JSONSerializer * parent);
	};
}