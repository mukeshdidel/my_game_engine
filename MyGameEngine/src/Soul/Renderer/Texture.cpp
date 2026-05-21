#include "soulpch.h"
#include "Texture.h"

#include "Soul/Core/Core.h"
#include <string>

#include "Soul/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace soul
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		SL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		SL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}