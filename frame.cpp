#include"frame.h"
clock_t frames = 0;
string frameTitle = "frame:";
clock_t frame1time = 0, frame2time;

void setFrame() {
	frame2time = clock();
	frames = 1000 / (double)(frame2time - frame1time);
	frame1time = frame2time;

	frameTitle = "frame :";
	frameTitle.append(to_string(frames));
	glutPostRedisplay();
}
void drawFrame() {//프레임 숫자 띄우는거
	glPushMatrix(); {
		glLineWidth(2);
		
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
		for (size_t i = 0; i < frameTitle.length(); i++) {
			glColor3f(0.5, 0.5, 0.5);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, frameTitle[i]);
		}
		glColor3f(1, 1, 1);
	}
	/*cout << "frames!!!" << endl;*/
	glPopMatrix();
}