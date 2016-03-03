#ifndef ACC
#define ACC
#include"force.h"
class Acc:Force{
public:
	Acc() :Force() {}
	GLdouble getX() { return this->x; };
	GLdouble getY() { return this->y; };
	void setX(GLdouble x) { this->x = x; };
	void setY(GLdouble y) { this->y = y; };
};
#endif