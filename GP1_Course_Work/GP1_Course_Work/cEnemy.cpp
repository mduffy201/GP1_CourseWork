#include "cEnemy.h"

LPCSTR enemySprite = "Images\\EnemyShip1.png";
//const float SHIP_SPEED = 5.0f;
//const int fireRate = 50;
vector<cShot*>	eShots;
int counter = 0;
cEnemy::cEnemy():cSprite()
{

}
cEnemy::cEnemy(int ID,float speed, int fireRate, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice): cSprite(sPosition,pd3dDevice,enemySprite)

{
	mID = ID;
	mPoints= 0;
	//mSpeed = SHIP_SPEED;
	mActive = true;
	mShooter = eShooter::CPU;
	shipSpeed = speed;
	rateOfFire = fireRate;
	/*switch(mID){
	case 0:
		
		break;
	}*/
}
void cEnemy::update(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots)
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;

	
	counter++;

	switch(mID){
	case 0:
		//HORIZONTAL (RIGHT TO LEFT)
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x - shipSpeed, tempV2.y, 0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
	break;
	case 1:
		//VERTICAL (BOTTOM TO TOP)
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x , tempV2.y- shipSpeed, 0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
		break;
			case 2:
				//VERTICAL (TOP TO BOTTOM)
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x , tempV2.y + shipSpeed, 0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
		break;
				case 3:
					//DIAGONAL (top right to down left)
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x - shipSpeed , tempV2.y + shipSpeed, 0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
		break;
			case 4:
					//DIAGONAL (bottom right to up left)
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x - shipSpeed , tempV2.y - shipSpeed, 0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
		break;
		case 5:
		//Forward then up
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	if(tempV2.x > 400){
	tempV3 = D3DXVECTOR3(tempV2.x - shipSpeed, tempV2.y, 0.0f);
	}
	else
	{
	tempV3 = D3DXVECTOR3(tempV2.x , tempV2.y- shipSpeed, 0.0f);
	}
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
	break;
	case 6:
		//Forward then down
	tempV2 = cEnemy::getSpritePos2D() + cEnemy::getTranslation();
	if(tempV2.x > 400){
	tempV3 = D3DXVECTOR3(tempV2.x - shipSpeed, tempV2.y, 0.0f);
	}
	else
	{
	tempV3 = D3DXVECTOR3(tempV2.x , tempV2.y + shipSpeed, 0.0f);
	}
	cEnemy::setSpritePos(tempV3);
	cSprite::update();
	break;
	}

	if(counter == rateOfFire)
	{
		cEnemy::fire(pd3dDevice, gShots);
		counter = 0;
	}


}
void cEnemy::fire(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots)
{
	D3DXVECTOR3 shotPosition;
	D3DXVECTOR2 shipP = cSprite::getSpritePos2D();
	D3DXVECTOR2 shipQ = cSprite::getSpriteCentre();
	int spW = cSprite::getSTWidth();
	int spL = cSprite::getSTHeight();
	shotPosition = D3DXVECTOR3(shipP.x, shipP.y + (spL/2),0);
	gShots.push_back(new cShot(mShooter, shotPosition,pd3dDevice,"Images\\shot.png"));
}
void cEnemy::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}
vector<cShot*>	getShots()
{
	return eShots;
}

/*
=================
- Determine if the sprite is active.
=================
*/
bool cEnemy::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}
/*void cEnemy::setRateOfFire(int rate){
	rateOfFire = rate;
}
void cEnemy::setShipSpeed(float speed){
shipSpeed = speed;
}*/
