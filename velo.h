#ifndef VELO
#define VELO
#include"force.h"
class Velo:Force {
public:
	Velo() :Force() {}
	GLdouble getX() { return this->x; };
	GLdouble getY() { return this->y; };
	void setX(GLdouble x) { this->x = x; };
	void setY(GLdouble y) { this->y = y; };
};
#endif