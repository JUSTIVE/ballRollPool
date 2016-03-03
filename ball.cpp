#include"ball.h"
ball::ball() {	};
ball::ball(GLdouble ballX, GLdouble ballY, GLint num,GLint half){
		this->bpoint = new Point(ballX, ballY);
		this->num= num;
		this->half = half;
		this->velo = new Velo();
		this->acc = new Acc();
		this->prevAcc = new Acc();
		this->force = new Force();
		this->preForce = new Force();
		this->preVelo = new Velo();
		this->visible = true;
	};
ball::~ball() {delete bpoint;};
void ball::setPoint(Point * nextPoint){ this->bpoint = nextPoint; }
void ball::setForce(Force* force) { this->force = force; };
void ball::setAcc(Acc* acc) { this->acc = acc; }
void ball::setPrevAcc(Acc* acc) { this->acc = acc; }
void ball::setVelo(Velo* velo){this->velo = velo;}
void ball::setPreVelo(Velo * velo) {
	this->preVelo = velo;
}
void ball::setPreForce(Force* force) { this->preForce = force; }

void ball::setVisible(GLboolean visible)
{
	this->visible = visible;

}

Point* ball::getPoint() { return bpoint; }
Force* ball::getForce() { return this->force; }
Acc* ball::getAcc() { return this->acc; }
Acc* ball::getPrevAcc() { return this->prevAcc; }
Velo* ball::getVelo() { return this->velo; }
Velo * ball::getPreVelo()
{
	return this->preVelo;
}
GLboolean ball::getVisible()
{
	return this->visible;
}
;
Force* ball::getPreForce() { return this->preForce; }

GLint ball::getNum(){ return num; }
GLint ball::getHalf() { return this->half; }

Point * ball::getNextPoint()
{
	Point* rtn=new Point(this->getPoint());
	rtn->setX(rtn->getX() - this->velo->getX()*DELTA_TIME);
	rtn->setY(rtn->getY() - this->velo->getY()*DELTA_TIME);
	return rtn;
}
GLdouble ball::getColor(int Num, int index) {
	return ballColors[Num][index];
}