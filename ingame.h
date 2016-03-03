#include"global.h"
#include"frame.h"
#include"Curtain.h"

void displayInGame();
	//��� ������
	void drawInGameBack();
		//Ÿ��
		void drawTile();
		//�籸��
		void drawPool();
		//�Ŀ� ������
		void drawGauge();
		//����
		void drawGoalPot();
	//��
	void drawBall();
		//�׸���
		void drawEllipse(float radiusX, float radiusY);
	//ť��
	void drawCueLine();
	//������ư
	void drawSetting();



void moveBall();//�� �����Ӹ��� ȣ��Ǵ� �� �̵� ����
	//���� �����ӿ� ���� ����
	//���ʱ�ȭ
	void forceInit(ball* b);
	//�� �浹
	void ballCollision();
		//�浹�մϱ�?
		bool ballsAreColliding(ball* a, ball * b);
		//���� �ǳ��ݴϴ�
		void giveForce(ball*a, ball*b);
		void passiveCollsion(ball*a, ball* b);
	
	//���ۿ� �־��°�?
	void checkGoal(ball* b);
	//���� ��Ҵ°�?
	void collisionBoundary(ball* b);
	//�� �̵�
	void EulerSolver(ball* b, GLdouble dt);
	//�����϶� �������� �ӵ�
	void groundFriction(ball* b);
	

//�̺�Ʈ
void inGameMouseEvent(int button, int state, int x, int y);
void inGameTracker(int x, int y);
//���̵�
void inGameUpdater();
void sling();


//�Ŀ�
void foulRule();
void foulMouseEvent(int button, int state, int x, int y);
void foulPassiveMotionEvent(int x, int y);
//�ý��۸޼���
void drawSystemMessage();
string setSYSMSG();