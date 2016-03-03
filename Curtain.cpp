#include"Curtain.h"
Curtain curtain;
Curtain::Curtain() {
	curtainAlpha = 0;
	curtainFrame = 0;
	flip = false;
}
void Curtain::drawCurtain() {
	glPushMatrix(); {
		glColor4f(0.2, 0.2, 0.2, curtainAlpha);
		glBegin(GL_POLYGON); {
			glVertex3f(0, 2, 0.0);
			glVertex3f(2, 2, 0.0);
			glVertex3f(2, 0, 0.0);
			glVertex3f(0, 0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
	if (flip) {
		curtainAlpha += 1.0 / 60.0;
		if (curtainFrame < 60)
			curtainFrame += 1;
	}
}
GLdouble Curtain::getAlpha() { return this->curtainAlpha; }
GLint Curtain::getFrame() { return curtainFrame; }
GLboolean Curtain::getFlip() { return flip; }
void Curtain::setFlip(GLboolean flag) { this->flip = flag; }
void Curtain::reset() {
	this->curtainAlpha = 0;
	this->curtainFrame = 0;
	this->flip = false;
}