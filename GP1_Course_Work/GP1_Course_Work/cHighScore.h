#ifndef _CHIGHSCORE_H
#define _CHIGHSCORE_H
#include <iostream>
#include <fstream>

#include "GameConstants.h"

class cHighScore{

public:
	cHighScore();
	int openfile();
	void getHighScores(char* scoreTable);
	~cHighScore();					// Destructor
bool checkScore(int score);
void enterName(char* name, int &nameI, int &nameJ, int &nameK);
void UpdateScore(char* name, int score);

private:
	//void openfile();
	void saveFile();
	//string aScores[10];
};
#endif