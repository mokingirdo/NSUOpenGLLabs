#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/FpsCounter.h"
#include "Tasks/ObjectRotator.h"

#include <ctime>
#include <stdio.h>
/**
* @brief Shows how to write text to the screen.
* Key code is situated in the classes FpsCounter, GUI, InternalGUI, DX9GUI, GL20GUI.
*/
class Task03: public Task
{
public:
	virtual ~Task03() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 3, -10), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );
			for(int j = 0; j < 50; j++)
			for (int i = 0; i < 10; i++)
			{
				Object * pObject = new Object();
				pObject->m_pTransform = new Transform(Vector3(10.- 2*i, 0, -10 + 2 * j), Vector3(0, 30, 0));
				pObject->m_pMesh = new MeshCube(10);
				pObject->m_pMaterial = new MaterialUnlitSimple();

				scene.AddObject(pObject);
			}
			scene.SetCamera( pCamera );
		}	


		
		// FPS counter
		{
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform();
			pObject->AddComponent( new FpsCounter() );

			scene.AddObject( pObject );
		}
	}

	virtual void Update()
	{
		
	}

};
