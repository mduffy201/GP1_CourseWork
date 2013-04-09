#include "cEnemyWave.h"


cEnemyWave::cEnemyWave(int ID,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice)
{
	mID = ID;
	mWave = makeWave(clientBounds, pd3dDevice);
		
}

list<cEnemy*> cEnemyWave::makeWave(RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice)
{
	//D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40+(i*60),clientBounds.bottom/2,0);


	switch(mID){
	case 0:
	for(int i = 0; i<4; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right,clientBounds.top + (150*i),0);
		mWave.push_back(new cEnemy(0, ePos, pd3dDevice));
	}
	break;
		case 1:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40,clientBounds.bottom,0);
		mWave.push_back(new cEnemy(1, ePos, pd3dDevice));
	}
	break;
			case 2:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40,clientBounds.top,0);
		mWave.push_back(new cEnemy(2, ePos, pd3dDevice));
	}
	break;
				case 3:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40,clientBounds.top,0);
		mWave.push_back(new cEnemy(3, ePos, pd3dDevice));
	}
	break;
				case 4:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40,clientBounds.bottom,0);
		mWave.push_back(new cEnemy(4, ePos, pd3dDevice));
	}
	break;
					case 5:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40+(i*60),clientBounds.bottom/2,0);
		mWave.push_back(new cEnemy(5, ePos, pd3dDevice));
	}
	break;
					case 6:
	for(int i = 0; i<1; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40+(i*60),clientBounds.bottom/2,0);
		mWave.push_back(new cEnemy(6, ePos, pd3dDevice));
	}
	break;
	}
	return mWave;

}