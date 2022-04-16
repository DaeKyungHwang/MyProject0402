#include <random>
#include <string>
#include <bangtal.h>




typedef struct {  //��ǥ ����ü
	int x;
	int y;
} Point;

SceneID scene1, scene2; //scene 1:���� �� ȭ��, scene2:���� �� ȭ��
ObjectID piece[32];	//���� ũ�� 300*416
ObjectID cardID[4][8];
int cardNO[4][8];
ObjectID blankID[4][8];	//�� ī��
Point clickPoint[2] = { {-1,-1},{-1,-1} };	//Ŭ���� ī�� ��ǥ
int foundCard = 0;	//ã�� ī���� ����

ObjectID buttonStart, buttonStart2, buttonEnd;
TimerID delayTimer;	//ī�� �������� �ð�

TimerID limitTimer;	//�ð� ���� Ÿ�̸�
SoundID sound;



void mouseCallback(ObjectID id, int x, int y, MouseAction act);
void timerCallback(TimerID id);
void clickCard(ObjectID id, int x, int y, MouseAction act);
void makeObject();	//������Ʈ ����
void startCard();	//ī�� ���� ����
void mixCard(); //ī�� ���� ����
int getRandom(int min, int max);	//�����Լ�
int getX(int x);	//���� ���� x��ǥ
int getY(int y);	//���� ���� y��ǥ
Point getEmptyPos(int n);	//ī�� �迭���� n��° ����ִ� ��ǥ ��������

// ���ν��� �Լ�
int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	makeObject();
	startGame(scene1);
}



// ���콺 �ݹ� �Լ�
void mouseCallback(ObjectID id, int x, int y, MouseAction act)
{
	if(getTimer(limitTimer)>0)
		clickCard(id, x, y, act);
	
	if (id == buttonStart) {
		if(act == MouseAction::MOUSE_CLICK)
			startCard();
	}
	else if (id == buttonEnd) {
		if (act == MouseAction::MOUSE_CLICK)
			endGame();
	}
	if (id == buttonStart2) {
		enterScene(scene2);
		startCard();
		hideObject(buttonStart2);
	}
}



//ī�� Ŭ�� ó�� �Լ�
void clickCard(ObjectID id, int x, int y, MouseAction act)
{
	if (act != MouseAction::MOUSE_CLICK) return;
	if (clickPoint[1].x != -1) return;


	Point target = { -1,-1 };
	
	// Ŭ���� ī�� ������Ʈ ã��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (id == blankID[i][j]) {
				target.x = i;
				target.y = j;
				break;
			}
		}
		if (target.x != -1) break;
	}
	
	if (target.x == -1) return;	//ī�� ������ �ƴϸ� ����
	if (clickPoint[0].x == -1) {
		clickPoint[0].x = target.x;
		clickPoint[0].y = target.y;
	}
	else {
		clickPoint[1].x = target.x;
		clickPoint[1].y = target.y;

		setTimer(delayTimer, 0.5f);
		startTimer(delayTimer);
	}
	hideObject(blankID[target.x][target.y]);

	playSound(sound);
}


//Ÿ�̸� �ݹ� �Լ�
void timerCallback(TimerID id)
{
	if (id == delayTimer) {
		if (getTimer(delayTimer) < 1)
		{
			if (cardNO[clickPoint[0].x][clickPoint[0].y] == cardNO[clickPoint[1].x][clickPoint[1].y]) {
				foundCard++;
				if (foundCard == 16) {
					stopTimer(limitTimer);
					std::string message = "�Ϸ�!! (" + std::to_string(300 - (int)getTimer(limitTimer)) + "��)";
					showMessage(message.c_str());
					showObject(buttonStart);
					showObject(buttonEnd);
				}
			}
			else {
				showObject(blankID[clickPoint[0].x][clickPoint[0].y]);
				showObject(blankID[clickPoint[1].x][clickPoint[1].y]);
				
			}
			clickPoint[0].x = -1;
			clickPoint[1].x = -1;
		}
	}
	else if (id == limitTimer) {
		if (getTimer(limitTimer) < 1)
		{
			showMessage("�ð� �ʰ�, ����");
			showObject(buttonStart);
			showObject(buttonEnd);
		}
	}
}


// ������Ʈ ���� ��
void makeObject()
{
	scene1 = createScene("scene1", "Images/background.png");
	scene2 = createScene("scene2", "Images/background2.png");

	//ù ī�� ��
	piece[0] = createObject("Images/1.png");
	piece[1] = createObject("Images/2.png");
	piece[2] = createObject("Images/3.png");
	piece[3] = createObject("Images/4.png");
	piece[4] = createObject("Images/5.png");
	piece[5] = createObject("Images/6.png");
	piece[6] = createObject("Images/7.png");
	piece[7] = createObject("Images/8.png");
	piece[8] = createObject("Images/9.png");
	piece[9] = createObject("Images/10.png");
	piece[10] = createObject("Images/11.png");
	piece[11] = createObject("Images/12.png");
	piece[12] = createObject("Images/13.png");
	piece[13] = createObject("Images/14.png");
	piece[14] = createObject("Images/15.png");
	piece[15] = createObject("Images/16.png");
	piece[16] = createObject("Images/1.png");
	piece[17] = createObject("Images/2.png");
	piece[18] = createObject("Images/3.png");
	piece[19] = createObject("Images/4.png");
	piece[20] = createObject("Images/5.png");
	piece[21] = createObject("Images/6.png");
	piece[22] = createObject("Images/7.png");
	piece[23] = createObject("Images/8.png");
	piece[24] = createObject("Images/9.png");
	piece[25] = createObject("Images/10.png");
	piece[26] = createObject("Images/11.png");
	piece[27] = createObject("Images/12.png");
	piece[28] = createObject("Images/13.png");
	piece[29] = createObject("Images/14.png");
	piece[30] = createObject("Images/15.png");
	piece[31] = createObject("Images/16.png");
	
	for (int i = 0; i < 32; i++) {
		scaleObject(piece[i], 0.3f);
		locateObject(piece[i], scene2, 0, 0);
		showObject(piece[i]);
	}

	//�� ī�� ����
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++)
		{
			blankID[i][j] = createObject("Images/blank.png");
			scaleObject(blankID[i][j], 0.3f);
			locateObject(blankID[i][j], scene2, getX(j), getY(i));
			showObject(blankID[i][j]);
		}
	}
	
	delayTimer = createTimer(0.5f);	//ī�� ������ �ð� Ÿ�̸�
	limitTimer = createTimer(300.f);	//���� �ð����� Ÿ�̸�
	
	//��ư ������Ʈ ����
	buttonStart = createObject("Images/start.png");
	buttonEnd = createObject("Images/end.png");
	buttonStart2 = createObject("Images/start.png");
	locateObject(buttonStart, scene2, 510, 30);
	locateObject(buttonEnd, scene2, 670, 30);
	locateObject(buttonStart2, scene1, 590, 50);
	showObject(buttonStart2);

	sound = createSound("18V Cordless Drill Switch.mp3");
}


//ī�� ���� ���� �Լ�
void startCard()
{
	hideObject(buttonStart);
	hideObject(buttonEnd);
	foundCard = 0;
	clickPoint[0].x = -1;
	clickPoint[1].x = -1;
	mixCard();
	setTimer(limitTimer, 300.f);
	startTimer(limitTimer);
	showTimer(limitTimer);
	enterScene(scene2);
}


void mixCard()
{
	//ī�� ��ȣ �ʱ�ȭ
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cardNO[i][j] = INVALID_OBJECT;
		}
	}

	//ī�� ������ ���� �迭�� �ֱ�
	for (int i = 0; i < 32; i++) {
		Point point = getEmptyPos(getRandom(1, 32 - i));
		cardID[point.x][point.y] = piece[i];
		cardNO[point.x][point.y] = 1 + i % 16;  // ī���ȣ 1~16
	}	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j ++ ) {
			locateObject(cardID[i][j], scene2, getX(j), getY(i));
			showObject(blankID[i][j]);
		}
	}

}

// ī�� �迭���� n��° ����ִ� ��ǥ ��������
Point getEmptyPos(int n)
{
	Point point = { -1,-1 };
	int count = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (cardNO[i][j] == INVALID_OBJECT) count++;
			if (count == n) {
				point.x = i;
				point.y = j;
				return point;
			}
		}
	}

	return point;
}


int getX(int x) // ���� x��ǥ ���
{
	int left = 200 + 110 * x;

	return left;
}


int getY(int y) // ���� y��ǥ ���
{
	int top = 530 - 150 * y;

	return top;
}

int getRandom(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int>dist(min, max);

	return dist(gen);
}