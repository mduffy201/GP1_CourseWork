#include "cPlayer.h"


const float SHIP_SPEED = 10.0f;

LPCSTR shipSprite =  "Images\\Gradius_Ship.png";
//list<cShot*> gShots;


D3DXVECTOR2 shipTrans;



cPlayer::cPlayer():cSprite()
{
	mScore = 0;
	mLives = 5;
	mSpeed = SHIP_SPEED;
	shipTrans = D3DXVECTOR2(0,0);
	mShooter = eShooter::PLAYER;
	bActive = true;

}

cPlayer::cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice): cSprite(sPosition,pd3dDevice,shipSprite)

{
	mScore = 0;
	mLives = 3;
	mSpeed = SHIP_SPEED;
	shipTrans = D3DXVECTOR2(0,0);
	//pd3dDevice = pd3dDevice;
	mShooter = eShooter::PLAYER;
	bActive = true;
}
void cPlayer::update()
{
	cPlayer::setTranslation(shipTrans);
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cPlayer::getTranslation();
	tempV3 =  D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cPlayer::setSpritePos(tempV3);
	cSprite::update();
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
float cPlayer::getSpeed()
{
	return cPlayer::mSpeed;
}

void cPlayer::fire(vector<cShot*> &gShots, LPDIRECT3DDEVICE9 pd3dDevice)
	//void cPlayer::fire(LPDIRECT3DDEVICE9 pd3dDevice)
{
	
	D3DXVECTOR2 shipPosition = cPlayer::getSpritePos2D();
	int width = cPlayer::getSTWidth();
	int height = cPlayer::getSTHeight();
	D3DXVECTOR3 shotPosition = D3DXVECTOR3(shipPosition.x + height, shipPosition.y + (height/2),0);
	gShots.push_back(new cShot(mShooter, shotPosition,pd3dDevice,"Images\\shot.png")); 

}

//Encapsulate shots
/*void cPlayer::fire(LPDIRECT3DDEVICE9 pd3dDevice)
{
	
	D3DXVECTOR2 shipPosition = cPlayer::getSpritePos2D();
	int width = cPlayer::getSTWidth();
	int height = cPlayer::getSTHeight();
	D3DXVECTOR3 shotPosition = D3DXVECTOR3(shipPosition.x + height, shipPosition.y + (height/2),0);
   gShots.push_back(new cShot(shotPosition,pd3dDevice,"Images\\shot.png")); 
}*/
void cPlayer::Draw(cD3DXSpriteMgr* d3dxSRMgr,float dt)
{

	/*d3dxSRMgr->setTheTransform(cPlayer::getSpriteTransformMatrix());
			d3dxSRMgr->drawSprite(cPlayer::getTexture(),NULL,NULL,NULL,0xFFFFFFFF);

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
				//	(*iter)->Draw(d3dxSRMgr);
						d3dxSRMgr->setTheTransform((*iter)->getSpriteTransformMatrix());  
					d3dxSRMgr->drawSprite((*iter)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
						++iter;		
					}
				}*/
}
vector<cShot*> cPlayer::getShots()
{
	return cPlayer::gShots;
}
void cPlayer::setShots(vector<cShot*> &gShots)
{
	gShots = gShots;
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
	{}

