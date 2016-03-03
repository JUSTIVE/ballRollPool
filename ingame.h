#include"global.h"
#include"frame.h"
#include"Curtain.h"

void displayInGame();
	//배경 렌더링
	void drawInGameBack();
		//타일
		void drawTile();
		//당구대
		void drawPool();
		//파워 게이지
		void drawGauge();
		//구멍
		void drawGoalPot();
	//공
	void drawBall();
		//그림자
		void drawEllipse(float radiusX, float radiusY);
	//큐대
	void drawCueLine();
	//설정버튼
	void drawSetting();



void moveBall();//매 프레임마다 호출되는 공 이동 연산
	//다음 프레임에 대한 연산
	//힘초기화
	void forceInit(ball* b);
	//공 충돌
	void ballCollision();
		//충돌합니까?
		bool ballsAreColliding(ball* a, ball * b);
		//힘을 건네줍니다
		void giveForce(ball*a, ball*b);
		void passiveCollsion(ball*a, ball* b);
	
	//구멍에 넣었는가?
	void checkGoal(ball* b);
	//벽에 닿았는가?
	void collisionBoundary(ball* b);
	//공 이동
	void EulerSolver(ball* b, GLdouble dt);
	//움직일때 느려지는 속도
	void groundFriction(ball* b);
	

//이벤트
void inGameMouseEvent(int button, int state, int x, int y);
void inGameTracker(int x, int y);
//아이들
void inGameUpdater();
void sling();


//파울
void foulRule();
void foulMouseEvent(int button, int state, int x, int y);
void foulPassiveMotionEvent(int x, int y);
//시스템메세지
void drawSystemMessage();
string setSYSMSG();