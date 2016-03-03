#ifndef GLOBAL
#define GLOBAL
#include<Windows.h>
#include<iostream>
#include"rain.h"
#include"relation.h"
#include<list>
#include"rain.h"
#include<vector>

using namespace std;
class Options {
public:
	GLint ALPHA_TRIG;
	GLint TEXTURE_TRIG;
	GLint ANTIALIAS_TRIG;
	GLint CAMERA_TRIG;
	GLint FRAME_TRIG;
	GLint SOUND_TRIG;
	GLint BIG_TRIG;
	GLint KONAMI_TRIG;
	Options();
};
class Game {
public:	
	GLboolean playing;
	list<Relation*> collisionList;
	
	int player;
	list<ball*> goal[2];
	
	GLboolean foul;
	Game();
};
class GlobalSingleTone{//real variables goes here;
public:	
	Options option;
	Game game;
	int konamiStatus;
	GLdouble rainbowTyrenol[3] = { 0.5,0.5,0.5 };
	int normValue;
	int systemSize;
	int stage;
	GLboolean settingTable;
	GLboolean mouseDown;
	
	GLdouble mX, mY;
	GLdouble slingDist;	
	
	ball* balls[16];

	Rain* beMyRain;

	GlobalSingleTone();
	
};
class Global{//singleton global variables;
private:
	GlobalSingleTone * variable;
	GlobalSingleTone * generator();
public:
	Global();
	GlobalSingleTone * getGlobal();
};
#endif