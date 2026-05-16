#include "soulpch.h"
#include "Buffer.h"
#include "Soul/Renderer/Renderer.h"

#include "platform/OpenGL/OpenGLBuffer.h"

namespace soul {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				SL_CORE_ASSERT(false, "Renderer API::None is currently not supported!");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
	}
	
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				SL_CORE_ASSERT(false, "Renderer API::None is currently not supported!");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}
	}

}