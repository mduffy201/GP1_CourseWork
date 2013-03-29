#ifndef _CBACKGROUND_H
#define _CBACKGROUND_H
#include "cSprite.h"
#include "cD3DXSpriteMgr.h"


class cBackground: public cSprite
{
private:
		RECT mBackGroundFull;
	RECT mBackGround1;

public:
	cBackground();
	cBackground(RECT clientBounds, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);
	void update();
	 RECT getRect();
	 void DrawBackground(cD3DXSpriteMgr* d3dxSRMgr);
};
#endif