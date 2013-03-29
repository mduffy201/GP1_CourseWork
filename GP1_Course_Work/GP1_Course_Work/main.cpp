

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
#include "cBackground.h"
#include "cShot.h"
#include "cStage.h"
#include "cXAudio.h"
#include "cD3DXFont.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

RECT clientBounds;

TCHAR szTempOutput[30];
//============================================Player
cPlayer theShip;

//=============================================Enemy

list<cEnemy*> eShips;

//===========================================Shot
D3DXVECTOR3 shotPos; 
vector<cShot*> gShots;

//================================================background
cBackground background1;
//cBackground background2;
D3DXVECTOR3 backPos;
//D3DXVECTOR3 backPos2;
char gScoreStr[50];

//====================================================stage
cStage stage1;

int score = 0;
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
				theShip.moveLeft();

				return 0;
			}
			if (wParam == 'D')
			{
				theShip.moveRight();

				return 0;
			}
			if (wParam == 'W')
			{
				theShip.moveUp();

				return 0;
			}
			if (wParam == 'S')
			{
				theShip.moveDown();

				return 0;
			}
			if (wParam == VK_SPACE)
			{
				theShip.fire(gShots, d3dMgr->getTheD3DDevice());
			//theShip.fire(d3dMgr->getTheD3DDevice());
				return 0;
			}
		//	StringCchPrintf(szTempOutput, STRSAFE_MAX_CCH, TEXT("Mouse: lLastX=%d lLastY=%d\r\n"), LOWORD(lParam), HIWORD(lParam));
			OutputDebugString(szTempOutput);

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

	D3DXVECTOR3 shipPos = D3DXVECTOR3(25,25,0);
	theShip = cPlayer(shipPos,d3dMgr->getTheD3DDevice());
	//==================================================stage
	stage1 = cStage();

	sprintf_s( gScoreStr, 50, "Score: %d", score);
	//============================================background
	backPos = D3DXVECTOR3(0,0,0);
	background1 = cBackground(clientBounds, backPos, d3dMgr->getTheD3DDevice());
	//if(background1.getRect().right == clientBounds.right)
//	{
	//	backPos2 = D3DXVECTOR3(background1.getRect().right,0,0);
	//	background2 = cBackground(clientBounds, backPos2, d3dMgr->getTheD3DDevice());
	//}

	//===================================================font
	cD3DXFont* scoreFont = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "visitor1");
	RECT textPos;
	SetRect(&textPos, 50, 10, 400, 100);
	
	
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );



	// Create the background surface
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\Back.png");
	//

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
			
				

				stage1.Update(eShips, clientBounds, d3dMgr->getTheD3DDevice());
				
				theShip.update();
			
				//====================================================Background
				background1.update();
			//	background2.update();
		
					//========================================================================Collisions
			
				list<cEnemy*>::iterator index;
				vector<cShot*>::iterator iter;
				for(index = eShips.begin(); index != eShips.end(); ++index)
				{			
					for(iter = gShots.begin(); iter!=gShots.end(); ++iter)
					{
						if((*iter)->collidedWith((*iter)->getBoundingRect(),(*index)->getBoundingRect()) && (*iter)->getShooter() == 0)
						{
							score++;
							sprintf_s( gScoreStr, 50, "Score: %d", score);
							(*iter)->setActive(false);
							(*index)->setActive(false);
							OutputDebugString("Collision!!");
						}
						if((*iter)->collidedWith((*iter)->getBoundingRect(),theShip.getBoundingRect()) && (*iter)->getShooter() == 1)
						{
						OutputDebugString("Death");
						}
						if((*iter)->getSpritePos2D().x < clientBounds.left || (*iter)->getSpritePos2D().x > clientBounds.right)
						{
						(*iter)->setActive(false);
						}
					}
							if((*index)->getSpritePos().x < 30
							|| 
							(*index)->getSpritePos().y > clientBounds.bottom || 
							(*index)->getSpritePos().y < clientBounds.top)
						{
							(*index)->setActive(false);
						}
				}

				d3dMgr->beginRender();
				theBackbuffer = d3dMgr->getTheBackBuffer();
				d3dMgr->updateTheSurface(aSurface, theBackbuffer);
				d3dMgr->releaseTheBackbuffer(theBackbuffer);

				d3dxSRMgr->beginDraw();

		//	d3dxSRMgr->setTheTransform(background1.getSpriteTransformMatrix());	
	//		d3dxSRMgr->drawSprite(background1.getTexture(),&background1.getRect(),NULL,NULL,0xFFFFFFFF);

	
				//=====================================================ship

				d3dxSRMgr->setTheTransform(theShip.getSpriteTransformMatrix());
				d3dxSRMgr->drawSprite(theShip.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			
				

				//========================================================================Updates
		
				iter = gShots.begin();
				index = eShips.begin();
				while(iter != gShots.end())
				{
					if((*iter)->isActive() == false)
					{
						iter = gShots.erase(iter);
					}
					else
					{
						(*iter)->update();
						d3dxSRMgr->setTheTransform((*iter)->getSpriteTransformMatrix());  
						d3dxSRMgr->drawSprite((*iter)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
						iter++;
					}
				}
				while(index != eShips.end())
				{
					if((*index)->isActive() == false)
					{
						index = eShips.erase(index);
					}
					else
					{	
						(*index)->update(d3dMgr->getTheD3DDevice(),gShots);
						d3dxSRMgr->setTheTransform((*index)->getSpriteTransformMatrix());
						d3dxSRMgr->drawSprite((*index)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
						index++;
					}
				}


				d3dxSRMgr->endDraw();
				scoreFont->printText(gScoreStr,textPos);
				d3dMgr->endRender();
				OutputDebugString("timeElapsed > fpsRate");
				timeElapsed = 0.0f;
			}
			previousTime = currentTime;
			//==================================
			StringCchPrintf(szTempOutput, 30, TEXT("dt=%f\n"), dt);
			OutputDebugString(szTempOutput);
			StringCchPrintf(szTempOutput, 30, TEXT("timeElapsed=%f\n"), timeElapsed);
			OutputDebugString(szTempOutput);
			StringCchPrintf(szTempOutput, 30, TEXT("previousTime=%u\n"), previousTime);
			OutputDebugString(szTempOutput);
			StringCchPrintf(szTempOutput, 30, TEXT("fpsRate=%f\n"), fpsRate);
			OutputDebugString(szTempOutput);
			//====================================
		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}

