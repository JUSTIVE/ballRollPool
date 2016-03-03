#include"ball.h"
#ifndef RELATION
#define RELATION
class Relation {
public:
	ball *a;
	ball *b;
	Relation(ball* a, ball* b) {
		this->a = a;
		this->b = b;
	}
};
#endif
