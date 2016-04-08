#include "MyCamera.h"
//Repo link: https://github.com/lms7898/ReEngineApp_2015s




//get view matrix from singleton
matrix4 MyCamera::GetViewMatrix(void)
{
	//move m_m4View to the what the camera sees
	//matrix4 tranformations = glm::toMat4(quaternerizor);
	m_m4View = glm::toMat4(quaternerizor);
	//tranformations = glm::translate(tranformations, -camPosition);
	m_m4View = glm::translate(m_m4View, -camPosition);
	//m_m4View = tranformations;
	return m_m4View;
}

//get projection matrix from singleton and change camera mode
matrix4 MyCamera::GetProjection(bool bOrthographic)
{
	if (bOrthographic == true)
	{
		m_nMode = CAMERAMODE::CAMROTHOZ;
		//copied from ICE10
		m_m4Projection = glm::ortho(
			-10.0f,//left
			10.0f,//right
			-10.0f,//bottom
			10.0f,//top
			0.01f,//near
			1000.0f//far
			);
	}
	else
	{
		m_nMode = CAMERAMODE::CAMPERSP;
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f); //copied from ICE10
	}

	return m_m4Projection;
}

void MyCamera::SetPosition(glm::vec3 InPos)
{
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
	camPosition += camUp * fIncrement;
}

void MyCamera::ChangePitch(float fIncrement) {
	rotate(fIncrement, glm::vec3(1.0f, 0.0f, 0.0f));
}

void  MyCamera::ChangeYaw(float fIncrement) {
	rotate(fIncrement, glm::vec3(0.0f, 1.0f, 0.0f));
}

void  MyCamera::ChangeRoll(float fIncrement) {
	rotate(fIncrement, glm::vec3(0.0f, 0.0f, 1.0f));
}

/*
//change camera pitch
void MyCamera::ChangePitch(float fIncrement)
{
	m_v3Forward.x *= fIncrement;
	camUp.x *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, camUp);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}

//change camera roll
void MyCamera::ChangeRoll(float fIncrement)
{
	m_v3Forward.z *= fIncrement;
	camUp.z *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, camUp);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}

//change camera yaw
void MyCamera::ChangeYaw(float fIncrement)
{
	m_v3Forward.y *= fIncrement;
	camUp.y *= fIncrement;

	glm::quat qQuaternion1 = glm::angleAxis(180.0f, m_v3Forward);
	glm::quat qQuaternion2 = glm::angleAxis(180.0f, camUp);

	camPosition += glm::mat4_cast(qQuaternion1);
	camPosition += glm::mat4_cast(qQuaternion2);
}
*/

