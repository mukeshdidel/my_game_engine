#include "soulpch.h"
#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace soul {

	Scope<RendererAPI> RenderCommand::s_RendererAPI =  Scope<RendererAPI>(new OpenGLRendererAPI());

}