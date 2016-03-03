#include"credit.h"
extern Curtain curtain;
extern Global globe;
void creditUpdater() {
	if (curtain.getFrame() == 60) {
		globe.getGlobal()->stage = 0;
		globe.getGlobal()->settingTable = false;
	}
	glutPostRedisplay();
}
void drawCreditText() {
	string text = "DEV";
	glLineWidth(3);
	glColor3f(0.8, 0.4, 0.3);
	glPushMatrix(); {
		glTranslatef(1.2, 1.7, 0.0);
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	glLineWidth(2);
	text = "SCH CGLAB KMS";
	glPushMatrix(); {
		glTranslatef(1.0, 1, 0.0);
		glScalef(1 / 2000.0, 1 / 2000.0, 1 / 2000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
}
void displayCredit() {
	glLoadIdentity();
	drawCreditBack();
	drawCreditText();
	drawCreditBackButton();

	curtain.drawCurtain();

}
void drawCreditBack() {
	glColor3f(0.8, 0.8, 0.1);
	glBegin(GL_POLYGON); {
		glVertex3f(0, 2, 0.0);
		glVertex3f(2, 2, 0.0);
		glVertex3f(2, 0, 0.0);
		glVertex3f(0, 0, 0.0);
	}
	glEnd();

	if (globe.getGlobal()->option.KONAMI_TRIG) {
		globe.getGlobal()->beMyRain->drawRain();
	}
	glColor4f(0.25, 0.25, 0.25,0.6);
	glBegin(GL_POLYGON); {
		glVertex3f(0.8, 1.8, 0.0);
		glVertex3f(1.75, 1.8, 0.0);
		glVertex3f(1.75, 0.2, 0.0);
		glVertex3f(0.8, 0.2, 0.0);
	}
	glEnd();
}
void drawCreditBackButton() {
	glPushMatrix(); {
		glColor3f(0.8, 0.4, 0.3);
		glTranslatef(0.3, 1, 0);
		glutSolidSphere(0.1, 20, 20);
	}
	glPopMatrix();
}

void creditMouseEvent(int button, int state, int x, int y) {
	if (button == 0 && state == 0) {
		globe.getGlobal()->mouseDown = true;
		globe.getGlobal()->mX = x;
		globe.getGlobal()->mY = y;
	}
	if (button == 0 && state == 1) {
		globe.getGlobal()->mouseDown = false;
		if (sqrt(pow((x / 250.0) - 0.3, 2) + pow((y / 250) - 1, 2)) < 0.1) {
			curtain.setFlip(true);
		}
	}
}