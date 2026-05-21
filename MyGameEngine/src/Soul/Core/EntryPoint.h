#pragma once

#ifdef SL_PLATFORM_WINDOWS

extern soul::Application* soul::CreateApplication();

int main(int argc, char** argv)
{
		
	soul::Log::Init();
	SL_CORE_INFO("Initialized Core Log!");
	SL_INFO("Hello! This is an info log.");

	auto app = soul::CreateApplication();
	app->Run();
	delete app;
}

#endif
