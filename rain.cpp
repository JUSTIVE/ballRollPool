#include "rain.h"

Rain::Rain()
{
	srand((unsigned)time(NULL));
	this->rainInit();
}

void Rain::rainInit() {
	GLdouble length;
	GLdouble begin;
	GLdouble width;
	for (size_t i = 0; i < GIVE_ME_RAIN; i++) {
		length = (rand() % 3000 / 10000.0)+0.2;
		begin =( rand() % 1000 / 500.0)+2;
		this->x[i] = begin;
		begin = (rand() % 1000 / 500.0)+2;
		this->y[i] = begin;
		this->width[i]= rand() % 3000 / 500.0;

		this->x[i + (GIVE_ME_RAIN)] = x[i] - length;
		this->y[i + (GIVE_ME_RAIN)] = y[i] - length;
		velo[i] = (0.5 - length) / 60;
	}
}

void Rain::drawRain() {
	for (size_t i = 0; i<GIVE_ME_RAIN; i++) {
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP); {
			glLineWidth(width[i]);
			glVertex3f(x[i], y[i], 0);
			glVertex3f(x[i + GIVE_ME_RAIN], y[i + GIVE_ME_RAIN], 0);
		}
		glEnd();		
	}
	rainDrop();
	reRain();
}

void Rain::rainDrop() {
	for (size_t i = 0; i < GIVE_ME_RAIN; i++) {
		x[i] -= velo[i];
		x[i + GIVE_ME_RAIN] -= velo[i];
		y[i] -= velo[i];
		y[i + GIVE_ME_RAIN] -= velo[i];
	}
}
void Rain::reRain() {
	for (size_t i = 0; i < GIVE_ME_RAIN; i++) {
		if (x[i] < 0 || y[i]<0) {
			GLdouble length;
			GLdouble begin;
			GLdouble width;
			length = (rand() % 2000 / 10000.0)+0.2;
			begin = (rand() % 1000 / 500.0)+2;
			this->x[i] = begin;
			begin = (rand() % 1000 / 500.0)+2;
			this->y[i] = begin;

			this->width[i] = rand() % 3000 / 500.0;
			this->x[i + (GIVE_ME_RAIN)] = x[i] - length;
			this->y[i + (GIVE_ME_RAIN)] = y[i] - length;
			velo[i] = (0.5 - length) / 60;
		}
	}
}