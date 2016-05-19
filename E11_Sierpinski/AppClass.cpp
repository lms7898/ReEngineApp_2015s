#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering");
<<<<<<< HEAD
=======
	m_v4ClearColor = vector4(REBLACK, 1.0f);
>>>>>>> refs/remotes/labigm/master
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
<<<<<<< HEAD

	//initializing the array
	int m_nObjects = 100;

	// we need 16 floats for each object (each matrix has 16 floats)
	m_fMatrixArray = new  float[m_nObjects * 16];

	//initializing the whole spaces to the position at the origin just to play it safe
	for (uint n = 0; n < m_nObjects; n++)
	{
		const float* m4mvp = glm::value_ptr(
			glm::translate(vector3(n * 2, 0, 0)));
		memcpy(&m_fMatrixArray[n * 16], m4mvp, 16 * sizeof(float));
	}
	
	//Creating the Mesh points
	m_pMesh->AddVertexPosition(vector3(1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( -1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(1.0f,  -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);

	m_pMesh->AddVertexPosition(vector3(2.0f, 2.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(3.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
=======
	
	//Creating the Mesh points
	m_pMesh->AddVertexPosition(vector3(-1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3( 1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
>>>>>>> refs/remotes/labigm/master

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
<<<<<<< HEAD
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
=======
	ClearScreen();
>>>>>>> refs/remotes/labigm/master
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObjects
<<<<<<< HEAD

	m_pMeshMngr->Render();

=======
													   //clear the screen
	
	m_pMeshMngr->Render(); //renders the render list
<<<<<<< HEAD
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
>>>>>>> refs/remotes/labigm/master
=======
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
>>>>>>> refs/remotes/labigm/master
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}