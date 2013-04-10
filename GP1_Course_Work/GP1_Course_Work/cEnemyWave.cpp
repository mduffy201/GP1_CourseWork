#include "cEnemyWave.h"


cEnemyWave::cEnemyWave(int ID,float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice)
{
	mID = ID;
	mWave = makeWave(speed,fireRate,clientBounds, pd3dDevice);
		
}

list<cEnemy*> cEnemyWave::makeWave(float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice)
{
	//D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40+(i*60),clientBounds.bottom/2,0);


	switch(mID){
	case 0:
	for(int i = 0; i<4; i++)
	{
		//Horizontal Wave
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right,clientBounds.top +40+ (150*i),0);
		mWave.push_back(new cEnemy(0,speed,fireRate, ePos, pd3dDevice));
	}
	break;
		case 1:
	for(int i = 0; i<4; i++)
	{
		//Up Wave
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-30-(70*i),clientBounds.bottom+(60*i),0);
		mWave.push_back(new cEnemy(1,speed,fireRate, ePos, pd3dDevice));
	}
	break;
			case 2:
	for(int i = 0; i<4; i++)
	{
		//Down Wave
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40-(70*i),clientBounds.top-(60*i),0);
		mWave.push_back(new cEnemy(2,speed,fireRate, ePos, pd3dDevice));
	}
	break;
				case 3:
	for(int i = 0; i<4; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40 - (50*i),clientBounds.top-(50*i),0);
		mWave.push_back(new cEnemy(3,speed,fireRate, ePos, pd3dDevice));
	}
	break;
				case 4:
	for(int i = 0; i<4; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right-40- (50*i),clientBounds.bottom+(50*i),0);
		mWave.push_back(new cEnemy(4,speed,fireRate, ePos, pd3dDevice));
	}
	break;
					case 5:
	for(int i = 0; i<4; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right+(i*70),clientBounds.bottom/2,0);
		mWave.push_back(new cEnemy(5,speed,fireRate, ePos, pd3dDevice));
	}
	break;
					case 6:
	for(int i = 0; i<4; i++)
	{
		
		D3DXVECTOR3 ePos = D3DXVECTOR3(clientBounds.right+(i*70),clientBounds.bottom/2,0);
		mWave.push_back(new cEnemy(6,speed,fireRate, ePos, pd3dDevice));
	}
	break;
	}
	return mWave;

}
