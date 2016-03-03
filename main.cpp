#include<time.h>
#include"pregame.h"
#include"ingame.h"
#include"credit.h"
#include"settings.h"
extern Global globe;
extern Curtain curtain;

GLboolean sling_trig = false;

void Konami2(unsigned char key, int x, int y) {
	cout << globe.getGlobal()->konamiStatus << endl;
	if (key == 'b') {
		if (globe.getGlobal()->konamiStatus == 8) {
			globe.getGlobal()->konamiStatus++;
		}
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}
	if (key == 'a') {
		if (globe.getGlobal()->konamiStatus == 9) {
			globe.getGlobal()->konamiStatus = 0;
			globe.getGlobal()->option.KONAMI_TRIG = (globe.getGlobal()->option.KONAMI_TRIG + 1) % 2;
			if (globe.getGlobal()->option.KONAMI_TRIG) {
				wchar_t title[13] = L"bbbgm.wav";
				PlaySound(title, NULL, SND_ASYNC | SND_LOOP | SND_SYSTEM);
			}
			else {
				wchar_t title[13] = L"titlebgm.wav";
				PlaySound(title, NULL, SND_ASYNC | SND_LOOP | SND_SYSTEM);
			}
		}
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}
	glutPostRedisplay();
}

void Konami(int key, int x, int y) {
	cout << globe.getGlobal()->konamiStatus<<endl;
	if (key == GLUT_KEY_UP) {
		if (((globe.getGlobal()->konamiStatus == 0) || (globe.getGlobal()->konamiStatus == 1)))
			globe.getGlobal()->konamiStatus++;
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}

	if (key == GLUT_KEY_DOWN) {
		if ((globe.getGlobal()->konamiStatus == 2) || (globe.getGlobal()->konamiStatus == 3)) {
			globe.getGlobal()->konamiStatus++;
		}
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}

	if (key == GLUT_KEY_LEFT) {
		if ((globe.getGlobal()->konamiStatus == 4) || (globe.getGlobal()->konamiStatus == 6)) {
			globe.getGlobal()->konamiStatus++;
		}
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}
	if (key == GLUT_KEY_LEFT) {
		if ((globe.getGlobal()->konamiStatus == 5) || (globe.getGlobal()->konamiStatus == 7)) {
			globe.getGlobal()->konamiStatus++;
		}
		else {
			globe.getGlobal()->konamiStatus = 0;
		}
	}
	
	glutPostRedisplay();
}

void ballInit() {
	 globe.getGlobal()->balls[0] = new ball(1, 0.6, 0,0);

	 globe.getGlobal()->balls[1] = new ball(1, 1.2, 1,1);

	 globe.getGlobal()->balls[2] = new ball(1 + RADIUS, 1.2 + (RADIUS * 2 * sqrt(3.0)) / 2, 2,2);
	 globe.getGlobal()->balls[3] = new ball(1 - RADIUS, 1.2 + (RADIUS * 2 * sqrt(3.0)) / 2, 3,1);

	 globe.getGlobal()->balls[4] = new ball(1 + 2 * RADIUS, 1.2 + 2 * (RADIUS * 2 * sqrt(3.0)) / 2, 4,1);
	 globe.getGlobal()->balls[5] = new ball(1, 1.2 + 2 * (RADIUS * 2 * sqrt(3.0)) / 2, 5,3);
	 globe.getGlobal()->balls[6] = new ball(1 - 2 * RADIUS, 1.2 + 2 * (RADIUS * 2 * sqrt(3.0)) / 2, 6,2);

	 globe.getGlobal()->balls[7] = new ball(1 + 3 * RADIUS, 1.2 + 3 * (RADIUS * 2 * sqrt(3.0)) / 2, 7,2);
	 globe.getGlobal()->balls[8] = new ball(1 + RADIUS, 1.2 + 3 * (RADIUS * 2 * sqrt(3.0)) / 2, 8,1);
	 globe.getGlobal()->balls[9] = new ball(1 - RADIUS, 1.2 + 3 * (RADIUS * 2 * sqrt(3.0)) / 2, 9,2);
	 globe.getGlobal()->balls[10] = new ball(1 - 3 * RADIUS, 1.2 + 3 * (RADIUS * 2 * sqrt(3.0)) / 2, 10,1);

	 globe.getGlobal()->balls[11] = new ball(1 + 4 * RADIUS, 1.2 + 4 * (RADIUS * 2 * sqrt(3.0)) / 2, 11,1);
	 globe.getGlobal()->balls[12] = new ball(1 + 2*RADIUS, 1.2 + 4 * (RADIUS * 2 * sqrt(3.0)) / 2, 12,2);
	 globe.getGlobal()->balls[13] = new ball(1 , 1.2 + 4 * (RADIUS * 2 * sqrt(3.0)) / 2, 13,1);
	 globe.getGlobal()->balls[14] = new ball(1 - 2 * RADIUS, 1.2 + 4 * (RADIUS * 2 * sqrt(3.0)) / 2, 14,2);
	 globe.getGlobal()->balls[15] = new ball(1 - 4 * RADIUS, 1.2 + 4 * (RADIUS * 2 * sqrt(3.0)) / 2, 15,2);
}
void update(){
	for (int i = 0; i < 16; i++) {
		//globe.getGlobal()->balls[i]->setForce
	}	
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (globe.getGlobal()->option.ANTIALIAS_TRIG) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}
	if(globe.getGlobal()->option.ALPHA_TRIG){
		glClear(GL_STENCIL_BUFFER_BIT);
		glEnable(GL_STENCIL_TEST);
	}
	switch (globe.getGlobal()->stage) {
	case 0://pregame
		if (globe.getGlobal()->settingTable == false) {
			glutMouseFunc(preGameMouseEvent);
			glutPassiveMotionFunc(preGameTracker);
			glutIdleFunc(preGameUpdater);
			glutKeyboardFunc(Konami2);
			glutSpecialFunc(Konami);
			curtain.reset();
			globe.getGlobal()->settingTable = true;
		}
		displayPreGame();
		break;
	case 1:	//ingame
		if (globe.getGlobal()->settingTable == false) {
			glutMouseFunc(inGameMouseEvent);
			glutMotionFunc(inGameTracker);
			glutIdleFunc(inGameUpdater);
			glutKeyboardFunc(Konami2);
			glutSpecialFunc(Konami);
			curtain.reset();
			globe.getGlobal()->game.playing = true;

			globe.getGlobal()->settingTable = true;
		}
		displayInGame();
		break;
	case 2://setting
		if (globe.getGlobal()->settingTable == false) {
			glutMouseFunc(settingsMouseEvent);
			glutMotionFunc(NULL);
			glutKeyboardFunc(Konami2);
			glutSpecialFunc(Konami);
			glutIdleFunc(settingUpdater);			
			curtain.reset();
			globe.getGlobal()->settingTable = true;
		}
		displaySettings();
		break;
	case 3://credit
		if (globe.getGlobal()->settingTable == false) {
			glutMouseFunc(creditMouseEvent);
			glutPassiveMotionFunc(NULL);
			glutKeyboardFunc(Konami2);
			glutSpecialFunc(Konami);
			glutIdleFunc(creditUpdater);
			curtain.reset();
			globe.getGlobal()->settingTable = true;
		}
		displayCredit();
		break;
	case 4://endGame
		if (globe.getGlobal()->settingTable == false) {
			curtain.reset();
			globe.getGlobal()->settingTable = true;
		}
		break;
	}
	
	glutSwapBuffers();
}
/////////////////////////
void MyReshape(int width, int height) {
	glutReshapeWindow(globe.getGlobal()->systemSize, globe.getGlobal()->systemSize);
}



void turnSwitch() {
	if (globe.getGlobal()->option.ALPHA_TRIG) {
		if (globe.getGlobal()->option.ALPHA_TRIG) {
			glClear(GL_STENCIL_BUFFER_BIT);
			glEnable(GL_STENCIL_TEST);
		}
	}
	else{
		glDisable(GL_STENCIL_TEST);
	}
	if (globe.getGlobal()->option.ANTIALIAS_TRIG) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
	}
	if (globe.getGlobal()->option.TEXTURE_TRIG) {
		glEnable(GL_TEXTURE_2D);		
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}

}



int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("pool");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(500, 500);
	
	glOrtho(0, 2, 0, 2, -1, 1);
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);

	ballInit();
	
	/*switch (globe.getGlobal()->stage) {
	case 0:
		glutPassiveMotionFunc(preGameTracker);
		glutIdleFunc(preGameUpdater);
		break;
	case 1:
		glutMouseFunc(inGameMouseEvent);
		glutMotionFunc(inGameTracker);
		
		
		glutIdleFunc(setFrame);
		break;
	case 2:
		break;
	}*/
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(render);
	if (globe.getGlobal()->option.SOUND_TRIG) {
		wchar_t title[13] = L"titlebgm.wav";
		PlaySound(title, NULL, SND_ASYNC | SND_LOOP | SND_SYSTEM);
	}
	glutMainLoop();
	return 0;
}