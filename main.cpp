//Retextured

//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//OpenCV
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "logic.h"
#include "SDL2SoundEffects.h"

using namespace std;
using namespace cv;

RenderWindow window("Family Feud", 1280, 720);

int SetMouseX, SetMouseY;
const int FPS = 60;
int framerate = 0;
//void keyboard();
void strikes(SDL_Texture* strikeTexture, bool& strikeanimation, float& tamanio, bool& registerstrike);
void animateanswer(int& fotograma,bool alreadyshown[][4],int tablero[][4],bool& startanimation,int &auxX,int &auxY);
void restart(string stringAnsw[][4], string ansPointsS[][4], int answPoints[][4], int& answers, int tablero[][4], bool alreadyshown[][4], int cantStrikes, int& acumulatedpoints, bool hardreset);
void mouseHandler(int event, int x, int y, int flags, void* userdata);
void SetMousePos(int x, int y) {
	SetMouseX = x;
	//cout << "x: " << SetMouseX << endl;
	SetMouseY = y;
	//cout << "y: " << SetMouseY << endl;
}
void onMouse(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	switch (event) {
	case EVENT_LBUTTONDOWN: {
		int pixelvalue = static_cast<int>(image->at<uchar>(Point(x, y)));
		//cout << "The pixel value is x:" << x << " y:" << y << " . " << pixelvalue << endl;
		SetMousePos(x,y);
	}break;

	}
	
}

SDL_Texture* animationTexture2 = window.loadTexture("res/gfx/sprite2.png");
int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;
	
	if (TTF_Init() == -1) {
		cout << "TTF_init has failed. Error: " << SDL_GetError() << endl;
	}
	

	string path = { "res/gfx/backgroundpoints.png" };

	Mat Settings(300, 200, CV_8UC3, Scalar(238, 238, 238));
	Mat reset(300, 200, CV_8UC3, Scalar(238, 238, 238));

	//Buttons:
	Mat switchOn = imread("res/gfx/switchOn.png");
	Mat switchOff = imread("res/gfx/switchoff.png");
	Mat switchDisabled = imread("res/gfx/buttonDisabled.png");
	Mat resetButton = imread("res/gfx/resetButton.png");
	Mat leftArrowButton = imread("res/gfx/arrow.png");
	Mat rightArrowButton = imread("res/gfx/arrow.png");
	Mat strikeButton = imread("res/gfx/strikeButton.png");
	Mat x2Button = imread("res/gfx/x2Button.png");
	Mat x3Button = imread("res/gfx/x3Button.png");
	Mat OneStrike = imread("res/gfx/strikeButton.png");
	Mat musicButton = imread("res/gfx/music.png");
	Mat hardResetButton= imread("res/gfx/hardReset.png");
	
	//Resize
	resize(switchOn, switchOn, Size(), 0.7, 0.7);
	resize(switchOff, switchOff, Size(), 0.7, 0.7);
	resize(switchDisabled, switchDisabled, Size(), 0.7, 0.7);
	resize(resetButton, resetButton, Size(), 0.7, 0.7);
	resize(leftArrowButton, leftArrowButton, Size(), 0.7, 0.7);
	resize(rightArrowButton, rightArrowButton, Size(), 0.7, 0.7);
	resize(strikeButton, strikeButton, Size(), 0.7, 0.7);
	resize(x2Button, x2Button, Size(), 0.7, 0.7);
	resize(x3Button, x3Button, Size(), 0.7, 0.7);
	resize(OneStrike, OneStrike,Size(), 0.5, 0.5);
	resize(musicButton, musicButton, Size(), 0.7, 0.7);
	resize(hardResetButton, hardResetButton, Size(), 0.5, 0.5);
	flip(leftArrowButton, leftArrowButton, 1);

	int buttons[11] = { 0,0,0,0,0,0,0,0,0 };
	int slides[5] = { 0,2,0,0,0, };
	
	//Sounds
	SDL2SoundEffects se;
	se.addSoundEffect("res/sound/strike.mp3"); //0
	se.addSoundEffect("res/sound/hit.mp3");//1
	se.addSoundEffect("res/sound/winSound.mp3");//2
	//Fast Money
	se.addSoundEffect("res/sound/FMSound1.mp3");//3
	se.addSoundEffect("res/sound/FMSound2.mp3");//4
	se.addSoundEffect("res/sound/FMNoPoints.mp3");//5
	
	//namedWindow(img_window);
	
	//Mat reset(700, 700, CV_8UC3, Scalar(0, 0, 0));
	int mouseX=0, mouseY=0;
	int acumulatedpoints = 0;
	int multiplicador = 1;
	int Team1Points = 0;
	int Team2Points = 0;
	string STeam1Points;
	string STeam2Points;
	stringstream tp;
	int pointsaux;
	int answers;
	int widthPoints=0, heightPoints=0;
	int respuestas = 0;

	
	stringstream ap; string stringpoints;

	


	//Texturas
	SDL_Texture* boardTexture = window.loadTexture("res/gfx/board.png");
	SDL_Texture* FMTexture = window.loadTexture("res/gfx/fastmoney.png");
	SDL_Texture* Slot1Texture = window.loadTexture("res/gfx/number1.png");
	SDL_Texture* Slot2Texture = window.loadTexture("res/gfx/number2.png");
	SDL_Texture* Slot3Texture = window.loadTexture("res/gfx/number3.png");
	SDL_Texture* Slot4Texture = window.loadTexture("res/gfx/number4.png");
	SDL_Texture* Slot5Texture = window.loadTexture("res/gfx/number5.png");
	SDL_Texture* Slot6Texture = window.loadTexture("res/gfx/number6.png");
	SDL_Texture* Slot7Texture = window.loadTexture("res/gfx/number7.png");
	SDL_Texture* Slot8Texture = window.loadTexture("res/gfx/number8.png");
	SDL_Texture* answerTexture = window.loadTexture("res/gfx/answers.png");
	SDL_Texture* strikeTexture = window.loadTexture("res/gfx/strike.png");
	SDL_Texture* twostrikeTexture = window.loadTexture("res/gfx/twostrikes.png");
	SDL_Texture* threestrikeTexture = window.loadTexture("res/gfx/3strikes.png");
	SDL_Texture* animationTexture = window.loadTexture("res/gfx/sprite.png");
	//SDL_Texture* x3Texture = window.loadTexture("res/gfx/x3.png");
	//SDL_Texture* x2Texture = window.loadTexture("res/gfx/x2.png");
	//Entidades
	Entity FastMoney(0, 0, 1280, 720, FMTexture);
	Entity board(0, 0, 1280, 720, boardTexture);
	Entity asw1(0, 0, 1280, 720, Slot1Texture);
	Entity asw2(0, 0, 1280, 720, Slot2Texture);
	Entity asw3(0, 0, 1280, 720, Slot3Texture);
	Entity asw4(0, 0, 1280, 720, Slot4Texture);
	Entity asw5(0, 0, 1280, 720, Slot5Texture);
	Entity asw6(0, 0, 1280, 720, Slot6Texture);
	Entity asw7(0, 0, 1280, 720, Slot7Texture);
	Entity asw8(0, 0, 1280, 720, Slot8Texture);
	Entity animation(0, 0, 419, 424, animationTexture);
	Entity strike(0, 0, 1280, 720, strikeTexture);



	//Rects
	bool alreadyshown[2][4] = { 0,0,0,0,0,0,0,0 };
	bool startanimation = false;
	bool strikepregunta = false;
	SDL_Rect animationpos;
	animationpos.x = 0;
	animationpos.y = 0;
	animationpos.w = 419;
	animationpos.h = 106;
	SDL_Rect vacio;
	vacio.x = 0;
	vacio.y = 318;
	vacio.w = 419;
	vacio.h = 106;
	SDL_Rect respos;
	respos.x = 214;
	respos.y = 202;
	respos.w = 419;
	respos.h = 106;
	int auxX = 0, auxY = 0;
	int fotograma = 0;
	int clicks = 0;
	int tablero[2][4] = { 0,0,0,0,
							0,0,0,0 };
	string stringAnsw[2][4];
	int answPoints[2][4];
	string ansPointsS[2][4];
	
	float tamanio = 0;
	bool strikeanimation = false;
	int cantStrikes = 0;
	bool registerstrike = false;
	bool gameRunning = true;
	bool playsound = false;
	int contador = 0;
	SDL_Event event;
	SDL_Event mouseEvent{ SDL_MOUSEMOTION };

	bool fastmoney = false;
	bool startFastMoney = false;
	int FMcont = 0;
	int FMcont2 = -1;
	int FMcont3 = 0;
	int FMcont4 = -1;
	int totalfastmoney = 0;
	int timer = 20;
	bool Btimer = false;
	bool roundone = false, roundtwo = false, startroundtwo = false;
	bool roundtwoover = false;
	int activated = 0;
	int intpuntaje[5] = { 0,0,0,0,0 };
	int intpuntaje2[5] = { 0,0,0,0,0 };
	fstream txt,txt2;
	restart(stringAnsw,ansPointsS,answPoints,answers,tablero,alreadyshown,cantStrikes,acumulatedpoints,true);
	

	while (gameRunning)
	{	
		
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x -25;
				mouseY = event.motion.y -25;
				//cout << mouseX << "," << mouseY << endl;
				
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				clicks++;
				if (clicks == 1) {
					if (fastmoney == false and respuestacorrecta(mouseX, mouseY, tablero, acumulatedpoints, answPoints, answers,multiplicador) == true) {
					se.playSoundEffect(1);
					startanimation = true;

			}		
					if (fastmoney == true) {
						if (startFastMoney == true and timer == 0) {
							if (FMcont <= 5 and FMcont2 <= 5){
								if (FMcont != FMcont2) {
									FMcont2++;
									if (FMcont2 > 0 and FMcont2 < 6) {
										if (intpuntaje[FMcont2-1] == 0) {
											se.playSoundEffect(5);
										}
										else se.playSoundEffect(4);
									}
										
									
								}
								else {
									FMcont++;
									if (FMcont > 0 and FMcont < 6)se.playSoundEffect(3);
								}
							}
						}
					if (startroundtwo == true and startFastMoney == true and timer == 0) {
						if (FMcont3 <= 5 and FMcont4 <= 5) {
							if (FMcont3 != FMcont4) {
								FMcont4++;
								if (FMcont4 > 0 and FMcont4 < 6) {
									if (intpuntaje2[FMcont4-1] == 0) {
											se.playSoundEffect(5);
									}
									else se.playSoundEffect(4);
								}


							}
							else {
								FMcont3++;
								if (FMcont3 > 0 and FMcont3 < 6)se.playSoundEffect(3);
							}
						}
					}
					if (dinerorapido(mouseX, mouseY) == true) {
						startFastMoney = true;
						roundone = true;

					}


					}
								}
					else clicks = 0;

					Sleep(10);
				}
		}

		window.RenderWindow::clear();


		//Controls

		setMouseCallback("Settings", onMouse, reinterpret_cast<void*>(&Settings));
		reset.copyTo(Settings(Rect(0, 0, reset.cols, reset.rows)));
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[6] == 1) {
			multiplicador = 3;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[7] == 1) {
			multiplicador = 2;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[0] == 1) {
			if (fastmoney == true) {
				startFastMoney == false;
				fastmoney = false;
				roundone = false;
				roundtwo = false;
				roundtwoover = false;
				startroundtwo = false;
				FMcont = 0;
				FMcont2 = -1;
				FMcont3 = 0;
				FMcont4 = -1;
				Btimer = false;
				timer = 20;
				activated = 0;
				slides[0] = 0;
				slides[1] = 2;
			}
			else {
				fastmoney = true;
				startFastMoney = true;
				roundone = true;
				slides[0] = 1;
				slides[1] = 0;
			}
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (timer == 0 and startroundtwo==true) {
			slides[1] = 0;
		}
		if (timer == 0) {
			if(FMcont < 6 and FMcont2 < 5)slides[1] = 2;
			else slides[1] = 0;
		}
		
		if (fastmoney == true) {
			if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[1] == 1 and slides[1] == 0) {

				if (roundtwoover == false and activated == 0) {
					Btimer = true;
					slides[1] = 1;
					activated++;

				}
				if (FMcont >= 5 and FMcont2 >= 5 and roundtwoover == false and roundtwo == true and activated==1) {
					startroundtwo = true;
					timer = 26;
					Sleep(20);

				}

				if (FMcont >= 5 and FMcont2 >= 5 and roundtwoover == false and startroundtwo == true) {
					if (activated == 1) {
						Btimer = true;
						slides[1] = 1;
						activated++;
					}

					cout << FMcont << " " << FMcont2 << endl;
				}
				
				
				
				SetMouseX = -1;
				SetMouseY = -1;
			}
			//else slides[1] = 2;

		
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[2] == 1) {
			Team1Points += acumulatedpoints;
			//restart(stringAnsw, ansPointsS, answPoints, answers, tablero, alreadyshown, cantStrikes, acumulatedpoints, true);
			cantStrikes = 0;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[3] == 1) {
			Team2Points += acumulatedpoints;
			//restart(stringAnsw, ansPointsS, answPoints, answers, tablero, alreadyshown, cantStrikes, acumulatedpoints, true);
			cantStrikes = 0;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[4] == 1) {
			restart(stringAnsw, ansPointsS, answPoints, answers, tablero, alreadyshown, cantStrikes, acumulatedpoints, true);
			cantStrikes = 0;
			multiplicador = 1;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (strikeanimation==false and settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[5] == 1) {
			strikeanimation = true;
			playsound = true;
			if (registerstrike == false) {
				cantStrikes++;
				registerstrike = true;
			}
			cout << "Strikes:" << cantStrikes << endl;
			Sleep(40);
			SetMouseX = -1;
			SetMouseY = -1;
			
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[8] == 1) {
			strikepregunta = true;
			playsound = true;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[9] == 1) {
			se.playSoundEffect(2);
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[10] == 1) {
			restart(stringAnsw, ansPointsS, answPoints, answers, tablero, alreadyshown, cantStrikes, acumulatedpoints, true);
			Team2Points = 0;
			Team1Points = 0;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		putText(Settings, "Fast Money", {5,25}, FONT_HERSHEY_PLAIN, 1, Scalar(150, 150, 150), 1.75);
		putText(Settings, "Timer", { 50,75 }, FONT_HERSHEY_PLAIN, 1, Scalar(150, 150, 150), 1.75);

		for (int i = 0; i < 2; i++) {
			if (slides[i]==1) {
				switchOn.copyTo(Settings(Rect(100 , 1 + 50 * i, switchOn.cols, switchOn.rows)));
			}
			else if (slides[i] == 2) {
				switchDisabled.copyTo(Settings(Rect(100, 1 + 50 * i, switchDisabled.cols, switchDisabled.rows)));
			}
			else switchOff.copyTo(Settings(Rect(100, 1 + 50 * i, switchOff.cols, switchOff.rows)));
		}
		if (fastmoney == false) {
			leftArrowButton.copyTo(Settings(Rect(0, 110, leftArrowButton.cols, leftArrowButton.rows)));
			rightArrowButton.copyTo(Settings(Rect(130, 110, rightArrowButton.cols, rightArrowButton.rows)));
			resetButton.copyTo(Settings(Rect(65, 110, resetButton.cols, resetButton.rows)));
			x3Button.copyTo(Settings(Rect(0,180, x3Button.cols, x3Button.rows)));
			x2Button.copyTo(Settings(Rect(130, 180, x2Button.cols, x2Button.rows)));
			strikeButton.copyTo(Settings(Rect(65, 160, strikeButton.cols, strikeButton.rows)));
			OneStrike.copyTo(Settings(Rect(75, 230, OneStrike.cols, OneStrike.rows)));
			hardResetButton.copyTo(Settings(Rect(140, 245, hardResetButton.cols, hardResetButton.rows)));
		}
		musicButton.copyTo(Settings(Rect(20, 240, musicButton.cols, musicButton.rows)));
		

		if (fastmoney == false) {
			window.render(board, 1);
			//Points

			ap.clear();
			ap << acumulatedpoints;
			ap >> stringpoints;
			tp.clear();
			tp << Team1Points;
			tp >> STeam1Points;
			tp.clear();
			tp << Team2Points;
			tp >> STeam2Points;
			if (acumulatedpoints < 10) {
				window.drawText(stringpoints.c_str(), 618, 98, 10, 10, 10, 85);
				window.drawText(stringpoints.c_str(), 615, 95, 228, 228, 224, 85);
			}
			else if (acumulatedpoints >= 10 and acumulatedpoints < 100) {
				window.drawText(stringpoints.c_str(), 618 - 20, 98, 10, 10, 10, 85);
				window.drawText(stringpoints.c_str(), 615 - 20, 95, 228, 228, 224, 85);
			}
			else if (acumulatedpoints >= 100) {
				window.drawText(stringpoints.c_str(), 618 - 35, 98, 10, 10, 10, 85);
				window.drawText(stringpoints.c_str(), 615 - 35, 95, 228, 228, 224, 85);
			}
			////////////////////////////////////////////////////////////////////////////
			if (Team1Points < 10) {
				window.drawText(STeam1Points.c_str(), 68, 453, 10, 10, 10, 85);
				window.drawText(STeam1Points.c_str(), 65, 450, 228, 228, 224, 85);
			}
			else if (Team1Points >= 10 and Team1Points < 100) {
				window.drawText(STeam1Points.c_str(), 68 - 20, 453, 10, 10, 10, 85);
				window.drawText(STeam1Points.c_str(), 65 - 20, 450, 228, 228, 224, 85);
			}
			else {
				window.drawText(STeam1Points.c_str(), 68 - 35, 453, 10, 10, 10, 85);
				window.drawText(STeam1Points.c_str(), 65 - 35, 450, 228, 228, 224, 85);
			}
			/////////////////////////////////////////////////////////////////////////////
			if (Team2Points < 10) {
				window.drawText(STeam2Points.c_str(), 1173, 453, 10, 10, 10, 85);
				window.drawText(STeam2Points.c_str(), 1170, 450, 228, 228, 224, 85);
			}
			else if (Team2Points >= 10 and Team2Points < 100) {
				window.drawText(STeam2Points.c_str(), 1173 - 20, 453, 10, 10, 10, 85);
				window.drawText(STeam2Points.c_str(), 1170 - 20, 450, 228, 228, 224, 85);
			}
			else {
				window.drawText(STeam2Points.c_str(), 1173 - 35, 453, 10, 10, 10, 85);
				window.drawText(STeam2Points.c_str(), 1170 - 35, 450, 228, 228, 224, 85);
			}
			

			//Answers

			if (answers >= 1 and tablero[0][0] == 0) {
				window.render(asw1, 1);

			}
			if (answers >= 2 and tablero[0][1] == 0) {
				window.render(asw2, 1);

			}
			else if (tablero[0][1] == 0) {
				respos.x = 214;
				respos.y = 202 + 115;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 3 and tablero[0][2] == 0) {
				window.render(asw3, 1);
			}
			else if (tablero[0][2] == 0) {
				respos.x = 214;
				respos.y = 202 + 115 + 115;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 4 and tablero[0][3] == 0) {
				window.render(asw4, 1);
			}
			else if (tablero[0][3] == 0) {
				respos.x = 214;
				respos.y = 202 + 115 + 115 + 115;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 5 and tablero[1][0] == 0) {
				window.render(asw5, 1);
			}
			else if (tablero[1][0] == 0) {
				respos.x = 214 + 430;
				respos.y = 202;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 6 and tablero[1][1] == 0) {
				window.render(asw6, 1);
			}
			else if (tablero[1][1] == 0) {
				respos.x = 214 + 430;
				respos.y = 202 + 115;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 7 and tablero[1][2] == 0) {
				window.render(asw7, 1);
			}
			else if (tablero[1][2] == 0) {
				respos.x = 214 + 430;
				respos.y = 202 + 115 + 115;
				window.animation(animation, vacio, respos);
			}
			if (answers >= 8 and tablero[1][3] == 0) {
				window.render(asw8, 1);
			}
			else if (tablero[1][3] == 0) {
				respos.x = 214 + 430;
				respos.y = 202 + 115 + 115 + 115;
				window.animation(animation, vacio, respos);
			}

		

			if (playsound == true) {
				se.playSoundEffect(0);
				playsound = false;
			}

		


		
			//Tablero correcto;
			int cont = 0, length = 0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++) {
					if (tablero[i][j] == 1 and cont < answers) {
						Entity answer(213 + (427 * i), 202 + (115 * j), 419, 106, answerTexture);
						window.render(answer, 1);
						length = stringAnsw[i][j].size();
						//cout << length << endl;
						if (length >= 14) {
							window.drawText(stringAnsw[i][j].c_str(), (288 + (430 * i)) - (length * 4), 240 + (114 * j) + 3, 33, 38, 59, 40);
						}
						else window.drawText(stringAnsw[i][j].c_str(), (250 + (430 * i)), 230 + (114 * j) + 3, 33, 38, 59, 50);
						//window.drawText(stringAnsw[i][j].c_str(), 265 + (430 * i), 220 + (114 * j), 255, 255, 255, 30);
						if (answPoints[i][j] >= 10) {
							window.drawText(ansPointsS[i][j].c_str(), 563 + (430 * i), 230 + (116 * j), 33, 38, 59, 55);
							//window.drawText(ansPointsS[i][j].c_str(), 560 + (430 * i), 225 + (114 * j), 255, 255, 255, 40);
						}
						else {
							window.drawText(ansPointsS[i][j].c_str(), 575 + (430 * i), 230 + (116 * j), 33, 38, 59, 55);
							//window.drawText(ansPointsS[i][j].c_str(), 572 + (430 * i), 225 + (114 * j), 255, 255, 255, 40);
						}

					}
					cont++;
				}
			}
			if (multiplicador == 2) {
				window.drawText("x2", 723, 163, 50, 50, 50, 35);
				window.drawText("x2", 720, 160, 228, 228, 224, 35);
				//window.render(x2, 0.15);
			}
			if (multiplicador == 3) {
				window.drawText("x3", 723, 163, 50, 50, 50, 35);
				window.drawText("x3", 720, 160, 228, 228, 224, 35);
				//window.render(x3, 0.15);
			}

			if (startanimation == true) {
				animateanswer(fotograma, alreadyshown, tablero, startanimation, auxX, auxY);
			}

			if (cantStrikes > 3) {
				cantStrikes = 0;
				registerstrike = false;
				strikeanimation = false;

			}

			if (strikeanimation == true) {
				
				if (cantStrikes == 1 or cantStrikes == 4) {
					strikes(strikeTexture, strikeanimation, tamanio, registerstrike);
				}
				if (cantStrikes == 2) {
					strikes(twostrikeTexture, strikeanimation, tamanio, registerstrike);
				}
				if (cantStrikes == 3) {
					strikes(threestrikeTexture, strikeanimation, tamanio, registerstrike);
				}


			}
			if (strikepregunta == true) {
				strikes(strikeTexture, strikepregunta, tamanio, registerstrike);
			}
		

		
	}
	else {
		string participante1[10]={ "-","-" ,"-" ,"-" ,"-"," "," " ," " ," " ," " };
		string puntajePart1[5];
		string participante2[10] = { "-","-" ,"-" ,"-" ,"-"," "," " ," " ," " ," " };
		string puntajePart2[5];
		stringstream pnt;
		string Stimer;
		int totalfastmoney = 0;
		string total;
		
		window.render(FastMoney, 1);
	
	
	
		
		if (startFastMoney == true) {
			if (roundone == true) {
				txt.open("fastmoney1.txt", ios::in);
				for (int i = 0; i < 5; i++) {
					getline(txt, participante1[i]);

				}
				for (int j = 0; j < 5; j++) {
					getline(txt, puntajePart1[j]);
					pnt.clear();
					pnt << puntajePart1[j];
					pnt >> intpuntaje[j];
				}
				/*if (FMcont = 1) {
					window.drawText(participante1[0].c_str(), 220, 210 + (68 * i) + 3, 255, 255, 255, 30);
				}*/
				for (int i = 0; i < FMcont; i++) {

					window.drawText(participante1[i].c_str(), 220, 210 + (68 * i) + 3, 255, 255, 255, 30);

				}


				for (int i = 0; i < FMcont2; i++) {
					if (intpuntaje[i] < 10) {
						window.drawText(puntajePart1[i].c_str(), 590, 205 + (68 * i) + 3, 255, 255, 255, 40);

					}
					else {
						window.drawText(puntajePart1[i].c_str(), 590 - 10, 205 + (68 * i) + 3, 255, 255, 255, 40);
					}
					totalfastmoney += intpuntaje[i];
				}
				if (Btimer == true) {
					Sleep(1000);
					timer--;
				}
				if (timer == 0) {
					Btimer = false;
					roundtwo = true;
				}

			}
		}
		txt.close();
	
		if (roundtwo == true) {
			if (startroundtwo == true) {
				txt2.open("fastmoney2.txt", ios::in);

				for (int i = 0; i < 5; i++) {
					getline(txt2, participante2[i]);

				}
				for (int j = 0; j < 5; j++) {
					getline(txt2, puntajePart2[j]);
					pnt.clear();
					pnt << puntajePart2[j];
					pnt >> intpuntaje2[j];
				}

				for (int i = 0; i < FMcont3; i++) {

					window.drawText(participante2[i].c_str(), 670, 210 + (68 * i) + 3, 255, 255, 255, 30);

				}


				for (int i = 0; i < FMcont4; i++) {
					if (intpuntaje[i] < 10) {
						window.drawText(puntajePart2[i].c_str(), 1035, 205 + (68 * i) + 3, 255, 255, 255, 40);

					}
					else {
						window.drawText(puntajePart2[i].c_str(), 1035 - 10, 205 + (68 * i) + 3, 255, 255, 255, 40);
					}
					totalfastmoney += intpuntaje2[i];
				}
				if (FMcont3>=4 and FMcont4>=4 and timer == 0) {
					roundtwoover = true;
				}
				txt2.close();
			}
			
		}
		
		pnt.clear();
		pnt << timer;
		pnt >> Stimer;
		if (timer < 10) {
			window.drawText(Stimer.c_str(), 598+20, 583, 10, 10, 10, 85);
			window.drawText(Stimer.c_str(), 595+20, 580, 228, 228, 224, 85);
		}
		else if(timer<20 and timer>10) {
			window.drawText(Stimer.c_str(), 603, 583, 10, 10, 10, 85);
			window.drawText(Stimer.c_str(), 600, 580, 228, 228, 224, 85);
		}
		else {
			window.drawText(Stimer.c_str(), 598, 583, 10, 10, 10, 85);
			window.drawText(Stimer.c_str(), 595, 580, 228, 228, 224, 85);
		}
		pnt.clear();
		pnt << totalfastmoney;
		pnt >> total;
		window.drawText(total.c_str(), 975 , 562, 255, 255, 255, 40);

	
	}

	
		window.display();
		if (tamanio > 1) {
			Sleep(1000);
		}

		imshow("Settings", Settings);
	
	}

	window.cleanUp();
	SDL_Quit();
	TTF_Quit();

	return 0;
}

void animateanswer(int &fotograma,bool alreadyshown[][4],int tablero[][4],bool &startanimation,int &auxX,int &auxY) {
	int frameWidth, frameHeight;
	int TextureWidth, TextureHeight;
	
	SDL_Rect rect;
	//SDL_Rect destRect;
	//destRect.w = 419;
	//destRect.h = 106;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (tablero[i][j] == 1 and alreadyshown[i][j] == false) {
				alreadyshown[i][j] = true;
				startanimation = true;
				auxX = (210 + 430 * i);
				auxY = (200 + 115 * j);
			}
		}
	}
	Entity entity(auxX, auxY, 422, 432, animationTexture2);
	SDL_Texture* animationTexture = entity.getTex();
	SDL_QueryTexture(animationTexture, NULL, NULL, &TextureWidth, &TextureHeight);
	frameHeight = TextureHeight / 4;
	frameWidth = TextureWidth / 1;

	if (startanimation == true) {

		rect.x = 0;
		rect.w = frameWidth;
		rect.h = frameHeight;
		rect.y = frameHeight * fotograma;

		//cout << rect.y << endl;
		if (rect.y >= (frameHeight * 4)) {
			rect.y = 0;
		}
		//cout << destRect.x << " " << destRect.y << endl;
		//window.animation(entity, rect, destRect);
		window.render(entity,rect);
		
	}
	//cout << "Fotograma: " << fotograma << endl;
	//cout << startanimation << endl;
	fotograma++;
	Sleep(75);
	if (fotograma > 3) {
		startanimation = false;
		fotograma = 0;
	}
	

}

void strikes(SDL_Texture* strikeTexture,bool &strikeanimation, float &tamanio,bool &registerstrike) {
	
	if (tamanio > 1) {
		tamanio = 0;
		strikeanimation = false;
		registerstrike = false;


	}
	if (strikeanimation == true and tamanio <= 1) {
		if (tamanio >= 0.2 and tamanio < 0.4) {
			Entity strike(2550, 1475, 1280, 720, strikeTexture);
			window.render(strike, tamanio);
		}
		if (tamanio >= 0.4 and tamanio < 0.6) {
			Entity strike(955, 535, 1280, 720, strikeTexture);
			window.render(strike, tamanio);
		}
		if (tamanio >= 0.6 and tamanio < 0.8) {
			Entity strike(425, 255, 1280, 720, strikeTexture);
			window.render(strike, tamanio);
		}
		if (tamanio >= 0.8 and tamanio < 1) {
			Entity strike(155, 95, 1280, 720, strikeTexture);
			window.render(strike, tamanio);
		}
		if (tamanio == 1) {
			Entity strike(0, 0, 1280, 720, strikeTexture);
			window.render(strike, tamanio);
		}
		tamanio += 0.2;
		Sleep(7);
	}
}
void restart(string stringAnsw[][4],string ansPointsS[][4],int answPoints[][4], int &answers, int tablero[][4], bool alreadyshown[][4], int cantStrikes,int &acumulatedpoints,bool hardreset) {
	
	//Leer txt
	stringstream ans;
	fstream txt;
	int lineas, lineascont = 0;
	string cantLineas;
	string opciones[8];
	string puntosTxt[8];
	
	txt.open("game.txt", ios::in);
	getline(txt, cantLineas);
	lineas = stoi(cantLineas);
	answers = lineas;
	for (int i = 0; i < lineas; i++) {
		getline(txt, opciones[i]);
		getline(txt, puntosTxt[i]);

		//ut << opciones[i] << endl;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			stringAnsw[i][j] = opciones[lineascont];
			ansPointsS[i][j] = puntosTxt[lineascont];
			ans.clear();
			ans << ansPointsS[i][j];
			ans >> answPoints[i][j];
			lineascont++;
		}

	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			tablero[i][j] = 0;
			alreadyshown[i][j] = 0;
		}
	}
	cantStrikes = 0;
	if (hardreset == true) {
		acumulatedpoints = 0;
	}
	txt.close();
}


void mouseHandler(int event, int x, int y, int flags, void* userdata)
{
	cout << "\n-- event: " << event << endl;
	cout << "mouse position: (" << x << ", " << y << ")" << endl;
	cout << "flags: " << flags << endl;

	//Simple events comparison
	if (event == EVENT_LBUTTONDOWN) { cout << "Left button of the mouse is clicked" << endl; }
	else if (event == EVENT_RBUTTONDOWN) { cout << "Right button of the mouse is clicked" << endl; }
	else if (event == EVENT_MBUTTONDOWN) { cout << "Middle button of the mouse is clicked" << endl; }
	else if (event == EVENT_MOUSEMOVE) { cout << "Mouse move over the window" << endl; }

	//Comparisons using the 'flags' argument. Note: flags = event_flag + another event_flag
	if (flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON))
	{
		cout << "Left mouse button is clicked while pressing CTRL key" << endl;
	}
	else if (flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_RBUTTON))
	{
		cout << "Right mouse button is clicked while pressing SHIFT key" << endl;
	}
	else if (flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_CTRLKEY + EVENT_FLAG_ALTKEY))
	{
		cout << "SHIFT, CTRL and ALT keys are pressed" << endl; //To execute, move your mouse
	}
	else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_ALTKEY) //ALT is a particular case
	{//For the ALT KEY, AND operation is nedeed with the event
		cout << "Mouse is moved over the window while pressing ALT key" << endl;
	}
}
