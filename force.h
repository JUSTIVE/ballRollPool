#ifndef FORCE
#define FORCE
#include"GL.H"
class Force{	
protected:
	GLdouble x;
	GLdouble y;
public:
	Force();
	Force(GLdouble x, GLdouble y);
	GLdouble getX();
	GLdouble getY();
	void setX(GLdouble x);
	void setY(GLdouble y);
};
#endif