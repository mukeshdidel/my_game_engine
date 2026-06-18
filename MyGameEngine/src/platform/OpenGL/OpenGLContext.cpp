#include "soulpch.h"
#include "OpenGLContext.h"
#include "Soul/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

namespace soul {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		SL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		SL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // what it does ? 
		// Glad is a library that loads OpenGL function pointers at runtime. 
		// Since OpenGL functions are not directly linked to your application, 
		// you need to load them before you can use them. gladLoadGLLoader is the function that performs this loading process. 
		// It takes a function pointer (in this case, glfwGetProcAddress) that it uses to retrieve the addresses of the OpenGL functions. 
		// If the loading is successful, it returns a non-zero value; otherwise, it returns zero.
		SL_CORE_ASSERT(status, "Failed to initialize Glad!");


		std::cout << "OpenGL Info:" << std::endl;
		std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

	}


	void OpenGLContext::SwapBuffers()
	{

		SL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}