#include"global.h"
Global globe;

Options::Options() {
	this->TEXTURE_TRIG = 0;
	this->ANTIALIAS_TRIG = 0;
	this->CAMERA_TRIG = 0;
	this->FRAME_TRIG=1;
	this->SOUND_TRIG = 1;
	this->ALPHA_TRIG = 1;
	this->ANTIALIAS_TRIG = 1;
	this->KONAMI_TRIG=0;
}
Game::Game() {
	this->player = 0;
	this->playing = false;
	this->foul = false;
}
GlobalSingleTone::GlobalSingleTone() {
	this->konamiStatus = 0;
	this->stage = 0;
	this->mouseDown = false;
	this->slingDist= 0;
	this->settingTable = false;
	this->systemSize = 500;
	this->normValue = 130;

	this->beMyRain=new Rain();

}
GlobalSingleTone * Global::generator() {
	GlobalSingleTone * rtn;
	if (this->variable == NULL) {
		rtn = new GlobalSingleTone();
		return rtn;
	}
	else {
		return this->variable;
	}
}

Global::Global() {
	variable = NULL;
	variable = generator();
}

GlobalSingleTone * Global::getGlobal() { return this->variable; }
