#pragma once
#include"GL.H"
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>

#define GIVE_ME_RAIN 100
using namespace std;
class Rain {
private:
	GLdouble x[GIVE_ME_RAIN*2];
	GLdouble y[GIVE_ME_RAIN * 2];
	GLdouble velo[GIVE_ME_RAIN];
	GLdouble width[GIVE_ME_RAIN];
	void rainInit();

public:
	Rain();
	void drawRain();
	void rainDrop();
	void reRain();
	
};
