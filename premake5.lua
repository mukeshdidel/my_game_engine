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


include "MyGameEngine/vendor/GLFW"
include "MyGameEngine/vendor/Glad"


project "MyGameEngine"
	location "MyGameEngine"
	kind "SharedLib"
	staticruntime "Off"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	pchheader "soulpch.h"
	pchsource "MyGameEngine/src/soulpch.cpp"
	 

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
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
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "SL_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "SL_DIST"
		buildoptions "/MD"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "Off"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"MyGameEngine/vendor/spdlog/include",
		"MyGameEngine/src",
		"MyGameEngine/vendor"
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
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "SL_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "SL_DIST"
		buildoptions "/MD"
		optimize "On"