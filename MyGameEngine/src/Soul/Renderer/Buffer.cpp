#include "soulpch.h"
#include "Buffer.h"
#include "Soul/Renderer/Renderer.h"

#include "platform/OpenGL/OpenGLBuffer.h"

namespace soul {
	
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				SL_CORE_ASSERT(false, "Renderer API::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return  CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			SL_CORE_ASSERT(false, "Renderer API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}
	}
	
	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				SL_CORE_ASSERT(false, "Renderer API::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
	}

}