#ifndef POINT
#define POINT
#include"GL.H"

class Point{ //���⼭ ���� point���� ����ϰ�; vec�� ����
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