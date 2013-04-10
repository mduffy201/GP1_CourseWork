#include "cPlayer.h"


const float SHIP_SPEED = 10.0f;

LPCSTR shipSprite =  "Images\\Gradius_Ship.png";

D3DXVECTOR2 shipTrans;



cPlayer::cPlayer():cSprite()
{

	mSpeed = SHIP_SPEED;
	shipTrans = D3DXVECTOR2(0,0);
	mShooter = eShooter::PLAYER;
	bActive = true;

}

cPlayer::cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice): cSprite(sPosition,pd3dDevice,shipSprite)

{

	mSpeed = SHIP_SPEED;
	shipTrans = D3DXVECTOR2(0,0);
	mShooter = eShooter::PLAYER;
	bActive = true;
}
void cPlayer::update()
{
	cPlayer::setTranslation(shipTrans);
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	D3DXVECTOR3 tempV4 = cSprite::getSpritePos();
	tempV2 = cPlayer::getTranslation();
	tempV3 =  D3DXVECTOR3(tempV4.x + tempV2.x,tempV4.y + tempV2.y,0.0f);
	cPlayer::setSpritePos(tempV3);
	cSprite::update();
	shipTrans = D3DXVECTOR2(0,0);
}

void cPlayer::moveUp()
{
shipTrans.y -= 10.0f;
}
void cPlayer::moveDown()
{
shipTrans.y += 10.0f;
}
void cPlayer::moveLeft()
{
shipTrans.x -= 10.0f;
}
void cPlayer::moveRight()
{
	shipTrans.x += 10.0f;

}


void cPlayer::fire(vector<cShot*> &gShots, LPDIRECT3DDEVICE9 pd3dDevice)

{
	
	D3DXVECTOR2 shipPosition = cPlayer::getSpritePos2D();
	int width = cPlayer::getSTWidth();
	int height = cPlayer::getSTHeight();
	D3DXVECTOR3 shotPosition = D3DXVECTOR3(shipPosition.x + height, shipPosition.y + (height/2),0);
	gShots.push_back(new cShot(mShooter, shotPosition,pd3dDevice,"Images\\shot.png")); 

}


	void cPlayer::Death()
	{
	bActive = false;
	}
	bool cPlayer::isActive()
	{
		return bActive;
	}
	void cPlayer::Respawn()
	{
	//bActive = true;
	}

