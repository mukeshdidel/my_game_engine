#include "soulpch.h"
#include "FrameBuffer.h"

#include "Soul/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace soul {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFrameBuffer>(spec);
		}

		SL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}