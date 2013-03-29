#include "cBackground.h"

//float SCROLL_SPEED = 5.0f;
//LPDIRECT3DDEVICE9 pd3dDevice;
LPCSTR iBackground =  "Images\\Space_Scene.png";

int offset = 0 ;
int gScreenWidth = 0;
int gScreenHeight = 0;
int gTextureWidth = 0;
int gTextureHeight = 0;

RECT mClientBounds;
cBackground::cBackground():cSprite()
{
	
}
cBackground::cBackground(RECT clientBounds, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice):cSprite(sPosition,pd3dDevice, iBackground)
{ 
	mClientBounds = clientBounds;
	mBackGround1.left = 0;
	mBackGround1.top = 0;
	mBackGround1.right = cBackground::getSTWidth();
	mBackGround1.bottom = cBackground::getSTHeight();
	mBackGroundFull = mBackGround1;
}
void cBackground::update()
{
	
	//RectRight start pos = VECTOR3(offset,0,0);
	//Rectright left = Rectleft right
	//Rectright top = Rectleft top;

	//if RectLeft right < screen right
	//then spawn RectRight


	/*mBackGroundFull.left = mBackGround1.left + offset;
	mBackGroundFull.right = mBackGround1.right + offset;
	offset++;*/
	mBackGround1.left++;
	mBackGround1.right++;

	

}
 RECT cBackground::getRect()
{
	return mBackGround1;
	//return mBackGroundFull;
}
 void DrawBackground(cD3DXSpriteMgr* d3dxSRMgr)
 {
	// d3dxSRMgr->drawSprite(cBackground::getTexture(),&background1.getRect(),NULL,NULL,0xFFFFFFFF);
 
 }
