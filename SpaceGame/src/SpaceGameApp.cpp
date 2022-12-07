#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "SpaceGame.h"


class Sandbox : public Hazel::Application
{
public:
	Sandbox(const Hazel::ApplicationSpecification& specification)
		: Hazel::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new SpaceGame());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication(Hazel::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Space Game";
	spec.WorkingDirectory = "../Hazelnut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}
