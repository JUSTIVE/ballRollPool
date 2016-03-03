#ifndef CURTAIN
#define CURTAIN
#include"GL.H"
class Curtain {
private:
	GLdouble curtainAlpha;
	GLint curtainFrame;
	GLboolean flip;
	
public:
	Curtain();
	void drawCurtain();
	GLdouble getAlpha();
	GLint getFrame();
	GLboolean getFlip();
	void setFlip(GLboolean flag);
	void reset();
};
#endif