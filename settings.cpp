#include"settings.h"
extern Global globe;
extern Curtain curtain;
GLint settingSelect,settingPick;

void drawSettingsBack() {
	glColor3f(0.2, 0.8, 0.9);
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

	glColor4f(0.25, 0.25, 0.25, 0.6);
	glBegin(GL_POLYGON); {
		glVertex3f(0.8, 1.8, 0.0);
		glVertex3f(1.75, 1.8, 0.0);
		glVertex3f(1.75, 0.2, 0.0);
		glVertex3f(0.8, 0.2, 0.0);
	}
	glEnd();
}
void drawSettingItem() {
	glPushMatrix(); {
		glTranslatef(1.0, 1.5 - (1.0 / 8.0), 0);
		if (globe.getGlobal()->option.SOUND_TRIG == 1) {
			glColor3f(0.9, 0.9, 0);
			glutSolidCube(0.1);
		}
		else {
			glColor3f(0.2, 0.2, 0.2);
			glutSolidCube(0.1);
		}
	}
	glPopMatrix();

	glPushMatrix(); {
		glTranslatef(1.0, 1.5 - (3.0 / 8.0), 0);
		if (globe.getGlobal()->option.FRAME_TRIG == 1) {
			glColor3f(0.9, 0.9, 0);
			glutSolidCube(0.1);
		}
		else {
			glColor3f(0.2, 0.2, 0.2);
			glutSolidCube(0.1);
		}
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(1.0, 1.5 - (5.0 / 8.0), 0);
		if (globe.getGlobal()->option.ANTIALIAS_TRIG== 1) {
			glColor3f(0.9, 0.9, 0);
			glutSolidCube(0.1);
		}
		else{
			glColor3f(0.2, 0.2, 0.2);
			glutSolidCube(0.1);
		}
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(1.0, 1.5 - (7.0 / 8.0), 0);
		if (globe.getGlobal()->option.TEXTURE_TRIG == 1) {
			glColor3f(0.9, 0.9, 0);
			glutSolidCube(0.1);
		}
		else {
			glColor3f(0.2, 0.2, 0.2);
			glutSolidCube(0.1);
		}
	}
	glPopMatrix();
}
void drawSettingText() {
	
	string text = "SETTINGS";//, "SOUND", "FRAME", "LIGHT", "TEXTURE"

	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix(); {
		glLineWidth(2);
		glTranslatef(1.1, 1.7, 0.0);
		glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	glLineWidth(2);

	text = "SOUND";
	glPushMatrix(); {
		glTranslatef(1.3, 1.5-(1.0/8.0), 0.0);
		glScalef(1 / 2000.0, 1 / 2000.0, 1 / 2000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();

	text = "SHOW FPS";
	glPushMatrix(); {
		glTranslatef(1.3, 1.5 - (3.0 / 8.0), 0.0);
		glScalef(1 / 2000.0, 1 / 2000.0, 1 / 2000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	text = "ANTIALIAS";
	glPushMatrix(); {
		glTranslatef(1.3, 1.5 - (5.0 / 8.0), 0.0);
		glScalef(1 / 2000.0, 1 / 2000.0, 1 / 2000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	text = "TEXTURE";
	glPushMatrix(); {
		glTranslatef(1.3, 1.5 - (7.0 / 8.0), 0.0);
		glScalef(1 / 2000.0, 1 / 2000.0, 1 / 2000.0);
		for (int i = 0; i < text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	}
	glPopMatrix();
	
	
}
void settingsMouseEvent(int button, int state, int x, int y) {
	if (button == 0 && state == 0) {
		globe.getGlobal()->mouseDown = true;
		globe.getGlobal()->mX = x;
		globe.getGlobal()->mY = y;

		if ((globe.getGlobal()->mX >= 200 && globe.getGlobal()->mX < 436) && (globe.getGlobal()->mY >= 120) && (globe.getGlobal()->mY < 360)) {
			settingPick = (globe.getGlobal()->mY - 120) / 60;
			//cout << "pick" << settingPick << endl;
		}
	}
	if (button == 0 && state == 1) {
		globe.getGlobal()->mouseDown = false;
		if ((globe.getGlobal()->mX >= 200 && globe.getGlobal()->mX < 436) && (globe.getGlobal()->mY >= 120) && (globe.getGlobal()->mY < 360)) {
			settingSelect = (globe.getGlobal()->mY - 120) / 60;
			//cout << "select" << settingPick << endl;
			if (settingPick == settingSelect) {
				switch (settingPick)
				{
				case 0:
					if (globe.getGlobal()->option.SOUND_TRIG){
						PlaySound(NULL, 0, 0);
						globe.getGlobal()->option.SOUND_TRIG = 0;
					}
					else{
						
						if (globe.getGlobal()->option.KONAMI_TRIG) {
							wchar_t title[13] = L"bbbgm.wav";
							PlaySound(title, NULL, SND_ASYNC | SND_LOOP | SND_SYSTEM);
						}
						else {
							wchar_t title[13] = L"titlebgm.wav";
							PlaySound(title, NULL, SND_ASYNC | SND_LOOP | SND_SYSTEM);
						}
						
						globe.getGlobal()->option.SOUND_TRIG = 1;
					}
					break;
				case 1:
					if (globe.getGlobal()->option.FRAME_TRIG)
						globe.getGlobal()->option.FRAME_TRIG = 0;
					else
						globe.getGlobal()->option.FRAME_TRIG = 1;					
					glutPostRedisplay();
					break;
				case 2:
					if (globe.getGlobal()->option.ANTIALIAS_TRIG){
						globe.getGlobal()->option.ANTIALIAS_TRIG = 0;
						glDisable(GL_LINE_SMOOTH);
					}
					else{
						globe.getGlobal()->option.ANTIALIAS_TRIG = 1;
						glEnable(GL_LINE_SMOOTH);
					}
					glutPostRedisplay();
					break;					
				case 3:
					if (globe.getGlobal()->option.TEXTURE_TRIG)
						globe.getGlobal()->option.TEXTURE_TRIG = 0;
					else
						globe.getGlobal()->option.TEXTURE_TRIG = 1;
					glutPostRedisplay();
					break;
				}
			}
		}
		if (sqrt(pow((x/250.0) - 0.3, 2) + pow((y/250) - 1, 2)) < 0.1) {
			curtain.setFlip(true);
		}
	}	
}
void drawSettingsBackButton() {
	glPushMatrix(); {
		glColor3f(0.9, 0.9, 0);
		glTranslatef(0.3,1,0);
		glutSolidSphere(0.1, 20, 20);
	}
	glPopMatrix();
}
void displaySettings() {
	drawSettingsBack();
	drawSettingItem();
	drawSettingText();
	drawSettingsBackButton();
	curtain.drawCurtain();
}

void settingUpdater() {
	if (curtain.getFrame() == 60) {
		if(globe.getGlobal()->game.playing == true)
			globe.getGlobal()->stage = 1;
		else {
			globe.getGlobal()->stage = 0;
		}
		
		globe.getGlobal()->settingTable = false;
	}
	glutPostRedisplay();
}