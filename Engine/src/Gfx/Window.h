#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/Base.h"
#include "../Core/Rtti.h"

// settings
const u32 WINDOW_WIDTH = 800;
const u32 WINDOW_HEIGHT = 600;

namespace Engine
{
	class Window : public IBase
	{
	RTTI_DECL;
	public:
		void CreateWindow();
		//void ResizeWindow(u32 width = WINDOW_WIDTH, u32 height = WINDOW_HEIGHT);
		
		u32 GetWidth() const;
		void setWidth(u32 width);
		u32 GetHeight() const;
		void setHeight(u32 height);

		GLFWwindow* GetGLFWHandle() { return window_; };
	private:
		GLFWwindow* window_ = nullptr;
		u32 width_ = WINDOW_HEIGHT;
		u32 height_ = WINDOW_HEIGHT;
	};
}
