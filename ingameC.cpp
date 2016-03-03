#include"ingame.h"
extern Global globe;
extern Curtain curtain;
void inGameMouseEvent(int button, int state, int x, int y) {
	//cout << button << '\t' << state << endl;
	if (button == 0 && state == 0) {
		globe.getGlobal()->mX = x;
		globe.getGlobal()->mY = y;
		globe.getGlobal()->mouseDown = true;
	}
	if (button == 0 && state == 1) {//sling		
		if (sqrt(pow((x / 250.0) - 0.35, 2) + pow(((500 - y) / 250.0) - 1, 2) < 0.05)) {		
			curtain.setFlip(true);
		}

		else{
		//globe.getGlobal()->balls[0]->setForce(globe.getGlobal()->slingDist);
			globe.getGlobal()->mouseDown = false;
			if((globe.getGlobal()->balls[0]->getVelo()->getX()==0.0)){
				if (globe.getGlobal()->option.SOUND_TRIG) {
					wchar_t title[8] = L"tic.wav";
					sndPlaySound(title, SND_ASYNC | SND_SYSTEM);
				}
				sling();
			}	
			
		}
	}
	//glutPostRedisplay();
}
void inGameUpdater(){
	if(globe.getGlobal()->option.FRAME_TRIG)
		setFrame();
	if (curtain.getFrame() == 60) {
		globe.getGlobal()->stage = 2;
		globe.getGlobal()->settingTable = false;
	}	
	
}
void inGameTracker(int x, int y) {
	if (globe.getGlobal()->mouseDown) {
		globe.getGlobal()->mX = x;
		globe.getGlobal()->mY = y;
		if ((globe.getGlobal()->balls[0]->getVelo()->getX() == 0.0)) {
			globe.getGlobal()->slingDist = sqrt(pow(globe.getGlobal()->mX - (globe.getGlobal()->balls[0]->getPoint()->getX() * 250), 2) + pow(globe.getGlobal()->mY - (500 - (globe.getGlobal()->balls[0]->getPoint()->getY() * 250)), 2));
		}
	}
	
}

void moveBall() {
	if(!globe.getGlobal()->game.foul){
		ballCollision();
		for (int i = 0; i < 16; i++) {
			
			checkGoal(globe.getGlobal()->balls[i]);
			collisionBoundary(globe.getGlobal()->balls[i]);
			EulerSolver(globe.getGlobal()->balls[i], DELTA_TIME);
			groundFriction(globe.getGlobal()->balls[i]);
			forceInit(globe.getGlobal()->balls[i]);
		}
	}
}
void foulMouseEvent(int button,int state,int x, int y) {
	if (button == 0 && state == 1) {
		bool collided = false;
		for (int i = 1; i < 16; i++) {
			if (globe.getGlobal()->balls[0]->getPoint()->getDistance(new Point(globe.getGlobal()->balls[i]->getPoint()->getX(), globe.getGlobal()->balls[i]->getPoint()->getY())) < RADIUS){
				collided = true;
				break;
			}
		}
		if(!collided){	
			glutMouseFunc(inGameMouseEvent);
			glutMotionFunc(inGameTracker);
			glutPassiveMotionFunc(NULL);
			globe.getGlobal()->game.foul = false;
		}
	}
}
void foulPassiveMotionEvent(int x,int y) {
	globe.getGlobal()->balls[0]->getPoint()->setX(((x/250.0)>(1.45-RADIUS)?(1.45-RADIUS): (x / 250.0)<(0.55+RADIUS)? (0.55 + RADIUS): (x / 250.0)));
	globe.getGlobal()->balls[0]->getPoint()->setY((((500-y) / 250.0)>(1.8 - RADIUS) ? (1.8 - RADIUS) : ((500 - y) / 250.0)<(0.2 + RADIUS) ? (0.2 + RADIUS) : ((500 - y) / 250.0)));
}
void foulRule() {
	glutMouseFunc(foulMouseEvent);
	glutPassiveMotionFunc(foulPassiveMotionEvent);
	if (globe.getGlobal()->game.player == 0) {
		globe.getGlobal()->game.player = 1;
	}
	else {
		globe.getGlobal()->game.player = 0;
	}
}
void checkGoal(ball* b) {
	GLdouble x = 0.55, y = 1.8;	
	Point*  p = new Point(x, y);
	for (int i = 0; i < 6; i++) {
		if (b->getNextPoint()->getDistance(p)<RADIUS*1.6) {
			globe.getGlobal()->game.goal[globe.getGlobal()->game.player].push_front(b);
			b->getVelo()->setX(0);
			b->getVelo()->setY(0);

			if(b->getNum()==0){//파울인지 먼저 검사
				globe.getGlobal()->game.foul = true;
				foulRule();
			}
			if (b->getHalf() == globe.getGlobal()->game.player) {

			}

			else{//파울이 아닌 경우
				switch(globe.getGlobal()->game.player){//플레이어를 검사
				case 0:
					
					b->getPoint()->setX(0.35);					
					b->getPoint()->setY(0.15-RADIUS +(2*RADIUS*( globe.getGlobal()->game.goal[globe.getGlobal()->game.player].size())));
					break;
				case 1:
					b->getPoint()->setX(0.35);
					b->getPoint()->setY(0.16 + (2 * RADIUS*(globe.getGlobal()->game.goal[globe.getGlobal()->game.player].size())));
					break;
				}
			}
		}
		if (i % 2 == 0) {
			p->setX(1.45);
		}
		else {
			p->setX(0.55);
			p->setY(p->getY() - 0.8);
		}	
	}
	delete p;
}
void sling() {
	globe.getGlobal()->slingDist = sqrt(pow(globe.getGlobal()->mX - (globe.getGlobal()->balls[0]->getPoint()->getX() * 250), 2) + pow(globe.getGlobal()->mY - (500 - (globe.getGlobal()->balls[0]->getPoint()->getY() * 250)), 2));
	
	globe.getGlobal()->balls[0]->getForce()->setX((globe.getGlobal()->mX) / 250.0 - (globe.getGlobal()->balls[0]->getPoint()->getX()));
	globe.getGlobal()->balls[0]->getForce()->setY((500-globe.getGlobal()->mY)/250.0 - (globe.getGlobal()->balls[0]->getPoint()->getY()));
	globe.getGlobal()->balls[0]->getForce()->setX(globe.getGlobal()->balls[0]->getForce()->getX()* 20);
	globe.getGlobal()->balls[0]->getForce()->setY(globe.getGlobal()->balls[0]->getForce()->getY() * 20);
	globe.getGlobal()->slingDist = 0;
}
void collisionBoundary(ball* b) {
	GLdouble x = 0.55, y = 1.8;
	Point*p = new Point(x, y);
	bool isHole=false;
	for (int i = 0; i < 6; i++) {
		//if(b->getVelo)
		if (b->getNextPoint()->getDistance(p) < RADIUS*1.5) {
			isHole = true;
		}
		if (i % 2 == 0) {
			p->setX(1.45);
		}
		else {
			p->setX(0.55);
			p->setY(p->getY() - 0.8);			
		}
	}
	if(!isHole){
		if (b->getNextPoint()->getX()<0.55+RADIUS||b->getNextPoint()->getX()>1.45-RADIUS) {
			b->getVelo()->setX((0 - b->getVelo()->getX())*0.6);
		}
		if (b->getNextPoint()->getY()<0.2+RADIUS || b->getNextPoint()->getY()>1.8-RADIUS) {
			b->getVelo()->setY((0 - b->getVelo()->getY())*0.6);
		}
	}
	delete p;
}
void groundFriction(ball* b) {//움직일때 느려지는 속도
	b->getAcc()->setX(( b->getAcc()->getX())*GROUND_FRICTION_COEF_ACC);
	b->getAcc()->setY(( b->getAcc()->getY())*GROUND_FRICTION_COEF_ACC);

	b->getVelo()->setX((b->getVelo()->getX())*GROUND_FRICTION_COEF_VEL);
	b->getVelo()->setY((b->getVelo()->getY())*GROUND_FRICTION_COEF_VEL);


	if (abs(b->getVelo()->getX())<0.2){
		//b->getVelo()->setX((b->getVelo()->getX())*GROUND_FRICTION_COEF);
	}
	if (abs(b->getVelo()->getY())<0.2) {
		//b->getVelo()->setY((b->getVelo()->getY())*GROUND_FRICTION_COEF);
	}

	if (abs(b->getVelo()->getX()) < 0.0005)
		b->getVelo()->setX(0);
	if (abs(b->getVelo()->getY()) < 0.0005)
		b->getVelo()->setY(0);
}
#define VELO_THRESHOLD 3.0
void EulerSolver(ball* b, GLdouble dt) {

	if (b->getNum() != 0) {
		//cout << "x:" << b->getForce()->getX() << '\t' << "y:" << b->getForce()->getY() << endl;
	}

	b->getAcc()->setX(b->getForce()->getX()/MASS);
	b->getAcc()->setY(b->getForce()->getY() / MASS);
	
	//cout << b->getVelo()->getX() + (b->getAcc()->getX()*dt) << endl;
	b->getPreVelo()->setX(b->getVelo()->getX());
	b->getPreVelo()->setY(b->getVelo()->getY());
	
	b->getPrevAcc()->setX(b->getAcc()->getX());
	b->getPrevAcc()->setY(b->getAcc()->getY());

	b->getVelo()->setX((b->getVelo()->getX() + (b->getAcc()->getX()*dt))>VELO_THRESHOLD? VELO_THRESHOLD : (b->getVelo()->getX() + (b->getAcc()->getX()*dt)<-VELO_THRESHOLD ?-VELO_THRESHOLD : (b->getVelo()->getX() + (b->getAcc()->getX()*dt))));
	b->getVelo()->setY((b->getVelo()->getY() + (b->getAcc()->getY()*dt))>VELO_THRESHOLD ? VELO_THRESHOLD : (b->getVelo()->getY() + (b->getAcc()->getY()*dt)<-VELO_THRESHOLD ? -VELO_THRESHOLD : (b->getVelo()->getY() + (b->getAcc()->getY()*dt))));
		
	b->getPoint()->setX(b->getPoint()->getX() - (b->getVelo()->getX()*dt));
	b->getPoint()->setY(b->getPoint()->getY() - (b->getVelo()->getY()*dt));

	//b->getForce()->setX(0);
	//b->getForce()->setY(0);
}
void drawSystemMessage() {
	glPushMatrix(); {
		glColor4f(0.1, 0.1, 0.1, 0.9);
		glBegin(GL_POLYGON); {
			glVertex3f(0.6,0.13,0);
			glVertex3f(1.4,0.13,0);
			glVertex3f(1.4,0.02,0);
			glVertex3f(0.6,0.02,0);
		}
		glEnd();
	}
	glColor3f(0.8, 0.6, 0.1);
	glPopMatrix();
	string text = setSYSMSG();

	glPushMatrix(); {
		glTranslatef(1-(0.011*text.length()), 0.05, 0.0);
		glScalef(1 / 2200.0, 1 / 2200.0, 1 / 2200.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
}
string setSYSMSG() {
	string msg = "";
	if (globe.getGlobal()->game.foul) {
		msg = "!! Foul !!";
	}
	else {
		if (globe.getGlobal()->game.player == 0) {
			msg = "player 1";
		}
		else {
			msg = "player 2";
		}
	}
	return msg;
}
bool ballsAreColliding(ball* a, ball * b) {
	if (a->getNextPoint()->getDistance(new Point(b->getNextPoint())) < RADIUS*1.9)
		return true;
	if (a->getPoint()->getDistance(new Point(b->getPoint())) < RADIUS*1.9)
		return true;
	return false;
}
void giveForce(ball*a, ball*b) {
}
void ballCollision() {
	cout << globe.getGlobal()->balls[0]->getVelo()->getX()<<'\t'<< globe.getGlobal()->balls[0]->getVelo()->getY() <<endl;
	list<Relation*>::iterator it;
	for (int i = 0; i < 16; i++) {
		if(globe.getGlobal()->balls[i]->getVisible()){
			for (int j = 0; j < 16; j++) {
				if (globe.getGlobal()->balls[j]->getVisible()) {
					if (i != j) {
						if (ballsAreColliding(globe.getGlobal()->balls[i], globe.getGlobal()->balls[j])) {
							globe.getGlobal()->game.collisionList.push_back(new Relation(globe.getGlobal()->balls[i], globe.getGlobal()->balls[j]));
							//cout << "pushBack" << endl;
						}
					}
				}
			}
		}
		if(globe.getGlobal()->game.collisionList.size()>0)
			it = globe.getGlobal()->game.collisionList.begin();
		while (globe.getGlobal()->game.collisionList.size() != 0)
		{
			Force* currentForce = new Force();
			int num1,num2;

			num1 = (*it)->a->getNum();
			num2 = (*it)->b->getNum();

			globe.getGlobal()->balls[num1]->getVelo()->setX(0 - globe.getGlobal()->balls[num1]->getVelo()->getX()*STATIC_FRICTION_COEF*STATIC_FRICTION_COEF);
			globe.getGlobal()->balls[num1]->getVelo()->setY(0 - globe.getGlobal()->balls[num1]->getVelo()->getY()*STATIC_FRICTION_COEF*STATIC_FRICTION_COEF);

			globe.getGlobal()->balls[num1]->getPreVelo()->setX(0 - globe.getGlobal()->balls[num1]->getPreVelo()->getX());
			globe.getGlobal()->balls[num1]->getPreVelo()->setY(0 - globe.getGlobal()->balls[num1]->getPreVelo()->getY());

			currentForce->setX((((*it)->a->getVelo()->getX() - (*it)->a->getPreVelo()->getX()) / DELTA_TIME)*MASS*1.5);
			currentForce->setY((((*it)->a->getVelo()->getY() - (*it)->a->getPreVelo()->getY()) / DELTA_TIME)*MASS *1.5);

			//cout << "x:" << currentForce->getX() << '\t' << "y:" << currentForce->getY() << endl;
			//aktion
			globe.getGlobal()->balls[num2]->getForce()->setX(globe.getGlobal()->balls[num2]->getForce()->getX() + currentForce->getX()*pow(STATIC_FRICTION_COEF, 1));
			globe.getGlobal()->balls[num2]->getForce()->setY(globe.getGlobal()->balls[num2]->getForce()->getY() + currentForce->getY()*pow(STATIC_FRICTION_COEF, 1));
			//reaktion
			globe.getGlobal()->balls[num1]->getForce()->setX(globe.getGlobal()->balls[num1]->getForce()->getX()-((currentForce->getX())*pow(STATIC_FRICTION_COEF,4)));
			globe.getGlobal()->balls[num1]->getForce()->setY(globe.getGlobal()->balls[num1]->getForce()->getY()-((currentForce->getY())*pow(STATIC_FRICTION_COEF,4)));

			
			

			//작용
			///(*it)->b->setForce(new Force(currentForce->getX()*STATIC_FRICTION_COEF, currentForce->getY()*STATIC_FRICTION_COEF));
			//반작용
			///(*it)->a->getForce()->setX(0 - (currentForce->getX())*STATIC_FRICTION_COEF);
			///(*it)->a->getForce()->setY(0 - (currentForce->getY())*STATIC_FRICTION_COEF);

			it++;			
			globe.getGlobal()->game.collisionList.pop_front();
			delete currentForce;
		}
	}
	
	// {
		//Relation* Current = globe.getGlobal()->game.collisionList.;		
		//cout << globe.getGlobal()->game.collisionList.size() << endl;
		//cout << "a: " << (*it)->a->getNum() << '\t' << "b: " << (*it)->b->getNum() << endl;
		
	//}
	
}

void passiveCollsion(ball*a, ball* b) {
	for (size_t i = 0; i < BALL_AMOUNT; i++) {
		if (globe.getGlobal()->balls[i]->getVisible()) {
			for (size_t j = 0; j < BALL_AMOUNT; j++) {
				if (i != j) {
					if (globe.getGlobal()->balls[j]->getVisible()) {
						if (ballsAreColliding(globe.getGlobal()->balls[i], globe.getGlobal()->balls[j])) {
							//겹치면 우짤꼬
							;
						}
					}
				}
			}
		}
	}
}
void forceInit(ball* b) {
	b->getForce()->setX(0);
	b->getForce()->setY(0);
}