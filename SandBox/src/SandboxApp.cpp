#include <Soul.h>

class ExampleLayer : public soul::Layer
{
	public:
	ExampleLayer() : Layer("Example") {}
	void OnUpdate() override
	{
		SL_INFO("ExampleLayer::Update");
	}
	void OnEvent(soul::Event& event) override
	{
		SL_INFO("{0}", event.ToString());
	}
};

class Sandbox : public soul::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}
};

soul::Application* soul::CreateApplication()
{
	return new Sandbox();
}