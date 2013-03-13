#include "cPlayer.h"
#include "cShot.h"

const float SHIP_SPEED = 10.0f;
//const D3DXVECTOR3 startPos = D3DXVECTOR3(300,300,0);
LPCSTR shipSprite =  "Images\\Gradius_Ship.png";
//list<cShot*> gShots;

cPlayer::cPlayer():cSprite()
{
	mScore = 0;
	mLives = 5;
	mSpeed = SHIP_SPEED;

}

cPlayer::cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice): cSprite(sPosition,pd3dDevice,shipSprite)

{
	mScore = 0;
	mLives = 3;
	mSpeed = SHIP_SPEED;
}
void cPlayer::update()
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	//tempV2 = cPlayer::getSpritePos2D() + cPlayer::getTranslation();
	tempV2 = cPlayer::getTranslation();
	//tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	tempV3 =  D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cPlayer::setSpritePos(tempV3);
	cSprite::update();
}
/*void cPlayer::update(float dt)
{
	//dt = 1.0f;
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	//tempV2 = cPlayer::getSpritePos2D() + cPlayer::getTranslation();
	tempV2 = cPlayer::getTranslation();
	//tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	tempV3 =  D3DXVECTOR3(tempV2.x*dt,tempV2.y*dt,0.0f);
	cPlayer::setSpritePos(tempV3);
	cSprite::update();
}*/
float cPlayer::getSpeed()
{
	return cPlayer::mSpeed;
}
void cPlayer::fire()
{
	/*D3DXVECTOR3 shotPos;
		D3DXVECTOR2 shipP = cSprite::getSpritePos2D();
					D3DXVECTOR2 shipQ = cSprite::getSpriteCentre();
					int spW = cSprite::getSTWidth();
					int spL = cSprite::getSTHeight();
					shotPos = D3DXVECTOR3(shipP.x + spL, shipP.y + (spL/2),0);
					gShots.push_back(new cShot(shotPos,d3dMgr->getTheD3DDevice(),"Images\\shot.png"));*/
}
