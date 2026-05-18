#include "soulpch.h"
#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace soul {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}