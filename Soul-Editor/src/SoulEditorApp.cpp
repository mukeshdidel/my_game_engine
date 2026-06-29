#include <Soul.h>
#include <Soul/Core/EntryPoint.h>

#include "EditorLayer.h"


namespace soul {

	class SoulEditor : public Application
	{
	public:
		SoulEditor() 
			: Application("Soul Editor")
		{
			PushLayer(new EditorLayer());
		}
		~SoulEditor() {

		}

	private:

	};

	Application* CreateApplication() {
		return new SoulEditor();
	}
}


