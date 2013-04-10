

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
#include "cHighScore.h"
#include "cXboxController.h"



using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();


int titleCounter = 0;
RECT clientBounds;

TCHAR szTempOutput[30];

//============================================Audio
cXAudio menuChange;
cXAudio stageMusic;

//============================================Player
int MENU_SCROLL = 15;
cPlayer theShip;

//=============================================Enemy
list<cEnemy*> eShips;

//===========================================Shot
D3DXVECTOR3 shotPos; 
vector<cShot*> gShots;

//----------------------------------------Counters
int fireCounter = 10;
int menuCounterUp = 10;
int menuCounterDown = 10;
int menuCounterRight = 10;
int menuCounterLeft = 10;
int deathCounter = 0;
//================================================background
cBackground background1;
//cBackground background2;
D3DXVECTOR3 backPos;
//D3DXVECTOR3 backPos2;

//===========================================Text
char gScoreStr[50];
char scoreTable[200];
char name[4];
char gStageTitle[25];
bool showTitle = true;

RECT titlePos;
RECT textPos;

//====================================================stage
cStage stage1;

int score = 0;     //Score

//================================================screens
bool menu = false;            //Main menu
bool hScore = false;         //High score table
bool newHScore = false;      //Name entry
bool lvComp = false;         //Level complete 
bool controls = true;


int menuOpt = 1;   //menu selection index

//=====================================NAME ENTRY
int nameI = 0;
int nameJ = 0;
int nameK = 0;
int sName = 1;

cHighScore* highScores;   //Highscore
cXboxController* Player1;    //Xbox controller
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
				//Screen edge collision
				if(theShip.getSpritePos2D().x < clientBounds.left + 60)
				{
					break;
				}
				//Change name index
				if(newHScore)
				{
					if(sName==1)
					{
						sName = 3;
					}
					else
					{
						sName--;
					}
				}

				theShip.moveLeft();

				return 0;
			}
			if (wParam == 'D')
			{
				//Change name index
				if(newHScore)
				{
					if(sName==3)
					{
						sName = 1;
					}
					else
					{
						sName++;
					}
				}
				theShip.moveRight();

				return 0;
			}
			if (wParam == 'W')
			{
				if(newHScore){
					//Change letter index
					switch(sName){
					case 1:
						if(nameI == 25)
							nameI=0;
						else
							nameI++;
						break;
					case 2:
						if(nameJ == 25)
							nameJ=0;
						else
							nameJ++;
						break;
					case 3:
						if(nameK == 25)
							nameK=0;
						else
							nameK++;
						break;
					}

				}

				//Play menu sound fx
				menuChange.playSound(L"Sounds\\menuChange.wav",false);
				//change menu index
				if(menuOpt==1)
				{
					menuOpt = 3;
				}
				else{
					menuOpt--;
				}

				theShip.moveUp();

				return 0;
			}
			if (wParam == 'S')
			{
				if(newHScore){
					//Change letter index
					switch(sName){
					case 1:
						if(nameI == 0)
							nameI=25;
						else
							nameI--;
						break;
					case 2:
						if(nameJ == 0)
							nameJ=25;
						else
							nameJ--;
						break;
					case 3:
						if(nameK == 0)
							nameK=25;
						else
							nameK--;
						break;
					}

				}

				//menu selection sound
				menuChange.playSound(L"Sounds\\menuChange.wav",false);
				//Menu index
				if(menuOpt==3)
				{
					menuOpt = 1;
				}
				else{
					menuOpt++;
				}
				theShip.moveDown();

				return 0;
			}
			if (wParam == VK_SPACE)
			{
				if(!menu)
				{
					//Add single shot to shot collection
					theShip.fire(gShots, d3dMgr->getTheD3DDevice());
				}

				//Play menu confirmation sound fx
				//Change scene using menu index
				else if(menu && menuOpt == 1)
				{
					menuChange.playSound(L"Sounds\\menuChoice.wav",false);
					menu= false;
				}
				else if(menu && menuOpt == 2)
				{
					menuChange.playSound(L"Sounds\\menuChoice.wav",false);
					menu = false;
					newHScore = true;
				}
				else if(menu && menuOpt == 3)
				{
					menuChange.playSound(L"Sounds\\menuChoice.wav",false);
					exit(0);
				}
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

	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer

	LPDIRECT3DSURFACE9 aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\Back.png");	
	LPDIRECT3DSURFACE9 menuScreen = d3dMgr->getD3DSurfaceFromFile("Images\\MENU_1.png");
	LPDIRECT3DSURFACE9 menuScreen1= d3dMgr->getD3DSurfaceFromFile("Images\\MENU_START.png");
	LPDIRECT3DSURFACE9 menuScreen2= d3dMgr->getD3DSurfaceFromFile("Images\\MENU_SCORES.png"); 
	LPDIRECT3DSURFACE9 menuScreen3= d3dMgr->getD3DSurfaceFromFile("Images\\MENU_QUIT.png");
	LPDIRECT3DSURFACE9 highScoreScreen = d3dMgr->getD3DSurfaceFromFile("Images\\HIGHSCORES.png");
	LPDIRECT3DSURFACE9 newHighScoreScreen = d3dMgr->getD3DSurfaceFromFile("Images\\NEWHIGHSCORE.png");
	LPDIRECT3DSURFACE9 levelComplete = d3dMgr->getD3DSurfaceFromFile("Images\\LEVEL_COMPLETE.png");
	LPDIRECT3DSURFACE9 controls = d3dMgr->getD3DSurfaceFromFile("Images\\CONTROLS.png");
	//==============================================================
	//      PLAYER 
	//==============================================================
	Player1 = new cXboxController(1);   //Crate controller instance for player 1

	SetRect(&titlePos, 330, 300, 500, 400);  //Set position for level title

	D3DXVECTOR3 shipPos = D3DXVECTOR3(100,100,0);   //Ship starting position
	theShip = cPlayer(shipPos,d3dMgr->getTheD3DDevice());  //Create cPlayer instance

	//==================================================stage
	stage1 = cStage();    //Create stage instance
	sprintf_s( gScoreStr, 50, "Score: %d", score);    //Update score display

	//============================================background
	//backPos = D3DXVECTOR3(0,0,0);
	//background1 = cBackground(clientBounds, backPos, d3dMgr->getTheD3DDevice());
	//===================================================font
	cD3DXFont* scoreFont = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "staravenue"); //Create score font

	SetRect(&textPos, 50, 10, 400, 100); //set position for score display


	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );


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

			//=============================TIMING
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			float dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;
			numFrames++;


			if(timeElapsed > fpsRate && numFrames>1)
			{	
				//=================================================================================
				//      XBOX CONTROLS
				//=================================================================================

				if(Player1->IsConnected())   //Test for controller conection
				{ 
					//===========================
					//          A BUTTON
					//===========================
					if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
					{

						//=================GAME PLAY
						if(!menu && !hScore && !newHScore && !lvComp){
							//Counter to limit fire rate
							if (fireCounter == 10)
							{
								//PLAY FIRE SOUND
								menuChange.playSound(L"Sounds\\LASER.wav",false);
								//Add new shot to vector
								theShip.fire(gShots, d3dMgr->getTheD3DDevice());
								fireCounter = 0;
							}
							fireCounter++;
						}
						//==================Main menu
						if(menu)
						{
							//Counter to limit menu scroll
							if(fireCounter == 10){
								//Play menu selection soundfx
								menuChange.playSound(L"Sounds\\menuChoice.wav",false);
								if(menu && menuOpt == 1)
								{
									//Load game scene
									stage1.startLevel();
									menu= false;
								}
								else if(menu && menuOpt == 2)
								{
									//Load highscore scene
									menu = false;
									hScore = true;
								}
								else if(menu && menuOpt == 3)
								{
									//Exit game
									exit(0);
								}
								fireCounter++;
							}
						}
						if(lvComp)
						{
							//Counter to limit menu scroll
							if(fireCounter == 10){
								lvComp = false;
								//Check for new highscore
								if(highScores->checkScore(score))
								{
									//If new highscore load name entry scene
									newHScore=true;
								}

								else{
									//if not load main menu
									menu = true;
								}
							}
							fireCounter++;
						}
						if(newHScore)
						{
							//Limit scroll
							if(fireCounter == 10){
								//Update highscores with entered name and current score
								highScores->UpdateScore(name,score);
								newHScore = false;
								hScore = true;       //Load highscore table
							}
							fireCounter++;
						}
						if(controls)
						{
							//Load main menu
							controls = false;
							menu = true;


						}
						fireCounter++;
					}
					else{
						fireCounter =10;
					}
					//================================
					//  B BUTTON
					//================================
					if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B){
						if(hScore)
						{
							//Load main menu
							hScore = false;
							menu = true;
						}

					}
					//================================
					//  LEFT STICK RIGHT
					//================================
					if(Player1->GetState().Gamepad.sThumbLX>10000)
					{
						if(!menu && !hScore && !newHScore && !lvComp){
							
							//Check screen collision
							if( theShip.getSpritePos2D().x < clientBounds.right - 60){
								theShip.moveRight();  
							}
						}
						//Limit menu scroll
						if(menuCounterRight == MENU_SCROLL)
						{
							if(newHScore)
							{
								//Scroll Letter position for name enter
								if(sName==3)
								{
									sName = 1;
								}
								else
								{
									sName++;
								}
							}
						}
						menuCounterRight++;

					}
					else
					{
						menuCounterRight = MENU_SCROLL;
					}
					//================================
					//  LEFT STICK LEFT
					//================================
					if(Player1->GetState().Gamepad.sThumbLX<-10000)
					{	
						
						if(!menu && !hScore && !newHScore && !lvComp){
							//Check screen collision
							if(theShip.getSpritePos2D().x > clientBounds.left + 60)
							{
								theShip.moveLeft();
							}
						}
						if(menuCounterLeft == MENU_SCROLL)
						{
							if(newHScore)
							{
								//Scroll Letter position for name enter
								if(sName==1)
								{
									sName = 3;
								}
								else
								{
									sName--;
								}
							}
						}
						menuCounterLeft++;

					}
					else{
						menuCounterLeft = MENU_SCROLL;
					}
					//================================
					//  LEFT STICK UP
					//================================
					if(Player1->GetState().Gamepad.sThumbLY>10000)
					{
						
						if(!menu && !hScore && !newHScore && !lvComp)
						{
							//Check screen collision
							if(theShip.getSpritePos2D().y >  clientBounds.top + 60)
							{
								theShip.moveUp();
							}
						}
						if(menu)
						{
							if(menuCounterUp == MENU_SCROLL)
							{
								//Play menu selection sound fx
								menuChange.playSound(L"Sounds\\MenuChange.wav",false);

								//Change menu index
								if(menuOpt==1)
								{
									menuOpt = 3;
								}
								else{
									menuOpt--;
								}
								menuCounterUp =0;
							}
							menuCounterUp++;
						}
						if(newHScore)
						{
							if(menuCounterUp == MENU_SCROLL)
							{
								//Scroll through letters on name entry
								switch(sName)
								{
								case 1:
									if(nameI == 25)
										nameI=0;
									else
										nameI++;
									break;
								case 2:
									if(nameJ == 25)
										nameJ=0;
									else
										nameJ++;
									break;
								case 3:
									if(nameK == 25)
										nameK=0;
									else
										nameK++;
									break;
								}
							}
							menuCounterUp++;
						}
					}
					else
					{
						menuCounterUp = MENU_SCROLL;
					}
					//================================
					//  LEFT STICK DOWN
					//================================
					if(Player1->GetState().Gamepad.sThumbLY<-10000)
					{

						if(!menu && !hScore && !newHScore && !lvComp){
							//Check screen collision
							if(theShip.getSpritePos2D().y <  clientBounds.bottom - 60){
								theShip.moveDown();}
						}
						if(menu)
						{
							if(menuCounterDown == MENU_SCROLL){
								menuChange.playSound(L"Sounds\\MenuChange.wav",false);
								if(menuOpt==3)
								{
									menuOpt = 1;
								}
								else{
									menuOpt++;
								}
								menuCounterDown = 0;
							}
							menuCounterDown++;

						}
						if(newHScore){
							if(menuCounterDown == MENU_SCROLL)
							{
								//Scroll through letters on name entry
								switch(sName){
								case 1:
									if(nameI == 0)
										nameI=25;
									else
										nameI--;
									break;
								case 2:
									if(nameJ == 0)
										nameJ=25;
									else
										nameJ--;
									break;
								case 3:
									if(nameK == 0)
										nameK=25;
									else
										nameK--;
									break;
								}

							}
							menuCounterDown++;
						}
					}
					else{
						menuCounterDown = MENU_SCROLL; 
					}
				}
				//=================================================================================
				//         GAME PLAY
				//=================================================================================
				if(!menu && !hScore && !newHScore && !lvComp &&!controls)
				{
					if(!theShip.isActive())
					{
						//counter to stall level end
						deathCounter++;
					}
					if(deathCounter == 20)
					{
						
						stageMusic.stopSound(); //Stop stage music
						lvComp = true;    //Load level complete scene
					}
					
					//========================================================stage title
					if(titleCounter<100)
					{
						//Counter for timed events
						if(titleCounter==5)
						{
							stageMusic.playSound(L"Sounds\\Moon.wav",false);    //Start stage music
						}
						sprintf_s( gStageTitle, 25, "Stage One");       //Display stage title
						titleCounter++;
					}
					else
					{

						showTitle = false;
						//========================================start stage
						if (stage1.isActive()){
							stage1.Update(eShips, clientBounds, d3dMgr->getTheD3DDevice());         //Run enemy scripting
						}
						else{
							
							//Load level complete scene
							lvComp = true;
						}
					}

					theShip.update();       //Update players movement

					//====================================================Background
					background1.update();
					//	background2.update();

					//========================================================================
					//               COLLISIONS                
					//=======================================================================
					list<cEnemy*>::iterator index;
					vector<cShot*>::iterator iter;
					

					//Loop through enemy ships
					for(index = eShips.begin(); index != eShips.end(); ++index)
					{			
						//Loop through shots
						for(iter = gShots.begin(); iter!=gShots.end(); ++iter)
						{
							//If enemy ship is shot
							if((*iter)->collidedWith((*iter)->getBoundingRect(),(*index)->getBoundingRect()) && (*iter)->getShooter() == 0)
							{

								score++;       //update score
								sprintf_s( gScoreStr, 50, "Score: %d", score);
								(*iter)->setActive(false);      //Remove shot
								(*index)->setActive(false);     //Remover enemy ship
								OutputDebugString("Collision!!");
							}
							//If player is shot
							if((*iter)->collidedWith((*iter)->getBoundingRect(),theShip.getBoundingRect()) && (*iter)->getShooter() == 1)
							{
								//PLAYER DEATH
								(*iter)->setActive(false);   //Remove shot
								theShip.Death();             //Kill player
								OutputDebugString("Death");
							}
							//If shot leaves screen bounds
							if((*iter)->getSpritePos2D().x < clientBounds.left || (*iter)->getSpritePos2D().x > clientBounds.right)
							{
								(*iter)->setActive(false);   //Remove shot
							}
						}
						//If enemy ship leaves screen bounds
						if((*index)->getSpritePos().x < 30
							|| 
							(*index)->getSpritePos().y > clientBounds.bottom+300 || 
							(*index)->getSpritePos().y < clientBounds.top-300)
						{
							(*index)->setActive(false);   //Remove enemy ship
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
					//If player is alive update and draw
					if(theShip.isActive()){
						d3dxSRMgr->setTheTransform(theShip.getSpriteTransformMatrix());
						d3dxSRMgr->drawSprite(theShip.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					}
					//========================================================================Updates


					//Delete inactive shots and enemy ships
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
							//If active update and draw
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
					//Display stage title
					if(showTitle)
						scoreFont->printText(gStageTitle,titlePos);
					d3dMgr->endRender();
					OutputDebugString("timeElapsed > fpsRate");
					timeElapsed = 0.0f;
				}
				//================================================================================================
				//                       MAIN MENU
				//================================================================================================
				else if(menu)
				{
					//Display specific screen based on menu index
					switch(menuOpt){
					case 1:
						menuScreen = menuScreen1;
						break;
					case 2:
						menuScreen = menuScreen2;
						break;
					case 3:
						menuScreen = menuScreen3;
						break;
					default:
						menuScreen = menuScreen;
						break;}
					//===============================
					//  RESET FOR NEW GAME
					//===============================
					score = 0;
					sprintf_s( gScoreStr, 50, "Score: %d", score);
					theShip.setSpritePos2D(D3DXVECTOR3(100,100,0));
					showTitle = true;
					titleCounter = 0;
					theShip.Respawn();

					//===============================

					//menuScreen1 = d3dMgr->getD3DSurfaceFromFile("Images\\MENU_1.png");
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(menuScreen, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					d3dMgr->endRender();
				}
				//================================================================================================
				//                      HIGH SCORE TABLE
				//================================================================================================
				else if(hScore)
				{
					//Set location for Score display
					RECT scorePos;
					SetRect(&scorePos, 50, 10, 700, 500);
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(highScoreScreen, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					highScores->openfile();               //Load highscores from file
					highScores->getHighScores(scoreTable);   //Load into scoreTable for display
					scoreFont->printText(scoreTable,scorePos);  //Display scores
					d3dMgr->endRender();
				}
				//================================================================================================
				//                     NEW HIGH SCORE
				//================================================================================================
				else if(newHScore)
				{

					//Update current name
					highScores->enterName(name, nameI, nameJ, nameK);
					//Set name psoition
					RECT scorePos;
					SetRect(&scorePos, 330, 300, 450, 400);
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(newHighScoreScreen, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					//Display current name
					scoreFont->printText(name,scorePos);
					d3dMgr->endRender();
				}
				//================================================================================================
				//                      LEVEL COMPLETE
				//================================================================================================
				else if(lvComp)
				{
					//Update score string
					sprintf_s( gScoreStr, 50, "%d", score);
					RECT scorePos;
					SetRect(&scorePos, 330, 300, 450, 400);
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(levelComplete, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					scoreFont->printText(gScoreStr,scorePos);   //Display Score
					d3dMgr->endRender();

				}
				else if(controls){
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(controls, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					d3dMgr->endRender();
				}
			}

			//menu
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
