#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment 06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	//define locations walleye should move to
	locations[0] = vector3(-4.0f, -2.0f, 5.0f);
	locations[1] = vector3(1.0f, -2.0f, 5.0f);
	locations[2] = vector3(-3.0f, -1.0f, 3.0f);
	locations[3] = vector3(2.0f, -1.0f, 3.0f);
	locations[4] = vector3(-2.0f, 0.0f, 0.0f);
	locations[5] = vector3(3.0f, 0.0f, 0.0f);
	locations[6] = vector3(-1.0f, 1.0f, -3.0f);
	locations[7] = vector3(4.0f, 1.0f, -3.0f);
	locations[8] = vector3(0.0f, 2.0f, -5.0f);
	locations[9] = vector3(5.0f, 2.0f, -5.0f);
	locations[10] = vector3(1.0f, 3.0f, -5.0f);

	//code for generating spheres - same as in E06
	m_nObjects = 11;

	m_pSphere = new PrimitiveClass[m_nObjects];
	m_pMatrix = new matrix4[m_nObjects];

	vector3 v3Start;
	vector3 v3End;

	for (int i = 0; i < 11; i++)
	{
		if (i != 11)
		{
			v3Start = locations[i];
			v3End = locations[i + 1];
		}
		else
		{
			v3Start = locations[i];
			v3End = locations[0];
		}

		m_pSphere[i].GenerateSphere(0.1f, 5, RERED);
		vector3 v3Current = glm::lerp(v3Start, v3End, 1.0f);
		m_pMatrix[i] = glm::translate(v3Current);
	}
	
}

void AppClass::Update(void)
{
#pragma region Do not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	//start point and end point
	vector3 v3Start;
	vector3 v3End;

	//loop through locations
	for (int i = 0; i < 11; i++)
	{
		//adjust start and end points to each location
		if (i != 11)
		{
			v3Start = locations[i];
			v3End = locations[i + 1];
		}
		else
		{
			v3Start = locations[i];
			v3End = locations[0];
		}

		//set the model
		m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");

		//adjust fPercent
		float fPercent = MapValue(
			static_cast<float>(i),			//value to change
			0.0f,							//original min
			10.0f,							//original max
			0.0f,							//new min
			static_cast<float>(fRunTime)	//new max - based on time?
			);

		//lerp the v3Current vector
		vector3 v3Current = glm::lerp(v3Start, v3End, fPercent);

		//translate the model
		IDENTITY_M4 = glm::translate(v3Current);
	}


#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
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

	matrix4 mProjection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 mView = m_pCameraMngr->GetViewMatrix();

	for (uint i = 0; i < m_nObjects; i++)
	{
		m_pSphere[i].Render(mProjection, mView, m_pMatrix[i]);
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (m_pSphere != nullptr)
	{
		delete[] m_pSphere; //new[]->delete[], new()->delete
		m_pSphere = nullptr;
	}

	if (m_pMatrix != nullptr)
	{
		delete[] m_pMatrix; //new[]->delete[], new()->delete
		m_pMatrix = nullptr;
	}

	super::Release(); //release the memory of the inherited fields
}