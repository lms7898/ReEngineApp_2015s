#include "MyCamera.h"


//get view matrix from singleton
matrix4 MyCamera::GetViewMatrix(void)
{
	return m_m4View;
}

//get projection matrix from singleton and change camera mode
matrix4 MyCamera::GetProjection(bool bOrthographic)
{
	if (bOrthographic == true)
	{
		m_nMode = CAMERAMODE::CAMROTHOZ;
	}
	else
	{
		m_nMode = CAMERAMODE::CAMPERSP;
	}

	return m_m4Projection;
}

void MyCamera::SetPosition(glm::vec3 InPos)
{
	//this should tranform the cameras transformation m4 by translating to the in vector
	//glm::translate(camTransMat, InPos);

	//this should set the camera's position property to the input position vector
	camPosition = InPos;
}

void MyCamera::SetTarget(glm::vec3 InTarget)
{
	//glm::lookAt(camPosition, center, );
	//this should set the camera's target to the in target
	camTarget = InTarget;
}

void MyCamera::SetUp(glm::vec3 InUp)
{
	//this should set the camera's up vector to the input up vector
	camUp = InUp;
}

//move camera forward
void MyCamera::MoveForward(float fIncrement)
{
	camPosition += m_v3Forward * fIncrement;
}

//move camera sideways
void MyCamera::MoveSideways(float fIncrement)
{
	camPosition += m_v3Rightward * fIncrement;
}

//move camera up or down
void MyCamera::MoveVertical(float fIncrement)
{
	camPosition += m_v3Upward * fIncrement;
}

//change camera pitch
void MyCamera::ChangePitch(float fIncrement)
{
	m_v3Forward.x *= fIncrement;
	m_v3Upward.x *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, m_v3Upward);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}

//change camera roll
void MyCamera::ChangeRoll (float fIncrement)
{
	m_v3Forward.z *= fIncrement;
	m_v3Upward.z *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, m_v3Upward);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}

//change camera yaw
void MyCamera::ChangeYaw(float fIncrement)
{
	m_v3Forward.y *= fIncrement;
	m_v3Upward.y *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, m_v3Upward);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}
