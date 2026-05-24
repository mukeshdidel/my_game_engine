#pragma once

#ifdef SL_PLATFORM_WINDOWS

extern soul::Application* soul::CreateApplication();

int main(int argc, char** argv)
{
		
	soul::Log::Init();

	SL_PROFILE_BEGIN_SESSION("Startup", "SoulProfile-Startup.json");
	auto app = soul::CreateApplication();
	SL_PROFILE_END_SESSION();

	SL_PROFILE_BEGIN_SESSION("Runtime", "SoulProfile-Runtime.json");
	app->Run();
	SL_PROFILE_END_SESSION();

	SL_PROFILE_BEGIN_SESSION("Shutdown", "SoulProfile-Shutdown.json");
	delete app;
	SL_PROFILE_END_SESSION();
}

#endif
