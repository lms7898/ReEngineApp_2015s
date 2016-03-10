#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E06_Lerp - Stapleford"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
<<<<<<< HEAD:E06_Lerp/AppClass.cpp
	//Set the camera at a position other than the default
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 12.0f),
		vector3(0.0f, 2.5f, 11.0f),
		vector3(0.0f, 1.0f, 0.0));

	m_nObjects = 10;

	m_pSphere = new PrimitiveClass[m_nObjects];
	m_pMatrix = new matrix4[m_nObjects];

	vector3 v3Start(-static_cast<float>(m_nObjects), 0.0f, 0.0f);
	vector3 v3End(static_cast<float>(m_nObjects), 0.0f, 0.0f);

	//vector3 v3Start(10, 0.0f, 0.0f);
	//vector3 v3End(20, 0.0f, 0.0f);

	for (uint i = 0; i < m_nObjects; i++)
	{
		float fPercent = MapValue(
			static_cast<float>(i),			//value to change
			0.0f,							//original min
			static_cast<float>(m_nObjects - 1),	//original max
			0.0f,							//new min
			1.0f							//new max
			);
		m_pSphere[i].GenerateSphere(0.5f, 5, RERED);
		vector3 v3Current = glm::lerp(v3Start, v3End, fPercent);
		m_pMatrix[i] = glm::translate(v3Current);
	}

=======
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
>>>>>>> 1ff633c8d38024521334e915ae750d4f7d39581f:00_Sandbox/AppClass.cpp
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

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	
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