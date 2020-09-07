#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"


class CameraController : public Component
{
	Vector3 mousePos;
	Vector3 mousePosPrev;
	Object *parrent;

	bool isInitialized = false;

public:
	CameraController()
	{
		parrent = new Object();

		mousePos		= Vector3::Zero();
		mousePosPrev	= Vector3::Zero();
	}

	virtual ~CameraController() {}

	virtual void Update() 
	{
		Transform * pTransform = m_pObject->m_pTransform;

		if (!isInitialized)
		{
			Vector3 pos = pTransform->GetPosition();

			parrent->m_pTransform = new Transform(pos, pTransform->GetEulerAngles());
			pos = parrent->m_pTransform->GetPosition();

			pTransform->SetLocalPosition(Vector3(0, 0, 0));
			pTransform->SetParent(parrent->m_pTransform);
			isInitialized = true;
		}

		Transform *parentTransform = parrent->m_pTransform;
		
		// Camera Translation
		{
			Vector3 forward	= pTransform->GetForward();
			Vector3 right	= pTransform->GetRight();
			double dt = Time::GetDeltaTime();

			const double speed = 1.0;
			Vector3 direction;

			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				direction += forward;
			}
			else if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				direction -= forward;
			}
			else if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
			{
				direction += right;
			}
			else if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
			{
				direction -= right;
			}
			// TODO : Task08

			parentTransform->Translate( speed * dt * direction );
		}

		// Camera Rotation
		{
			mousePos = Input::GetMousePosition();

			// TODO : Task08
			if (mousePosPrev.x != 0 || mousePosPrev.y != 0)
			{
				Vector3 angles = pTransform->GetEulerAngles();
				double x = mousePos.x;
				double y = mousePos.y;

				parentTransform->Rotate(0,-(mousePosPrev.x - x),0);

				int angle = (int)abs(angles.y) % 360;

				if(abs(angles.x - (mousePosPrev.y - y)) <= 90)
					if (angle < 90 || angle >= 270)
					{
						pTransform->Rotate(-(mousePosPrev.y - y), 0, 0);
					}
					else
					{
						pTransform->Rotate((mousePosPrev.y - y), 0, 0);
					}
			}
			mousePosPrev = mousePos;
		}
	}
};
