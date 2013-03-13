

/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cSprite.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cShot.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

RECT clientBounds;

cPlayer theShip;
D3DXVECTOR2 shipTrans = D3DXVECTOR2(0,0);

D3DXVECTOR3 shotPos; 
//= D3DXVECTOR3(shipTrans.x,shipTrans.y,0);
list<cShot*> gShots;
/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{
	case WM_KEYDOWN:
			{
				if (wParam == 'A')
				{
					shipTrans.x -= 10.0f;
					return 0;
				}
				if (wParam == 'D')
				{
			shipTrans.x +=  10.0f;
					return 0;
				}
					if (wParam == 'W')
				{
				shipTrans.y -=  10.0f;
					return 0;
				}
				if (wParam == 'S')
				{
			shipTrans.y +=  10.0f;
					return 0;
				}
				if (wParam == VK_SPACE)
				{
				D3DXVECTOR2 shipP = theShip.getSpritePos2D();
					D3DXVECTOR2 shipQ = theShip.getSpriteCentre();
					int spW = theShip.getSTWidth();
					int spL = theShip.getSTHeight();
					shotPos = D3DXVECTOR3(shipP.x + spL, shipP.y + (spL/2),0);
					gShots.push_back(new cShot(shotPos,d3dMgr->getTheD3DDevice(),"Images\\shot.png"));
				
				return 0;
				}
				return 0;
			}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,"plant.ico"); // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "SpaceRockets"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"plant.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("SpaceRockets",			// the window class to use
							 "Space Rockets",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	//===============================================================
	//    FRAME/TIMING
	//===============================================================
		// Grab the frequency of the high def timer
	__int64 freq = 0; 				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	float fpsRate = 1.0f/25.0f;
	//==============================================================
	// SCREEN
	//==============================================================
	GetClientRect(wndHandle,&clientBounds);
	LPDIRECT3DSURFACE9 aSurface;				// the Direct3D surface
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	//==============================================================
	//      PLAYER 
	//==============================================================
	// Initial starting position for Ship
	
	D3DXVECTOR3 shipPos = D3DXVECTOR3(0,0,0);
	//cPlayer
		theShip = cPlayer(shipPos,d3dMgr->getTheD3DDevice());
	//theShip.setTranslation(shipTrans);
	//====================================================================
	

	//Build our matrix to rotate, scale and position our sprite
	//D3DXMATRIX transformMatrix;

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\Star_Field.jpg");

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			
			float dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;
			numFrames++;

			if(timeElapsed > fpsRate && numFrames>1)
			{
				theShip.setTranslation(shipTrans);
				
				theShip.update();

			d3dMgr->beginRender();
			theBackbuffer = d3dMgr->getTheBackBuffer();
			d3dMgr->updateTheSurface(aSurface, theBackbuffer);
			d3dMgr->releaseTheBackbuffer(theBackbuffer);

			d3dxSRMgr->beginDraw();

			d3dxSRMgr->setTheTransform(theShip.getSpriteTransformMatrix());
			d3dxSRMgr->drawSprite(theShip.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
				
			//===========================================================================            SHOTS
			list<cShot*>::iterator iter = gShots.begin();
				while(iter != gShots.end())
				{
					if((*iter)->isActive() == false)
					{
						//iter = gExplode.erase(iter);
					}
					else
					{
						(*iter)->update(dt);
						d3dxSRMgr->setTheTransform((*iter)->getSpriteTransformMatrix());  
						//d3dxSRMgr->drawSprite((*iter)->getTexture(),&((*iter)->getSourceRect()),NULL,NULL,0xFFFFFFFF);
						d3dxSRMgr->drawSprite((*iter)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
						++iter;
					}
				}
					//======================================================================
			d3dxSRMgr->endDraw();
			d3dMgr->endRender();
			}
				previousTime = currentTime;
		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}

