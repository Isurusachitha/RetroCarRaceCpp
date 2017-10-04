//Header Files
#include "windows.h"  
#include <iostream>
#include<conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <ios>
#include <cstdlib>


//Define Arrow  ASCII codes as constants

#define KEY_LEFT 75
#define KEY_RIGHT 77


//Defining and Inizilizing Var for Track
int Xlngt = 12;

int XlngtCrd = 57;


// Class for changing Colors

class TextAttr {
	friend std::ostream& operator<<(std::ostream& out, TextAttr attr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr.value);
		return out;
	}
public:
	explicit TextAttr(WORD attributes) : value(attributes) {}
private:
	WORD value;
};

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

//Dificulty changing Variables
int Difi=1;

int DifiLevl;

char Dificlty;

//Player Name

char ChrPlyr[]="Player1";


//Declaring Functions
DWORD WINAPI ThreadFn(LPVOID vpParam);

void gotoxy(int x, int y);
void drawp(int x, int y, int Cr);
void drawCar(int x, int y, int Cr);
void resetb();
int getCar();
void Intro();
int Exit();
void LogHighScore(char name[], int score);
void readScore();


//Variable initializer functions;
void VarIniz();


char chrGetKey;

//Declaring Array for Road track metrix
int ArryDraw[12][26][2];


int Incremt = 0, BolGamestatue = 1, XcordDrw = 0, XcordComptrCar, XcordComptrCar1, XcordComptrCar2;

int score = 1, level = 1, delay = 85;

using namespace std;

void VarIniz() {
	score = 1; level = 1;// delay = 85;
	Incremt = 0; BolGamestatue = 1; XcordDrw = 0;
	
}


int main() {
StructOutr:system("cls");

	//seting up gaming environment

	 Intro();
	 VarIniz();
	 system("cls");


	 //Calling Tread
	DWORD qThreadID;
	HANDLE hThread = CreateThread(0, 0, ThreadFn, 0, 0, &qThreadID);  // Tread


//	Splash Screen																  //Splash Screen before game started

	gotoxy(44, 2);


	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN) << "Need for Speed-Retro version";
	gotoxy(44, 4);


	cout << TextAttr(FOREGROUND_WHITE) << "CONTROLS";
	gotoxy(44, 5);
	cout << "========";
	gotoxy(44, 6);
	cout << "[A]=LEFT  or ARROW LEFT  [<-]";
	gotoxy(44, 7);
	cout << "[D]=RIGHT or ARROW RIGHT [->]";


	for (int i = 5,j=0; i >= 0; i--,j++) {  // Timer before game started

		gotoxy(44, 8);
		cout << i;
		gotoxy(45+j, 8);
		cout << "*";
		gotoxy(51, 15);
		Sleep(1000);

	}

	system("cls");// clean background


	//Game started
	while (BolGamestatue) {

		gotoxy(59, 4);
		cout << "SCORE:" << score;
		gotoxy(59, 5);
		cout << "LEVEL:" << level;

		resetb();


		//Drawing  templtes of Computer Controlled Cars
		drawCar(XcordComptrCar, Incremt, 0);

		if (Difi==1) {
			drawCar(XcordComptrCar1, Incremt, 0);
		}else if (Difi == 2) {
			drawCar(XcordComptrCar1, Incremt, 0);
			drawCar(XcordComptrCar2, Incremt, 0);
		}

		//Drawing the templete of player control car
		drawCar(XcordDrw, 21, 1);


		

		for (int j = 0; j<26; j++) {

			//Printing Left track line
			gotoxy(44, j + 1);

			cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN) << "S";
			cout << TextAttr(FOREGROUND_WHITE);

			gotoxy(45, j + 1);
			//Printing the movements of  the computer controlled Cars
			for (int i = 0; i<Xlngt; i++) {

				if (ArryDraw[i][j][0] == 1) {
					cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_BLUE) << "0";
					cout << TextAttr(FOREGROUND_WHITE);
				}
				else if (ArryDraw[i][j][1] == 1) {
					cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED) << "0";
					cout << TextAttr(FOREGROUND_WHITE);
				}
				else {
					cout << " ";
				}
			}

			//Drawing the Right track line
			gotoxy(XlngtCrd, j + 1);

			cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN) << "S";
			cout << TextAttr(FOREGROUND_WHITE);


			//Checking wheather  Players Car is Crashed with oncoming Compter Controlled Cars
			if (Incremt >= 21 && (XcordDrw == XcordComptrCar || XcordDrw == XcordComptrCar1 || XcordDrw == XcordComptrCar1)) {

				BolGamestatue = 0;

			}
		}

		Incremt++;


		// Scoring and designating tracks for computer controlled Cars
		if (Incremt == 25) {
			Incremt = -4;
			XcordComptrCar = getCar();

			int RndCord = XcordComptrCar;

			while (XcordComptrCar == RndCord) {
				//srand(0);

				RndCord = rand() % 4;
				RndCord = RndCord * 3;
			}
			XcordComptrCar1 = RndCord;

			int RndCord1 = XcordComptrCar1;

			while(XcordComptrCar1 == RndCord1) {
				//srand(0);

				RndCord1 = rand() % 4;
				RndCord1 = RndCord1 * 3;
			}
			XcordComptrCar2 = RndCord1;

			score++;
		}

		//Level Changing
		if (score % 5 == 0 && (Incremt == 25 || Incremt == -4)) {
			level++;

			//changing the speeeds of PC controlled Cars
			if (DifiLevl==1) {
				delay = delay - 10;
			}
			else if (DifiLevl == 2) {
				delay = delay - 5;
			}
			else if (DifiLevl == 3) {
				delay = delay - 5;
			}
			
		}

	



		// Winning event and displying winners  scores 

		if (delay<0) {
			gotoxy(59, 4);
			cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_BLUE) << "YOU WIN!" << endl;
			gotoxy(59, 5);
			cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);
			cout << "SCORE:" << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED) << score;
			gotoxy(59, 6);
			cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE) << "LEVEL:" << "12";

			BolGamestatue = 0;

			int intExt = Exit();
			if (intExt == 0) {
				goto StructOutr;
			}
			else {
				return 1;
			}

		}

		//  Delay of While Loop
		Sleep(delay);

		if (score == 5) {   /// designating no of oncoming cars

			Difi = 2;

		}


	}//end while

	//Saving scores into txt file
	LogHighScore(ChrPlyr,score);

	 // Gave Over Event
	if (delay>0) {
		gotoxy(59, 4);
		cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED) << "GAME OVER" << endl;
		gotoxy(59, 5);
		cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);
		cout << "TOP SCORE:" << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED) << score;
		gotoxy(59, 6);
		cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE) << "LEVEL:" << level;
		
		int intExt = Exit();
		if (intExt == 0) {
			goto StructOutr;
		}
		else {
			return 1;
		}
	}

	//Closeing the thread
	CloseHandle(hThread);
	_getch();
	
	return 0;
}

DWORD WINAPI ThreadFn(LPVOID vpParam)  // Thread
{
	/// Moving the player's Car 



		int leftCr = 0;
		int rigtCr = 3;

		while (1) {                       //getch get single charactor value from anykey


			chrGetKey = _getch();

			if (Xlngt == 12) {

				if (chrGetKey == 'a') {

					if (rigtCr == 0 && leftCr == 3) {
						XcordDrw = 6;
						rigtCr++;//1
						leftCr--;//2
					}
					else if (rigtCr == 1 && leftCr == 2) {
						XcordDrw = 3;
						rigtCr++;//= 2;
						leftCr--; //= 1;
					}
					else if (rigtCr == 2 && leftCr == 1) {
						XcordDrw = 0;
						rigtCr++;//= 1
						leftCr--; //= 0;
					}


				}
				else if (chrGetKey == 'd') {
					if (rigtCr == 3 && leftCr == 0) {
						XcordDrw = 3;
						rigtCr--;//2
						leftCr++;//1
					}
					else if (rigtCr == 2 && leftCr == 1) {
						XcordDrw = 6;
						rigtCr--;//= 1;
						leftCr++; //= 2;
					}
					else if (rigtCr == 1 && leftCr == 2) {
						XcordDrw = 9;
						rigtCr--;//= 0;
						leftCr++; //= 3;
					}

				}
				else if (chrGetKey == KEY_LEFT) {

					if (rigtCr == 0 && leftCr == 3) {
						XcordDrw = 6;
						rigtCr++;//1
						leftCr--;//2
					}
					else if (rigtCr == 1 && leftCr == 2) {
						XcordDrw = 3;
						rigtCr++;//= 2;
						leftCr--; //= 1;
					}
					else if (rigtCr == 2 && leftCr == 1) {
						XcordDrw = 0;
						rigtCr++;//= 1
						leftCr--; //= 0;
					}

				}
				else if (chrGetKey == KEY_RIGHT) {

					if (rigtCr == 3 && leftCr == 0) {
						XcordDrw = 3;
						rigtCr--;//2
						leftCr++;//1
					}
					else if (rigtCr == 2 && leftCr == 1) {
						XcordDrw = 6;
						rigtCr--;//= 1;
						leftCr++; //= 2;
					}
					else if (rigtCr == 1 && leftCr == 2) {
						XcordDrw = 9;
						rigtCr--;//= 0;
						leftCr++; //= 3;
					}

				}


			}

			if (Xlngt == 6) {

				if (chrGetKey == 'a') {
					XcordDrw = 0;
				}
				else if (chrGetKey == 'd') {
					XcordDrw = 3;
				}


			}


		}


	




	
	return 0;
}


void gotoxy(int x, int y)  // Set console cursor position on given cordinations
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




void resetb() // resting the Track Matrix by nulliing the Array
{
	for (int j = 0; j<26; j++) {

		for (int i = 0; i<Xlngt; i++) {

			ArryDraw[i][j][0] = 0;
			ArryDraw[i][j][1] = 0;


		}
	}
}


void drawp(int x, int y, int Cr) {  //Assiging Car drawing crdinates to array

	if (x >= 0 && x<Xlngt && y >= 0 && y<26) {

		ArryDraw[x][y][Cr] = 1;

	}

}


//Drawing Car template
void drawCar(int x, int y, int Cr)  //
{
	drawp(1 + x, 0 + y, Cr);
	drawp(0 + x, 1 + y, Cr);
	drawp(1 + x, 1 + y, Cr);
	drawp(2 + x, 1 + y, Cr);
	drawp(1 + x, 2 + y, Cr);
	drawp(0 + x, 3 + y, Cr);
	drawp(1 + x, 3 + y, Cr);
	drawp(2 + x, 3 + y, Cr);

}


int getCar() //   this method use to return reminder of  random number
{
	int n = 0;

	//initialize random seed

	int Modr = 2;

	if (Xlngt == 12) {
		Modr = 4;
	}
	else if (Xlngt == 9) {
		Modr = 3;
	}
	else if (Xlngt == 6) {
		Modr = 2;
	}

	int random = rand();

	//getting Reminder Value

	if (random % Modr == 0) {
		n = 0;
	}
	else if (random % Modr == 1) {
		n = 3;
	}
	else if (random % Modr == 2) {
		n = 6;
	}
	else if (random % Modr == 3) {
		n = 9;
	}





	return n;

}


//printing Intro Menu
void Intro() {

	system("cls");

	

	gotoxy(44, 3);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN) << "Need for Speed-Retro version";
	gotoxy(44, 4);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);
	cout << "Enter Player's name : ";
	
	cin >> ChrPlyr;
	

	gotoxy(44, 6);
	cout << "____________________________________________ ";
	VallidLbel1:gotoxy(44, 7);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_BLUE)<<ChrPlyr<< TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED) << "   Select Difficulty Level ";
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);

VallidLbel11:gotoxy(44, 8);

    cout << "_____________________________________________ " ;
	gotoxy(44, 9);
		cout << "       Easy        (1) ";
	gotoxy(44, 10);
	    cout << "       Medium      (2)";
	gotoxy(44,11);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED);
	     cout<< "       Hard        (3) ";
	gotoxy(44, 12);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);
	cout << "___________________________________________ ";
	gotoxy(44, 14);
	VallidLbel12:int intInput;
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE)<<"Enter your choice :";
	cin >> intInput;
	DifiLevl = intInput;

	if (intInput==1) {
		delay = 85;
		Dificlty = 'a';
	}
	else if (intInput == 2) {
		delay = 68;
		Dificlty = 'a';

	}
	else if (intInput == 3) {
		delay = 37;
		Dificlty = 'h';
	}
	else  {
		gotoxy(44, 15);
		cout << " <!> Invalid Input  <!>   Default Difficulty activatedc(Easy)";
		system("cls");
		Dificlty = 'a';
	}



	//strgName= sname;

}

// Displaying High Scores and Exit Sequence
int Exit() {
	system("cls");
	gotoxy(44, 3);
	readScore();

	system("cls");

	gotoxy(44, 3);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN) << "Do you want to play Need for Speed again (y/n) :"<<TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);

	char Chrchoice;
	cin >> Chrchoice;


	if (Chrchoice=='y') {
		return 0;
	}
	else if (Chrchoice=='n') {
	
		return 1;
	}
	else{
		return 1 ;
	}


}


//Saving High Scores to TXT file
void LogHighScore(char name[],int scoret) {

	try {


		std::ofstream log("Scorelogfile.txt", std::ios_base::app | std::ios_base::out);
		if (Dificlty == 'h') {
			log << "Player " << name << "  Top Score :" << scoret << "   status :  | Hard |\n";
		}
		std::ofstream log1("ScorelogfileTemp.txt", std::ios_base::app | std::ios_base::out);
		log1 << name << "  Top Score :" << scoret << "   status :  | ---------- |\n";
	
	
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}


}


//Reading and displaying data in TXT FILE of HIGH sCIRES
void readScore() {

	gotoxy(44, 3);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED)<< "------------------ScoreBoard--------------------";
	gotoxy(44, 4);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_BLUE) << "-----<Hard> Difficulty Level Scores Only--------";
	gotoxy(44, 5);
	cout << TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE) << "_______________________________________________";
	string STRING;
	ifstream infile;
	int lineY=6;
	infile.open("Scorelogfile.txt");
	while (!(infile.eof())) // To get you all the lines.
	{
		getline(infile, STRING); // Saves the line in STRING.

		gotoxy(44, lineY);
		cout << STRING<<endl; // Prints our STRING.

		lineY++;
	}
	infile.close();
	gotoxy(44 , lineY + 1);
	for (int i = 0; i <8; i++) {  // Timer before game started
		
		cout << "##";
		Sleep(1000);
		gotoxy(44 + i, lineY + 1);
	}
	system("cls");


}
