#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <windows.h>
#include <math.h>

#include "logic.h"

using namespace std;

bool respuestacorrecta(int& mouseX, int& mouseY, int tablero[][4], int& acumulatedpoints, int answPoints[][4], int answers,int multiplicador);
bool dinerorapido(int& mouseX, int& mouseY);
bool settingsmouse(int x, int y,int buttons[]);

bool dinerorapido(int& mouseX, int& mouseY) {
	if (mouseX > 560 and mouseX < 710 and mouseY>560 and mouseY < 670) {
		return true;
	}
	else return false;
}

bool settingsmouse(int x, int y,int buttons[]) {
	if (x > 100 and x < 165 and y > 10 and y < 30) {
		buttons[0] = 1;
		return true;
	}
	else {
		buttons[0] = 0;
	}
	if (x > 100 and x < 165 and y > 60 and y <80) {
		buttons[1] = 1;
		return true;
	}
	else {
		buttons[1] = 0;
	}
	if (x > 15 and x < 50 and y > 110 and y < 150) {
		buttons[2] = 1;
		return true;
	}
	else {
		buttons[2] = 0;
	}
	if (x > 145 and x < 180 and y > 110 and y < 150) {
		buttons[3] = 1;
		return true;
	}
	else {
		buttons[3] = 0;
	}
	if (x > 65 and x < 135 and y > 110 and y < 150) {
		buttons[4] = 1;
		return true;
	}
	else {
		buttons[4] = 0;
	}
	if (x > 65 and x < 135 and y > 160 and y < 225) {
		buttons[5] = 1;
		return true;
	}
	else {
		buttons[5] = 0;
	}
	if (x > 10 and x < 50 and y > 180 and y < 215) {
		buttons[6] = 1;
		return true;
	}
	else {
		buttons[6] = 0;
	}
	if (x > 140 and x < 185 and y > 180 and y < 215) {
		buttons[7] = 1;
		return true;
	}
	else {
		buttons[7] = 0;
	}
	if (x > 78 and x < 120 and y > 235 and y < 275) {
		buttons[8] = 1;
		return true;
	}
	else {
		buttons[8] = 0;
	}
	if (x > 22 and x < 45 and y > 245 and y < 275) {
		buttons[9] = 1;
		return true;
	}
	else {
		buttons[9] = 0;
	}
	if (x > 140 and x < 190 and y > 248 and y < 278) {
		buttons[10] = 1;
		return true;
	}
	else {
		buttons[10] = 0;
	}

}

bool respuestacorrecta(int& mouseX, int& mouseY, int tablero[][4], int& acumulatedpoints, int answPoints[][4], int answers, int multiplicador) {
	bool playsound = false;
	if (mouseX > 190 and mouseY > 170 and mouseX < 190 + 419 and mouseY < 170 + 106) {
		if (tablero[0][0] == 0) {
			acumulatedpoints += answPoints[0][0]*multiplicador;
			playsound = true;
		}
		tablero[0][0] = 1; //cout << "1" << endl;
		if(playsound==true)return true;
	}
	if (mouseX > 190 and mouseY > 276 and mouseX < 190 + 419 and mouseY < 276 + 106 and answers >= 2) {
		if (tablero[0][1] == 0) {
			acumulatedpoints += answPoints[0][1] * multiplicador;
			playsound = true;
		}
		tablero[0][1] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 190 and mouseY > 382 and mouseX < 190 + 419 and mouseY < 382 + 106 and answers >= 3) {
		if (tablero[0][2] == 0) {
			acumulatedpoints += answPoints[0][2] * multiplicador;
			playsound = true;
		}
		tablero[0][2] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 190 and mouseY > 488 and mouseX < 190 + 419 and mouseY < 488 + 106 and answers >= 4) {
		if (tablero[0][3] == 0) {
			acumulatedpoints += answPoints[0][3] * multiplicador;
			playsound = true;
		}
		tablero[0][3] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 609 and mouseY > 170 and mouseX < 609 + 419 and mouseY < 170 + 106 and answers >= 5) {
		if (tablero[1][0] == 0) {
			acumulatedpoints += answPoints[1][0] * multiplicador;
			playsound = true;
		}
		tablero[1][0] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 609 and mouseY > 276 and mouseX < 609 + 419 and mouseY < 276 + 106 and answers >= 6) {
		if (tablero[1][1] == 0) {
			acumulatedpoints += answPoints[1][1] * multiplicador;
			playsound = true;
		}
		tablero[1][1] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 609 and mouseY > 382 and mouseX < 609 + 419 and mouseY < 382 + 106 and answers >= 7) {
		if (tablero[1][2] == 0) {
			acumulatedpoints += answPoints[1][2] * multiplicador;
			playsound = true;
		}
		tablero[1][2] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	if (mouseX > 609 and mouseY > 488 and mouseX < 609 + 419 and mouseY < 488 + 106 and answers >= 8) {
		if (tablero[1][3] == 0) {
			acumulatedpoints += answPoints[1][3] * multiplicador;
			playsound = true;
		}
		tablero[1][3] = 1; //cout << "1" << endl;
		if (playsound == true)return true;
	}
	return false;
}
