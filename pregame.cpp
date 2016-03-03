#include"pregame.h"
extern Global globe;
extern Curtain curtain;
GLint menu = 0;
GLint pick = 0;
GLint preGameSelect = 0;

void drawPreGameBack()
{
	glPushMatrix(); {
		if (globe.getGlobal()->option.KONAMI_TRIG) {
			globe.getGlobal()->rainbowTyrenol[0] = (globe.getGlobal()->rainbowTyrenol[0] + 0.01) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[0] + 0.01);
			globe.getGlobal()->rainbowTyrenol[1] = (globe.getGlobal()->rainbowTyrenol[1] + 0.015) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[1] + 0.015);
			globe.getGlobal()->rainbowTyrenol[2] = (globe.getGlobal()->rainbowTyrenol[2] + 0.02) > 1 ? 0.5 : (globe.getGlobal()->rainbowTyrenol[2] + 0.02);

			glColor3f(globe.getGlobal()->rainbowTyrenol[0], globe.getGlobal()->rainbowTyrenol[1], globe.getGlobal()->rainbowTyrenol[2]);
		}
		else {
			glColor3f(0.2, 0.9, 0.2);
		}
		glBegin(GL_POLYGON); {
			glVertex3f(0, 2, 0.0);
			glVertex3f(2, 2, 0.0);
			glVertex3f(2, 0, 0.0);
			glVertex3f(0, 0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();

	if(globe.getGlobal()->option.KONAMI_TRIG){
		globe.getGlobal()->beMyRain->drawRain();

	}

	glColor4f(0.2, 0.2, 0.2,0.5);
	glBegin(GL_POLYGON); {
		glVertex3f(0, 1.3, 0);
		glVertex3f(2, 1.3, 0);
		glVertex3f(2, 0.7, 0);
		glVertex3f(0, 0.7, 0);
	}
	glEnd();

	glColor3f(0.2, 0.9, 0.9);
	glBegin(GL_POLYGON); {
		glVertex3f(1.3,2,0);
		glVertex3f(2,2,0);
		glVertex3f(2,0,0);
		glVertex3f(1.3,0,0);
	}
	glEnd();	
}
void drawCursor() {
	glLoadIdentity();
	if(globe.getGlobal()->mouseDown){
		glColor3f(1, 1, 1);
	}
	else{
		glColor3f(0.8,0.8,0.8);
	}
	glPushMatrix(); {
		glTranslatef(1.4, 1.6 - (0.6*menu), 0);
		glBegin(GL_TRIANGLES); {
			glVertex3f(0, 0.05, 0);
			glVertex3f(0 + 0.05*sqrt(3), 0, 0);
			glVertex3f(0, -0.05, 0);
		}		
		glEnd();
	}
	glPopMatrix();
}
void preGameTracker(int x, int y) {
	globe.getGlobal()->mX = x;
	globe.getGlobal()->mY = y;
	if (x > 1.5) {
		menu = ( y / 150);		
	}
}
void drawText() {
	glLoadIdentity();
	string text = "start";
	glLineWidth(2);	
	glColor3f(1, 1, 1);
	glPushMatrix(); {
		glTranslatef(1.6, 1.58 - 0, 0.0);
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
		
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	text = "settings";
	glPushMatrix(); {
		glTranslatef(1.6, 1.58 - 0.6, 0.0);
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);

		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	text = "credit";
	glPushMatrix(); {
		glTranslatef(1.6, 1.58 - 1.2, 0.0);
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);

		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	
	text = "POOL";
	glPushMatrix(); {
		glLineWidth(3);
		glTranslatef(0.5, 1.58 - 0.6, 0.0);
		glScalef(1 / 1000.0, 1 / 1000.0, 1 / 1000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	text = "GAME";
	glPushMatrix(); {
		glLineWidth(1);
		glTranslatef(0.5, 1.58 - 0.7, 0.0);
		glScalef(1 / 1000.0, 1 / 1000.0, 1 / 1000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
}
void preGameMouseEvent(int button, int state, int x, int y) {
	if(x>1.5){
		if (button == 0 && state == 0) {
			globe.getGlobal()->mouseDown = true;
			pick = menu;
		}
	
		if (button == 0 && state == 1) {
			globe.getGlobal()->mouseDown = false;
			if (x > 1.5) {
				menu = (y / 150);
				preGameSelect;
			}
			if(menu==pick){
				curtain.setFlip(true);
			}
		}
	}
}
void preGameUpdater() {
	if (curtain.getFrame() == 60) {
		globe.getGlobal()->stage = pick+1;
		globe.getGlobal()->settingTable = false;
		if(pick==0){
			PlaySound(NULL, 0, 0);
		}
		
	}
	glutPostRedisplay();
}
void displayPreGame() {
	glLoadIdentity();
	drawPreGameBack();
	drawText();
	drawCursor();
	curtain.drawCurtain();
}