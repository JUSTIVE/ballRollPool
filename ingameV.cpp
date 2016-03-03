#include"ingame.h"

extern Global globe;
extern Curtain curtain;

void drawTile() {
	glLoadIdentity();
	//backtile
	if (globe.getGlobal()->option.KONAMI_TRIG) {
		globe.getGlobal()->rainbowTyrenol[0] = (globe.getGlobal()->rainbowTyrenol[0] + 0.01) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[0] + 0.01);
		globe.getGlobal()->rainbowTyrenol[1] = (globe.getGlobal()->rainbowTyrenol[1] + 0.015) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[1] + 0.015);
		globe.getGlobal()->rainbowTyrenol[2] = (globe.getGlobal()->rainbowTyrenol[2] + 0.02) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[2] + 0.02);

		glColor3f(globe.getGlobal()->rainbowTyrenol[0], globe.getGlobal()->rainbowTyrenol[1], globe.getGlobal()->rainbowTyrenol[2]);
	}
	else {
		glColor3f(0.5, 0.2, 0.2);
	}
	glPushMatrix(); {
	
		glBegin(GL_POLYGON); {
			glVertex3f(0, 2, 0.0);
			glVertex3f(2, 2, 0.0);
			glVertex3f(2, 0, 0.0);
			glVertex3f(0, 0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();

	glLoadIdentity();
	//lines
	GLdouble x = 0.1, y = 0.05;

	//가로선
	glLineWidth(0.5);
	glColor3f(0.6, 0.3, 0.2);
	glPushMatrix(); {
		for (int i = 0; i <39; i++) {
			if (i % 3 == 0) { glLineWidth(4); }
			else { glLineWidth(0.5); }
			glBegin(GL_LINE_LOOP); {
				glLineWidth(0.5);
				glVertex3f(0, y, 0);
				glVertex3f(2.0, y, 0);
			}
			glEnd();
			y += 0.05;
		}
		//세로선
		x = 0.05;
		for (int i = 0; i < 39; i++) {
			if (i % 3 == 0) { glLineWidth(4); }
			else {
				glLineWidth(0.5);
			}
			glBegin(GL_LINE_LOOP); {

				glLineWidth(0.5);
				if (i % 3 == 0) { glLineWidth(10); }
				glVertex3f(x, 0, 0);
				glVertex3f(x, 2.0, 0);
			}
			glEnd();
			x += 0.05;
		}
	}
	glPopMatrix();
}
void drawPool() {
	GLdouble x = 0.0, y = 0.1;
	//shadow
	glPushMatrix(); {
		glColor4f(0.0, 0.0, 0.0, 0.2);
		glBegin(GL_POLYGON); {
			glVertex3f(0.49, 1.86, 0.0);
			glVertex3f(1.51, 1.86, 0.0);
			glVertex3f(1.51, 0.14, 0.0);
			glVertex3f(0.49, 0.14, 0.0);
		}
		glEnd();
	}glPopMatrix();
	//border
	glColor3f(0.6, 0.6, 0.2);
	glPushMatrix(); {
		glBegin(GL_POLYGON); {
			glVertex3f(0.5, 1.85, 0.0);
			glVertex3f(1.5, 1.85, 0.0);
			glVertex3f(1.5, 0.15, 0.0);
			glVertex3f(0.5, 0.15, 0.0);
		}
		glEnd();
	}glPopMatrix();
	//back
	glColor3f(0.2, 0.6, 0.2);
	glBegin(GL_POLYGON); {
		glVertex3f(0.55, 1.8, 0.0);
		glVertex3f(1.45, 1.8, 0.0);
		glVertex3f(1.45, 0.2, 0.0);
		glVertex3f(0.55, 0.2, 0.0);
	}
	glColor3f(1, 1, 1);
	glEnd();
	//hole
	x = 0.55, y = 1.8;
	for (int i = 0; i < 6; i++) {
		glPushMatrix(); {
			glColor3f(0.015, 0.1, 0.2);
			glTranslatef(x, y, 0.0);
			glutSolidSphere(RADIUS*1.5, 20, 20);
			glColor3f(0.7, 0.7, 0.2);
			drawEllipse(RADIUS*1.6, RADIUS*1.6);
			if (i % 2 == 0) {
				x = 1.45;
			}
			else {
				x = 0.55;
				y -= 0.8;
			}
		}
		glPopMatrix();
	}
}
void drawInGameBack() {
	drawTile();
	globe.getGlobal()->beMyRain->drawRain();
	drawPool();
	drawGauge();
	drawGoalPot();
	
}
void drawEllipse(float radiusX, float radiusY) {
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<360; i++)	{
		float rad = i*DEG2RAD;
		glVertex2f(cos(rad)*radiusX,
			sin(rad)*radiusY);
	}

	glEnd();
}
void drawBall() {//공들 좌표에 맞게 그리기
	for (int i = 0; i < 16; i++) {
		if (globe.getGlobal()->balls[i]->getVisible()){
			glPushMatrix(); {
				glLoadIdentity();
				glTranslatef(globe.getGlobal()->balls[i]->getPoint()->getX(), globe.getGlobal()->balls[i]->getPoint()->getY(), 0);
				glColor4f(0, 0, 0, 0.5);
				glLineWidth(1);
				drawEllipse(RADIUS + 0.001, RADIUS + 0.001);
				glColor3f(globe.getGlobal()->balls[i]->getColor(globe.getGlobal()->balls[i]->getNum(), 0), globe.getGlobal()->balls[i]->getColor(globe.getGlobal()->balls[i]->getNum(), 1), globe.getGlobal()->balls[i]->getColor(globe.getGlobal()->balls[i]->getNum(), 2));
				glutSolidSphere(RADIUS, 30, 30);
				if (globe.getGlobal()->balls[i]->getHalf() == 2) {
					glColor4f(1, 1, 1, 0.5F);
					glutSolidSphere(RADIUS / 2, 30, 30);
				}
			}
			glPopMatrix();
		}
	}
}
void drawGauge() {
	//Gauge
	glColor4f(1, 1, 1, 0.5);
	glBegin(GL_POLYGON); {
		glVertex3f(1.6, 1.85, 0.01);
		glVertex3f(1.7, 1.85, 0.01);
		glVertex3f(1.7, 0.15, 0.01);
		glVertex3f(1.6, 0.15, 0.01);
	}
	glEnd();
	GLdouble height = 0.15 + (globe.getGlobal()->slingDist>130.0 ? 130.0 : globe.getGlobal()->slingDist)*1.7 * 100 / (100 * 130);

	//bar
	glColor4f(1, 1, 1, 0.5);
	glBegin(GL_POLYGON); {
		glVertex3f(1.6, height + 0.005, 0.01);
		glVertex3f(1.72, height + 0.005, 0.01);
		glVertex3f(1.72, height - 0.005, 0.01);
		glVertex3f(1.6, height - 0.005, 0.01);
	}
	glEnd();
}
void displayInGame() {
	drawInGameBack();
	drawBall();
	drawCueLine();
	if (globe.getGlobal()->option.FRAME_TRIG == 1) {
		drawFrame();
	}
	drawSetting();
	moveBall();
	drawSystemMessage();
	curtain.drawCurtain();
	for (int i = 0; i < 16; i++) {
		forceInit(globe.getGlobal()->balls[i]);
	}
}

void drawCueLine() {	//마우스 클릭시 선 
	extern GLboolean mouse_down;
	GLdouble r, g = 0.8, b = 0.0;
	if (globe.getGlobal()->mouseDown && (globe.getGlobal()->balls[0]->getVelo()->getX() == 0.0)) {
		glPushMatrix(); {
			glLineWidth(2);
			glLoadIdentity();
			r = 0.5 + (globe.getGlobal()->slingDist>130.0 ? 130.0 : globe.getGlobal()->slingDist)*(100.0 / 130.0)*(0.004);
			g = 0.8 - (globe.getGlobal()->slingDist>130.0 ? 130.0 : globe.getGlobal()->slingDist)*(100.0 / 130.0)*(0.006);

			glColor3f(r, g, b);
			glBegin(GL_LINES); {
				glLineWidth(5);
				glVertex3f(globe.getGlobal()->balls[0]->getPoint()->getX(), globe.getGlobal()->balls[0]->getPoint()->getY(), 0);
				glVertex3f((globe.getGlobal()->mX / 250), 2 - (globe.getGlobal()->mY / 250), 0);
			}
			glEnd();
		}
		glPopMatrix();
	}
}
void drawSetting() {
	glPushMatrix(); {
		glColor3f(0.9, 0.9, 0);
		glTranslatef(0.35, 1, 0);
		glutSolidSphere(0.05, 20, 20);
	}
	glPopMatrix();
}
void drawGoalPot() { //골 들어간 이후의 공 위치
	glColor3f(0.1, 0.1, 0.2);
	glBegin(GL_POLYGON); {
		glVertex3f(0.3, 0.9, 0);
		glVertex3f(0.4, 0.9, 0);
		glVertex3f(0.4, 0.15, 0);
		glVertex3f(0.3, 0.15, 0);
	}glEnd();

	glBegin(GL_POLYGON); {
		glVertex3f(0.3, 1.85, 0);
		glVertex3f(0.4, 1.85, 0);
		glVertex3f(0.4, 1.1, 0);
		glVertex3f(0.3, 1.1, 0);
	}glEnd();
}