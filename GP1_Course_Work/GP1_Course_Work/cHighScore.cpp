#include "cHighScore.h"

int i;

string aScores[9];

cHighScore::cHighScore()
{
	//cHighScore::openfile();
}
/*
=================
- Destructor.
=================
*/
cHighScore::~cHighScore()			// Destructor
{

}
/*
=================
- Open File.
=================
*/
int cHighScore::openfile()
{

	string line;
	ifstream myFile ("HIGHSCORES.txt");
	i = 0;

	if(myFile.is_open())
	{

		while(!myFile.eof())
		{

			getline(myFile,line,'\n');
			aScores[i] = line;
			++i;
		}
		myFile.close();
		//cHighScore::checkScore(1);
	//	cHighScore::saveFile();
	}
	return(0);
}
/*
=================
- Save File.
=================
*/
void cHighScore::saveFile()
{
	ofstream myFile;
	myFile.open("HIGHSCORES.txt");


	if(myFile.is_open())
	{
		for(int i = 0; i < 10; i++)
		{
			myFile << aScores[i] + "\n";
			//myFile << name[i]+score[i] + "\n"; 	
		}
		myFile.close();	
	}
}
/*
=================
- Get High Scores.
=================
*/
void cHighScore::getHighScores(char* scoreTable){

	//string hName1 = name[0].substr(0,3);
	//int hScore1 =atoi(name[0].substr(3,3).c_str());

	string hNames[10];
	int hScores[10];

	for(int i = 0; i<10; i++)
	{
		hScores[i] = atoi(aScores[i].substr(0,3).c_str());
		hNames[i] =  aScores[i].substr(3,3);

	}
	//char scoreTable[50];
	//sprintf_s( gScoreStr, 50, "Score: %d", score);
	sprintf_s( scoreTable, 200, "1st %d %s \n2nd %d %s\n3rd %d %s\n4th %d %s \n5th %d %s \n6th %d %s \n7th %d %s \n8th %d %s \n9th %d %s \n10th %d %s"
		,hScores[0], hNames[0].c_str(),hScores[1], hNames[1].c_str()
		,hScores[2], hNames[2].c_str(),hScores[3], hNames[3].c_str()
		,hScores[4], hNames[4].c_str(),hScores[5], hNames[5].c_str()
		,hScores[6], hNames[6].c_str(),hScores[7], hNames[7].c_str()
		,hScores[8], hNames[8].c_str(),hScores[9], hNames[9].c_str());
	//"1. %s \n2. %s\n"
	//return scoreTable;
//	cHighScore::checkScore(1);
}
/*
=================
- Check Score.
=================
*/
void cHighScore::UpdateScore(char* name, int score)
{
	char i = name[0];
	char j = name[2];
	char k = name[4];
	string newName;


	int newScore = score;
	int bottomScore = atoi(aScores[9].substr(0,3).c_str());
	
	char sScore[9];

	sprintf_s(sScore,"%03i%c%c%c",score,i,j,k);
	
	if(newScore > bottomScore)
	{
		aScores[9] = sScore;
		int i, j, pass =1;
		string temp;
		int aLength = 10;
		bool exchanges = false;
		
		do{
			exchanges = false;
			
			for(i = aLength - 1; i >= pass;i--){
			
				int score1 =atoi(aScores[i].substr(0,3).c_str());
				int score2 = atoi(aScores[i-1].substr(0,3).c_str());
			
				if(score1 > score2)
				{
					temp = aScores[i];
					aScores[i] = aScores[i - 1];
					aScores[i - 1] = temp;
					exchanges = true;
				}
			}
			pass++;
	}while(exchanges && pass < aLength)	;
	}
	cHighScore::saveFile();
}
bool cHighScore::checkScore(int score)
{
	cHighScore::openfile();
	int newScore = score;
	int bottomScore = atoi(aScores[9].substr(0,3).c_str());

	if(newScore > bottomScore)
	{
	return true;
	}
	else
	{
	return false;
	}

}
/*
=================
- Enter Name.
=================
*/
void cHighScore::enterName(char* name, int &nameI, int &nameJ, int &nameK)
{
	//int i = 0, j = 1, k = 2;

	char firstLetter[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char secondLetter[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char thirdLetter[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


sprintf_s( name, 50, "%c.%c.%c",firstLetter[nameI],secondLetter[nameJ],thirdLetter[nameK]);


//use font draw text to change colour
//add set colour to font class
// each letter a different char array???
//ORRR
//Three background surfaces. 
//each with an indication of which letter is selected.

}