#ifndef POINT
#define POINT
#include"GL.H"

class Point{ //여기서 다음 point까지 계산하고싶어서 vec을 포함
private:
	GLdouble X;
	GLdouble Y;
public:
	Point(Point* point);
	Point(GLdouble X, GLdouble Y);	
	GLdouble getX();
	GLdouble getY();
	void setX(GLdouble X);
	void setY(GLdouble Y);
	GLdouble getDistance(Point* a);	
};
#endif