#include "cShot.h"

const float SHOT_SPEED = 10.0f;


cShot::cShot():cSprite()
{
	mActive = true;
	
}
cShot::cShot(eShooter shooter, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR shotSprite): cSprite(sPosition,pd3dDevice,shotSprite)
{
	mActive = true;
	mShooter = shooter;
}
eShooter cShot::getShooter()
{
	return mShooter;
}
void cShot::update()
{
	
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	
	switch(mShooter){
			case 0:
				cShot::setSpriteScaling(1.0f,1.0f);
				tempV2 = cShot::getSpritePos2D() + cShot::getTranslation();
				tempV3 = D3DXVECTOR3(tempV2.x + SHOT_SPEED, tempV2.y, 0.0f);
				cShot::setSpritePos(tempV3);
				cSprite::update();
				break;
			case 1:
					cShot::setSpriteScaling(-1.0f,1.0f);
				tempV2 = cShot::getSpritePos2D() + cShot::getTranslation();
				tempV3 = D3DXVECTOR3(tempV2.x - SHOT_SPEED, tempV2.y, 0.0f);
				cShot::setSpritePos(tempV3);
				cSprite::update();
				break;
	}

	//while(isActive)
}
void cShot::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}

/*
=================
- Determine if the sprite is active.
=================
*/
bool cShot::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}
 void Draw(cD3DXSpriteMgr* d3dxSRMgr)
{
	
	//d3dxSRMgr->setTheTransform(cShot::getSpriteTransformMatrix());  
				//	d3dxSRMgr->drawSprite(cShot::getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
}