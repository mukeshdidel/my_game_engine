#include "soulpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace soul {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		SL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // what it does ? 
		// Glad is a library that loads OpenGL function pointers at runtime. 
		// Since OpenGL functions are not directly linked to your application, 
		// you need to load them before you can use them. gladLoadGLLoader is the function that performs this loading process. 
		// It takes a function pointer (in this case, glfwGetProcAddress) that it uses to retrieve the addresses of the OpenGL functions. 
		// If the loading is successful, it returns a non-zero value; otherwise, it returns zero.
		SL_CORE_ASSERT(status, "Failed to initialize Glad!");

	}


	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}