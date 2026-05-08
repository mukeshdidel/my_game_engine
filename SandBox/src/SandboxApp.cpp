#include <Soul.h>

class Sandbox : public soul::Application
{
public:
	Sandbox()
	{
	}
	~Sandbox()
	{
	}
};

soul::Application* soul::CreateApplication()
{
	return new Sandbox();
}