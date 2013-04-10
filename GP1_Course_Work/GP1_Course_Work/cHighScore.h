#ifndef _CHIGHSCORE_H
#define _CHIGHSCORE_H
#include <iostream>
#include <fstream>

#include "GameConstants.h"

class cHighScore{

public:
	cHighScore();   //constructor
	int openfile();    //Open txt file of scores
	void getHighScores(char* scoreTable);      //Get highscore table for display
	~cHighScore();					// Destructor
bool checkScore(int score);   //Check players score against collection
void enterName(char* name, int &nameI, int &nameJ, int &nameK);    //Allows user to enter 3 initials as name
void UpdateScore(char* name, int score);   //update score collection

private:
	
	void saveFile();   //Save score collection to file
	
};
#endif