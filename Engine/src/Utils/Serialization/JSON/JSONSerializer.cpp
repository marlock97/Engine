/************************************************************************/
/*!
\file	  JSONSerializer.cpp
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  01/09/2020
\brief  JSON serialization.

\log    01/09/2020 -> Initial version.
*				02/10/2020 -> Added vec2 and vec3.
*/
/************************************************************************/
#include "JSONSerializer.h"
#include <iostream>
#include <fstream>

#ifndef FOR_EACH
#define FOR_EACH(itName, container)												\
		for(auto itName = (container).begin(); itName != (container).end(); ++itName)	
#endif

namespace Engine
{
	RTTI_IMPL(JSONSerializer, ISerializer);

	JSONSerializer::JSONSerializer(ISerializer::EMode mode, JSONSerializer * parent) : ISerializer(mode), mParentSerializer(parent){
	}

	JSONSerializer::~JSONSerializer() {
		DeleteChildNodes();
	}

	void JSONSerializer::StreamRead(const char * name, s32 & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isInt())
				out = childNode->mValue.asInt();
		}
	}

	void JSONSerializer::StreamRead(const char * name, u32 & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isUInt())
				out = childNode->mValue.asUInt();
		}
	}

	void JSONSerializer::StreamRead(const char * name, f32 & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isDouble())
				out = childNode->mValue.asFloat();
		}
	}

	void JSONSerializer::StreamRead(const char * name, bool & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isBool())
				out = childNode->mValue.asBool();
		}
	}

	void JSONSerializer::StreamRead(const char * name, std::string & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isString())
				out = childNode->mValue.asString();
		}
	}
	
	void JSONSerializer::StreamRead(const char * name, vec2 & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isObject()) {
				out.x = static_cast<float>(childNode->mValue.get("x", mValue).asDouble());
				out.y = static_cast<float>(childNode->mValue.get("y", mValue).asDouble());
			}
		}
	}

	void JSONSerializer::StreamRead(const char * name, vec3 & out) {
		FOR_EACH(child, mChildNodes) {
			JSONSerializer * childNode = *child;
			if (childNode->name_ == name && childNode->mValue.isObject()) {
				out.x = static_cast<float>(childNode->mValue.get("x", mValue).asDouble());
				out.y = static_cast<float>(childNode->mValue.get("y", mValue).asDouble());
				out.z = static_cast<float>(childNode->mValue.get("z", mValue).asDouble());
			}
		}
	}
	/*
	void JSONSerializer::StreamRead(const char * name, Transform2D & out)
	{
		FOR_EACH(child, mChildNodes)
		{
			JSONSerializer * childNode = *child;
			if (childNode->mName == name && childNode->mValue.isObject())
			{
				Vec2 position;
				childNode->StreamRead("Translation", position);
				out.SetPosition(position);

				Vec2 scale;
				childNode->StreamRead("Scale", scale);
				out.SetScale(scale);

				float orientation;
				childNode->StreamRead("Orientation", orientation);
				out.SetRotationAngle(orientation);
			}
		}
	}
	*/
	void JSONSerializer::StreamWrite(const char * name, const s32 & in) {
		mValue[name] = in;
	}

	void JSONSerializer::StreamWrite(const char * name, const u32 & in) {
		mValue[name] = in;
	}

	void JSONSerializer::StreamWrite(const char * name, const f32 & in) {
		mValue[name] = in;
	}

	void JSONSerializer::StreamWrite(const char * name, const bool & in) {
		mValue[name] = in;
	}

	void JSONSerializer::StreamWrite(const char * name, const std::string & in) {
		mValue[name] = in;
	}
	
	void JSONSerializer::StreamWrite(const char * name, const vec2 & in) {
		mValue[name]["x"] = in.x;
		mValue[name]["y"] = in.y;
	}

	void JSONSerializer::StreamWrite(const char * name, const vec3 & in) {
		mValue[name]["x"] = in.x;
		mValue[name]["y"] = in.y;
		mValue[name]["z"] = in.z;
	}
	/*
	void JSONSerializer::StreamWrite(const char * name, const Transform2D & in) {
		mValue[name]["Translation"]["x"] = in.GetPosition().x;
		mValue[name]["Translation"]["y"] = in.GetPosition().y;

		mValue[name]["Scale"]["x"] = in.GetScale().x;
		mValue[name]["Scale"]["y"] = in.GetScale().y;

		mValue[name]["Orientation"] = in.GetRotation();
	}
	*/


	ISerializer * JSONSerializer::BeginNode(const char * name) {
		JSONSerializer * newNode = new JSONSerializer(mMode, this);
		newNode->setName(name);
		mChildNodes.push_back(newNode);
		return newNode;
	}

	void JSONSerializer::EndNode(ISerializer * secSerializer) {
		FOR_EACH(it, mChildNodes)
			mValue[(*it)->getName()] = (*it)->mValue;
	}

	ISerializer * JSONSerializer::FirstChildNode(const char * name) {
		// NO CHILDREN NODESS
		if (mChildNodes.empty())
			return NULL;

		// no name was provided -> return the first
		if (name == NULL)
			return *mChildNodes.begin();

		// name exists -> find the node in the list
		FOR_EACH(nodeIt, mChildNodes) {
			// name is found
			if ((*nodeIt)->name_ == name)
				return *nodeIt;
		}

		// done
		return NULL;
	}

	ISerializer * JSONSerializer::NextSiblingNode() {
		// root node -> no sibling
		if (mParentSerializer == NULL)
			return NULL;

		// find ourselves
		auto it = mParentSerializer->mChildNodes.begin();
		for (; it != mParentSerializer->mChildNodes.end(); ++it) {
			// we found ourselves, get next
			if (*it == this) {
				// increment iterator
				++it;

				// warning: it's possible for us to be 
				// the last node, in this case, return NULL.
				if (it == mParentSerializer->mChildNodes.end())
					return NULL;
				// Everything is fine, just return the next
				// node.
				else
					return *it;
			}
		}

		// we shouldn't get here...
		//DebugAssert(false, "something horribly wrong has happened");
		return NULL;
	}

	ISerializer * JSONSerializer::ParentNode() {
		if (mParentSerializer)
			return mParentSerializer;
		else
			return this;
	}

	void ReadJSONChildNodesRec(JSONSerializer * parent) {
		using namespace std;
		// get the values
		for (Json::Value::iterator it = parent->mValue.begin(); it != parent->mValue.end(); ++it) {
			JSONSerializer * newNode = new JSONSerializer(parent->GetMode(), parent);
			newNode->setName(it.key().asCString());
			newNode->mValue = *it;
			parent->mChildNodes.push_back(newNode);

			// read if necessary
			if (it->type() == Json::ValueType::objectValue)
				ReadJSONChildNodesRec(newNode);
		}
	}

	/// \fn		LoadFile
	/// \brief	Opens a text file and reads all the data from it. 
	bool JSONSerializer::LoadFile(const char * filename) {
		if (!filename)
			return false;

		if (!mFileName.empty())
			mFileName.erase();

		mFileName = filename;
		std::ifstream is(mFileName);

		if (is.is_open()) {
			Json::CharReaderBuilder jsonReader;
			std::string errs;
			if (!Json::parseFromStream(jsonReader, is, &mValue, &errs)) {
				//for some reason it always fails to parse
				std::cout << "Failed to parse configuration\n";
			}
			ReadJSONChildNodesRec(this);
			is.close();

			return true;
		}

		return false;
	}

	/// \fn		ReloadFile
	/// \brief	Re-Opens the previous text file associted and 
	///			reads all the data from it.
	void JSONSerializer::ReloadFile() {
		if (!mFileName.empty())
			LoadFile(mFileName.c_str());
	}

	/// \fn		WriteToFile
	/// \brief	Writes the data stored in mSource to the provided
	///			text file.
	void JSONSerializer::WriteToFile(const char * filename) {
			Json::StreamWriterBuilder builder;
			std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
			std::ofstream outputFileStream(filename);
			writer->write(mValue, &outputFileStream);
	}

	// --------------------------------------------------------------------
	// XML specific

	/// \fn		GetRootSerializer
	/// \brief	Walks up the hierachy to the root serialzier and returns it.
	JSONSerializer * JSONSerializer::GetRootSerializer() {
		// walk up
		JSONSerializer * pNode = this;
		while (pNode->mParentSerializer)
			pNode = pNode->mParentSerializer;

		// this is the node that doesn't have a parent.
		return pNode;
	}

	void JSONSerializer::DeleteChildNodes() {
		// delete the children
		FOR_EACH(it, mChildNodes)
			delete *it;
		mChildNodes.clear();
	}
}