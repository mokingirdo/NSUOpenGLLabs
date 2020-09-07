#include "MaterialDiffuseEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialDiffuseEarth::MaterialDiffuseEarth(TextureFilterMode filterMode)
{
	m_vsFileName = "ShaderDiffuseEarth";
	m_psFileName = "ShaderDiffuseEarth";
	m_filterMode = filterMode;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialDiffuseEarth::Init()
{
	Material::Init();

	map_texture = new Texture2D("Earth_NormalMap.jpg");
	earth_texture = new Texture2D("Earth_Albedo.jpg");
	earth_texture->SetFilterMode(m_filterMode);
	map_texture->SetFilterMode(m_filterMode);

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialDiffuseEarth::Deinit()
{
	Material::Deinit();
}

void MaterialDiffuseEarth::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Matrix4x4 matWorldT			= matWorld.Transpose();
	const Matrix4x4 matWorldNormal		= matWorld.Inverse();

	// Получили список всех источников света в сцене
	std::list<const Light *> lights = SceneUtils::GetLights();
	const size_t count = lights.size() < 3 ? lights.size() : 3;

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderMatrix4x4	("matWorldNormal",	matWorldNormal);
		SetPixelShaderMatrix4x4	("matWorldT",		matWorldT);
		SetPixelShaderVector4	("materialColor",	Vector4(1, 1, 1, 1));
		SetPixelShaderVector4	("lightsCount",		Vector4(count, 1, 1, 1));
		SetPixelShaderTexture2d("map_texture", map_texture);
		SetPixelShaderTexture2d("earth_texture", earth_texture);
		
		// Передаём параметры каждого источника света
		int i = 0;
		std::list<const Light *>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
		{
			const Light * pLight = *iter;
			const Vector4 lightType			= pLight->GetType();
			const Vector4 lightPosition		= Vector4( pLight->GetPosition(), 1 );
			const Vector4 lightDirection	= Vector4( pLight->GetDirection(), 0 );
			const Vector4 lightColor		= pLight->GetColor();
			const Vector4 lightCorner		= Vector4( pLight->GetCorner(), 1);

			// "lights[i]"
			std::string lightStr = "lights[" + std::to_string(static_cast<long long>(i)) + "]";
			std::string cam = "cameraPosition";

			
			// "lights[i].type", "lights[i].position", "lights[i].direction", "lights[i].color"
			SetPixelShaderVector4( (lightStr + ".type").c_str(),		lightType);
			SetPixelShaderVector4( (lightStr + ".position").c_str(),	lightPosition );
			SetPixelShaderVector4( (lightStr + ".direction").c_str(),	lightDirection );
			SetPixelShaderVector4( (lightStr + ".color").c_str(),		lightColor );	
			SetPixelShaderVector4( (lightStr + ".corner").c_str(),		lightCorner);
			SetPixelShaderVector4( (cam).c_str(),						Vector4(0.0f, 0.0f, -7.0f, 0.0f) );

		}

		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
