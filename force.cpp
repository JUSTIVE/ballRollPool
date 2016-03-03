#include"force.h"
Force::Force() {
	this->x = 0;
	this->y = 0;
}
Force::Force(GLdouble x,GLdouble y) {
	this->x = x;
	this->y = y;
}

GLdouble Force::getX() {
	return this->x;
}
GLdouble Force::getY() {
	return this->y;
}
void Force::setX(GLdouble x) {
	this->x = x;
}
void Force::setY(GLdouble y) {
	this->y = y;
}