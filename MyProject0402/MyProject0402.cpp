#include <random>
#include <string>
#include <bangtal.h>




typedef struct {  //좌표 구조체
	int x;
	int y;
} Point;

SceneID scene1, scene2; //scene 1:시작 전 화면, scene2:시작 후 화면
ObjectID piece[32];	//조각 크기 300*416
ObjectID cardID[4][8];
int cardNO[4][8];
ObjectID blankID[4][8];	//빈 카드
Point clickPoint[2] = { {-1,-1},{-1,-1} };	//클릭한 카드 좌표
int foundCard = 0;	//찾은 카드의 개수

ObjectID buttonStart, buttonStart2, buttonEnd;
TimerID delayTimer;	//카드 보여지는 시간

TimerID limitTimer;	//시간 제한 타이머
SoundID sound;



void mouseCallback(ObjectID id, int x, int y, MouseAction act);
void timerCallback(TimerID id);
void clickCard(ObjectID id, int x, int y, MouseAction act);
void makeObject();	//오브젝트 생성
void startCard();	//카드 게임 시작
void mixCard(); //카드 조각 섞기
int getRandom(int min, int max);	//랜덤함수
int getX(int x);	//퍼즐 조각 x좌표
int getY(int y);	//퍼즐 조각 y좌표
Point getEmptyPos(int n);	//카드 배열에서 n번째 비어있는 좌표 가져오기

// 메인시작 함수
int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	makeObject();
	startGame(scene1);
}



// 마우스 콜백 함수
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



//카드 클릭 처리 함수
void clickCard(ObjectID id, int x, int y, MouseAction act)
{
	if (act != MouseAction::MOUSE_CLICK) return;
	if (clickPoint[1].x != -1) return;


	Point target = { -1,-1 };
	
	// 클릭한 카드 오브젝트 찾기
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
	
	if (target.x == -1) return;	//카드 조각이 아니면 리턴
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


//타이머 콜백 함수
void timerCallback(TimerID id)
{
	if (id == delayTimer) {
		if (getTimer(delayTimer) < 1)
		{
			if (cardNO[clickPoint[0].x][clickPoint[0].y] == cardNO[clickPoint[1].x][clickPoint[1].y]) {
				foundCard++;
				if (foundCard == 16) {
					stopTimer(limitTimer);
					std::string message = "완료!! (" + std::to_string(300 - (int)getTimer(limitTimer)) + "초)";
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
			showMessage("시간 초과, 실패");
			showObject(buttonStart);
			showObject(buttonEnd);
		}
	}
}


// 오브젝트 생성 함
void makeObject()
{
	scene1 = createScene("scene1", "Images/background.png");
	scene2 = createScene("scene2", "Images/background2.png");

	//첫 카드 쌍
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

	//빈 카드 생성
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++)
		{
			blankID[i][j] = createObject("Images/blank.png");
			scaleObject(blankID[i][j], 0.3f);
			locateObject(blankID[i][j], scene2, getX(j), getY(i));
			showObject(blankID[i][j]);
		}
	}
	
	delayTimer = createTimer(0.5f);	//카드 뒤집힌 시간 타이머
	limitTimer = createTimer(300.f);	//게임 시간제한 타이머
	
	//버튼 오브젝트 생성
	buttonStart = createObject("Images/start.png");
	buttonEnd = createObject("Images/end.png");
	buttonStart2 = createObject("Images/start.png");
	locateObject(buttonStart, scene2, 510, 30);
	locateObject(buttonEnd, scene2, 670, 30);
	locateObject(buttonStart2, scene1, 590, 50);
	showObject(buttonStart2);

	sound = createSound("18V Cordless Drill Switch.mp3");
}


//카드 게임 시작 함수
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
	//카드 번호 초기화
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cardNO[i][j] = INVALID_OBJECT;
		}
	}

	//카드 조각을 랜덤 배열에 넣기
	for (int i = 0; i < 32; i++) {
		Point point = getEmptyPos(getRandom(1, 32 - i));
		cardID[point.x][point.y] = piece[i];
		cardNO[point.x][point.y] = 1 + i % 16;  // 카드번호 1~16
	}	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j ++ ) {
			locateObject(cardID[i][j], scene2, getX(j), getY(i));
			showObject(blankID[i][j]);
		}
	}

}

// 카드 배열에서 n번째 비어있는 좌표 가져오기
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


int getX(int x) // 퍼즐 x좌표 계산
{
	int left = 200 + 110 * x;

	return left;
}


int getY(int y) // 퍼즐 y좌표 계산
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