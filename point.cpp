#include"point.h"
#include<math.h>

Point::Point(Point* point) {
	this->X = point->getX();
	this->Y = point->getY();
}
Point::Point(GLdouble X, GLdouble Y) {
		this->X = X;
		this->Y = Y;
		
}

GLdouble Point::getX() { return X; }
GLdouble Point::getY() { return Y; }
void Point::setX(GLdouble X) { this->X = X; }
void Point::setY(GLdouble Y) { this->Y = Y; }

GLdouble Point::getDistance(Point* a) {
	return (sqrt(pow(this->X - a->getX(),2)+pow(this->Y - a->getY(),2)));
}