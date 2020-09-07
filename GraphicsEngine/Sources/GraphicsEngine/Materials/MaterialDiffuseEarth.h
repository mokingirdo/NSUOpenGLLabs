﻿#pragma once
#include "GraphicsEngine/Materials/Material.h"


// Рассчитывает только компоненту diffuse от всех источников света
class MaterialDiffuseEarth : public Material
{
public:
	MaterialDiffuseEarth(TextureFilterMode filterMode);

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D * map_texture;
	Texture2D *	earth_texture;
	TextureFilterMode m_filterMode;
};
