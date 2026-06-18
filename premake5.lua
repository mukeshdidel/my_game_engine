workspace "MyGameEngine"
	architecture "x64"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MyGameEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MyGameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MyGameEngine/vendor/imgui"
IncludeDir["glm"] = "MyGameEngine/vendor/glm"
IncludeDir["stb_image"] = "MyGameEngine/vendor/stb_image"


include "MyGameEngine/vendor/GLFW"
include "MyGameEngine/vendor/Glad"
include "MyGameEngine/vendor/imgui"


project "MyGameEngine"
	location "MyGameEngine"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	pchheader "soulpch.h"
	pchsource "MyGameEngine/src/soulpch.cpp"
	 

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		
		"%{prj.name}/vendor/stb_image/stb_image.h",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SL_PLATFORM_WINDOWS",
			"SL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		buildoptions 
		{ 
			"/utf-8" 
		}

	filter "configurations:Debug"
		defines "SL_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "SL_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "SL_DIST"
		runtime "Release"
		optimize "on"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	includedirs
	{
		"MyGameEngine/vendor/spdlog/include",
		"MyGameEngine/src",
		"MyGameEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"MyGameEngine"
	}

	filter "system:windows"
		cppdialect "C++17"

		systemversion "latest"

		defines
		{
			"SL_PLATFORM_WINDOWS"
		}
		
		buildoptions 
		{ 
			"/utf-8" 
		}

	filter "configurations:Debug" 
		defines "SL_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "SL_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "SL_DIST"
		runtime "Release"
		optimize "on"