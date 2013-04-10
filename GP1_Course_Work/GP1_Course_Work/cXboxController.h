#ifndef _CXBOXCONTROLLER_H
#define _CXBOXCONTROLLER_H
#include "GameConstants.h"

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
class cXboxController{

private:
	XINPUT_STATE _controllerState;
	
    int _controllerNum;
public:
	   cXboxController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
   // void Vibrate(int leftVal = 0, int rightVal = 0);

};
#endif