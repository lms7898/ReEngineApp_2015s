#pragma once

#include <SFML\Graphics.hpp>
#include "RE\ReEngAppClass.h"

using namespace ReEng;

class MyCamera
{
public:
	static MyCamera& getInstance()
	{
		static MyCamera    instance;
		return instance;
	}

	/* DELETE THIS?
	glm::mat4x4 CameraTransform;
	glm::vec3 target;
	glm::vec3 forward;

	void MyCamera::initVariables();
	*/

	//glm::mat4 camTransMat;
	glm::vec3 camPosition;
	glm::vec3 camTarget;
	glm::vec3 camUp;
	CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP;
	matrix4 m_m4View = matrix4(1.0f);
	matrix4 m_m4Projection = matrix4(1.0f);
	glm::vec3 m_v3Forward;
	glm::vec3 m_v3Rightward;
	glm::vec3 m_v3Upward;


	matrix4 GetViewMatrix(void);

	matrix4 GetProjection(bool bOrthographic);

	void MyCamera::SetPosition(glm::vec3 InPos);

	void MyCamera::SetTarget(glm::vec3 InTarget);

	void MyCamera::SetUp(glm::vec3 InUp);

	void MyCamera::MoveForward(float fIncrement);

	void MyCamera::MoveSideways(float fIncrement);

	void MyCamera::MoveVertical(float fIncrement);

	void MyCamera::ChangePitch(float fIncrement);

	void MyCamera::ChangeRoll(float fIncrement);

	void MyCamera::ChangeYaw(float fIncrement);

	/*
	glm::mat4x4 MyCamera::getPosition();

	void MyCamera::rotatePositiveX();
	*/
private:
	MyCamera() {}
	MyCamera(MyCamera const&);       // Don't Implement
	void operator=(MyCamera const&); // Don't implement

};