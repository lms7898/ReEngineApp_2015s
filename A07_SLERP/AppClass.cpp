#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - L.A. Stapleford"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 50.0f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//This matrices will hold the relative transformation of the Moon and the Earth
	matrix4 distanceEarth = glm::translate(11.0f, 0.0f, 0.0f);
	matrix4 distanceMoon = glm::translate(2.0f, 0.0f, 0.0f);

	//set start and end rotations, 360 degrees
	glm::quat Start = glm::quat(vector3(0.0f,0.0f,0.0f));
	glm::quat End = glm::quat(vector3(360.0f, 0.0f, 0.0f));

	//amount to rotate sun
	glm::quat sunCurrentTime = glm::mix(Start, End, m_fDay);
	matrix4 m4sunRotate = glm::mat4_cast(sunCurrentTime);

	//rotate sun
	matrix4 m_m4Sun = IDENTITY_M4;
	m_m4Sun = m4sunRotate;

	//scale sun
	m_m4Sun = glm::scale(5.936f, 5.936f, 5.936f);

	//amount to rotate Earth
	glm::quat earthCurrentTime = glm::mix(Start, End, fEarthHalfRevTime);
	matrix4 m4earthRotate = glm::mat4_cast(earthCurrentTime);

	//scale earth
	matrix4 m_m4Earth = IDENTITY_M4;
	m_m4Earth = glm::scale(0.524f, 0.524f, 0.524f);

	//rotate Earth at distance away from sun
	m_m4Earth = m4earthRotate * distanceEarth;

	//amount to rotate
	glm::quat moonCurrentTime = glm::mix(Start, End, fMoonHalfOrbTime);
	matrix4 m4moonRotate = glm::mat4_cast(moonCurrentTime);

	//scale moon
	matrix4 m_m4Moon = IDENTITY_M4;
	m_m4Moon = glm::scale(0.524f, 0.524f, 0.524f) * glm::scale(0.27f, 0.27f, 0.27f);

	//rotate moon at distance away from Earth
	m_m4Moon = m4moonRotate * distanceEarth * distanceMoon;

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	m_fDay += 0.001f;

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//increment earth orbit count
	static int nEarthOrbits;
	if (fRunTime == 0)
	{
		nEarthOrbits = 0;
	}
	else
	{
		//placeholder until Earth orbits
		nEarthOrbits++;
	}

	//increment earth revolutions count
	static int nEarthRevolutions;
	if (fRunTime == 0)
	{
		nEarthRevolutions = 0;
	}
	else
	{
		if (fmod(fEarthHalfRevTime, 0)) //wrong, needs to increment based on live revolutions based on m_fDay...
		{
			nEarthRevolutions++;
		}
	}

	//increment moon orbit count
	static int nMoonOrbits;
	if (fRunTime == 0)
	{
		nMoonOrbits = 0;
	}
	else
	{
		//placeholder until Earth orbits
		nMoonOrbits++;
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}