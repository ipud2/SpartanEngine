/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ==================
#include "IComponent.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"
//=============================

enum Projection
{
	Perspective,
	Orthographic,
};

class __declspec(dllexport) Camera : public IComponent
{
public:
	Camera();
	~Camera();

	/*------------------------------------------------------------------------------
									[INTERFACE]
	------------------------------------------------------------------------------*/
	virtual void Initialize();
	virtual void Update();
	virtual void Serialize();
	virtual void Deserialize();

	/*------------------------------------------------------------------------------
									[MATRICES]
	------------------------------------------------------------------------------*/
	Directus::Math::Matrix GetViewMatrix();
	Directus::Math::Matrix GetProjectionMatrix();
	Directus::Math::Matrix GetPerspectiveProjectionMatrix();
	Directus::Math::Matrix GetOrthographicProjectionMatrix();
	Directus::Math::Matrix GetBaseViewMatrix();

	/*------------------------------------------------------------------------------
									[CONVERSIONS]
	------------------------------------------------------------------------------*/
	Directus::Math::Vector2 WorldSpaceToScreenPoint(Directus::Math::Vector3 point);

	/*------------------------------------------------------------------------------
								[PLANES/PROJECTION]
	------------------------------------------------------------------------------*/
	float GetNearPlane();
	void SetNearPlane(float nearPlane);
	float GetFarPlane();
	void SetFarPlane(float farPlane);
	Projection GetProjection();
	void SetProjection(Projection projection);
	float GetFieldOfView();
	void SetFieldOfView(float fov);

private:
	float m_FOV = 1.04719755f; // 60 degrees
	float m_nearPlane = 0.3f;
	float m_farPlane = 1000.0f;
	Projection m_projection = Perspective;

	Directus::Math::Matrix m_viewMatrix;
	Directus::Math::Matrix m_perspectiveProjectionMatrix;
	Directus::Math::Matrix m_orthographicProjectionMatrix;
	Directus::Math::Matrix m_baseViewMatrix;

	Directus::Math::Vector3 m_position;
	Directus::Math::Quaternion m_rotation;
	bool m_isDirty;

	/*------------------------------------------------------------------------------
									[PRIVATE]
	------------------------------------------------------------------------------*/
	void CalculateViewMatrix();
	void CalculateBaseView();
	void CalculateProjectionMatrix();
};