#pragma once

#ifdef SL_PLATFORM_WINDOWS

extern soul::Application* soul::CreateApplication();

int main(int argc, char** argv)
{
	auto app = soul::CreateApplication();
	app->Run();
	delete app;
}

#endif
