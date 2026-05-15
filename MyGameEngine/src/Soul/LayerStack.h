#pragma once

#include "Soul/Core.h"
#include "Layer.h"

#include <vector>

namespace soul {
	
	class SOUL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0; 
		// This is an iterator that points to the position where the next layer will be inserted. 
		// It starts at the beginning of the vector and moves forward as layers are added. When an overlay is added, 
		// it is inserted at the position pointed to by m_LayerInsert,
		// and then m_LayerInsert is incremented to point to the next position for the next layer. 
		// When a layer is removed, m_LayerInsert is decremented to point to the previous position for the next layer. 
		// This way, layers are always added before overlays in the vector, and overlays are always added after layers.
	};
}