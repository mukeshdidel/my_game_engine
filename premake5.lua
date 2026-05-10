workspace "MyGameEngine"
	architecture "x64"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MyGameEngine"
	location "MyGameEngine"
	kind "SharedLib"
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
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SL_PLATFORM_WINDOWS",
			"SL_BUILD_DLL"
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
		symbols "On"
	filter "configurations:Release"
		defines "SL_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "SL_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
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
		"MyGameEngine/src"
	}

	links
	{
		"MyGameEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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
		symbols "On"
	filter "configurations:Release"
		defines "SL_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "SL_DIST"
		optimize "On"