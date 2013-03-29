#include "cStage.h"
#include"cEnemyWave.h"

cStage::cStage()
{
	mWaves = 2;
	mCounter = 0;


}
void cStage::Update(list<cEnemy*> &eShips,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice)
{
	mCounter++;
	if(mCounter == 100)
	{
		cEnemyWave eWave = cEnemyWave(0, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);
		//mCounter = 0;
	}
	if(mCounter == 200){
	cEnemyWave eWave = cEnemyWave(1, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);
	}
	if(mCounter == 300){
	cEnemyWave eWave = cEnemyWave(2, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);}
	if(mCounter == 400){
	cEnemyWave eWave = cEnemyWave(3, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);}
	if(mCounter == 500){
	cEnemyWave eWave = cEnemyWave(4, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);}
	if(mCounter == 600){
	cEnemyWave eWave = cEnemyWave(5, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);}
	if(mCounter == 700){
	cEnemyWave eWave = cEnemyWave(6, clientBounds, pd3dDevice);
		eShips.merge(eWave.mWave);}
	if(mCounter == 800){}
	if(mCounter == 900){}
	if(mCounter == 1000)
	{
		mCounter = 0;
	
	}
}