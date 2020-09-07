#pragma once
#include "GraphicsEngineImpl.h"


class GraphicsEngineContext
{
public:
	GraphicsEngineContext(GraphicsEngineImpl * pImpl)
		: m_pImpl(pImpl)
	{
	
	}

	GraphicsEngineImpl * m_pImpl;
};
