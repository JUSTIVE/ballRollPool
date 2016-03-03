#ifndef BALL
#define BALL
#include"velo.h"
#include"acc.h"
#include<math.h>
#include"point.h"

#define RADIUS 0.03
#define MASS 0.5


class ball{
private:
	Point* bpoint; //°ø ÁÂÇ¥
	Force* force,*preForce;

	Velo *velo,*preVelo;
	Acc* acc,*prevAcc;
	GLint num;
	GLint half;

	GLboolean visible;
	GLdouble ballColors[16][3] = {
		{ 1, 1, 1 },
		{ 0.7, 0.7, 0 },
		{ 0, 0, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 0 },
		{ 0.2, 0.2, 0.2 },
		{ 1, 0.7, 0 },
		{ 0.7, 0, 0 },
		{ 0, 1, 0.7 },
		{ 0, 0.7, 0.4 },
		{ 0, 0, 0.7 },
		{ 0.7,0 , 0.7 },
		{ 0.8,0, 0.8 },
		{ 0.7,0.4 ,0.1 },
		{ 0.2, 0.8, 1 },
		{ 0.8, 0.5, 0.2 },
	};
public:
	ball();
	ball(GLdouble ballX, GLdouble ballY, GLint num,GLint half);
	~ball();
	void setPoint(Point * nextPoint);	
	void setForce(Force* force);
	void setAcc(Acc* acc);
	void setPrevAcc(Acc * acc);
	void setVelo(Velo*velo);
	void setPreVelo(Velo* velo);
	void setPreForce(Force* force);
	void setVisible(GLboolean visible);

	Point* getPoint();
	Force* getForce();
	Force* getPreForce();
	Acc* getAcc();
	Acc * getPrevAcc();
	Velo* getVelo();
	Velo* getPreVelo();
	GLboolean getVisible();

	GLint getNum();
	GLint getHalf();
	
	Point* getNextPoint();
	GLdouble getColor(int Num, int index);
};
#endif