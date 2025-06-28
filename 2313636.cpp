#include<graphics.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<random>
#include<vector>
using namespace std;
const int width = 20;
const int origin_x = 10;
const int origin_y = 10;
const int end_x = 630;
const int end_y = 470;
const int origin_length = 15;
int deraction_x = -1;
int deraction_y = 0;
int num = 0;
int c_power = 0;
int snake_color = 0x0089BA;
int bk_color = 0x008F7A;
int line_color = RGB(55,88,66,64);
int food_color = 0x7C8ED3;
#define BUTTON_WIDTH 180
#define BUTTON_HEIGHT 50
#define BUTTON1_X 200
#define BUTTON1_Y 200
#define BUTTON2_X 200
#define BUTTON2_Y 300
class Pair_lo {
public:
	int x;
	int y;
	Pair_lo(int a, int b) {
		x = a;
		y = b;
	}
};
vector<Pair_lo> food_lo;
//���ߵ�����
void DrawUnitBlock(Pair_lo lo,int color) {
	setcolor(color);
	setfillcolor(color);
	fillrectangle(origin_x +lo.x * width, origin_y +lo.y * width, origin_x +(lo.x + 1) * width, origin_y +(lo.y + 1) * width);
	return;
}
//��������
void DrawbkUnitBlock(Pair_lo lo) {
	setcolor(line_color);
	setfillcolor(bk_color);
	fillrectangle(origin_x + lo.x * width, origin_y + lo.y * width, origin_x + (lo.x + 1) * width, origin_y + (lo.y + 1) * width);
	return;
}
//����
void DrawSnake(vector<Pair_lo> lo) {
	//����
	for (int i = 0; i < lo.size(); i++) {
		if (i == 0)DrawUnitBlock(lo[i], 0x5057A4);
		else DrawUnitBlock(lo[i], snake_color);
	}
	return;
}
//������
void drawBackground(vector<Pair_lo> lo) {
	for (int i = 0; i < lo.size(); i++) {
		DrawbkUnitBlock(lo[i]);
	}
	return;
}
//��ӡλ������
void print_lo(vector<Pair_lo> snake) {
	for (int i = 0; i < snake.size(); i++) {
		cout << '(' << snake[i].x << ',' << snake[i].y << ')' << ' ';
	}
	cout << endl << "-------------------------------------------------------------" << endl;
	return;
}
//�ж��Ƿ񴥵��߽�
bool Can_move_boundary(Pair_lo lo) {
	if (lo.x <= origin_x/width|| lo.x >= end_x / width|| lo.y <= origin_y / width|| lo.y >= end_y / width) {
		return false;
	}
	else {
		return true;
	}
}
//��ײ�ж�
bool Can_move_body(vector<Pair_lo> snake) {
	bool is_b = false;
	for (int i = 0; i < snake.size(); i++) {
		for (int j = 0; j < snake.size(); j++) {
			if (i != j && (snake[i].x == snake[j].x && snake[i].y == snake[j].y)) {
				is_b = true;
			}
		}
	}
	return !is_b;
}
//��Ϸ����
void end() {
	settextstyle(50, 0, _T("����"));
	settextcolor(RED);
	outtextxy(250, 100, _T("LOSER"));
	return;
}
//�Զ��ƶ�
void autoMove(vector<Pair_lo>& snake) {
	drawBackground(snake);
	if (c_power >= 10) {
		snake.erase(snake.begin());
	}
	c_power = c_power % 10;
	for (int i = snake.size() - 1; i > 0; i--) {
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	snake[0].x += deraction_x;
	snake[0].y += deraction_y;
	DrawSnake(snake);
	return;
}
//���ݼ��������ƶ�
void moveSnake(vector<Pair_lo>& snake,char in) {
	if (in == 'a') {
		deraction_x = -1;
		deraction_y = 0;
	}
	else if (in == 's') {
		deraction_x = 0;
		deraction_y = 1;
	}
	else if (in == 'd') {
		deraction_x = 1;
		deraction_y = 0;
	}
	else if (in == 'w') {
		deraction_x = 0;
		deraction_y = -1;
	}
	autoMove(snake);
	return;
}
void m_moveSnake(vector<Pair_lo>& snake, int x, int y) {
	//�����λ������ͷλ�ý��жԱ�
	if (x > snake[0].x*width) {
		deraction_x = 1;
	}
	else if(x<snake[0].x*width) {
		deraction_x = -1;
	}
	
	if (y > snake[0].y*width) {
		deraction_y = 1;
	}
	else if(y<snake[0].y*width) {
		deraction_y = -1;
	}
	autoMove(snake);
	return;
}
//ʳ������
void Product_food() {
	// ��������棺ʹ�� Mersenne Twister �㷨
	mt19937 rng(std::random_device{}());

	// �ֲ����������� 0 �� 99 ֮��ľ��ȷֲ�����
	uniform_int_distribution<int> dist_x(origin_x, end_x);
	uniform_int_distribution<int> dist_y(origin_y, end_y);
	uniform_int_distribution<int> dist_c(0, 2);
	// ���������
	int x = dist_x(rng);
	int y = dist_y(rng);
	int c = dist_c(rng);
	Pair_lo lo(x, y);
	food_lo.push_back(lo);
	setfillcolor(0x845EC2);
	setcolor(0x845EC2);
	fillcircle(x, y, 2);
	return;
}
//����䳤
void lengthen(vector<Pair_lo>& snake) {
	for (int i = 0; i < snake.size(); i++) {
		for (int j = 0; j < food_lo.size(); j++) {
			if ((food_lo[j].x >= snake[i].x * width && food_lo[j].x <= (snake[i].x + 1) * width) && food_lo[j].y) {
				num++;
				food_lo.erase(food_lo.begin() + j);
				j--;
			}
		}
	}
	int el = num / 10;
	num = num % 10;
	for (int i = 0; i < el; i++) {
		Pair_lo ne(snake[0].x + deraction_x, snake[0].y + deraction_y);
		snake.insert(snake.begin(), ne);
	}
	clearrectangle(100, 20, 150, 50);
	wstring leng = to_wstring(snake.size());
	settextcolor(0X8F72B9);
	settextstyle(30, 0, _T("����"));
	outtextxy(20, 20, _T("�߳���"));
	outtextxy(100, 20, leng.c_str());
	return;
}
//��ȡ�����
bool isInButton(int x, int y, int buttonX, int buttonY, int width, int height) {
	return x >= buttonX && x <= buttonX + width && y >= buttonY && y <= buttonY + height;
}
void key_move(vector<Pair_lo>& snake) {
	//��ʾ�������������ʼ��Ϸ
	//����q������Ϸ
	settextstyle(20, 0, _T("����"));
	settextcolor(line_color);
	outtextxy(500, 20, _T(" w  s  a  d "));
	outtextxy(500, 20 + 30, _T("�� �� �� ��"));
	outtextxy(500, 20 + 60, _T("q ������Ϸ"));
	_getch();//�߿�ʼ�ƶ�
	char in;
	while (true) {
		if (_kbhit()) {
			in = _getch();
			if (in == 'q') {
				end();
				break;
			}
			else {
				moveSnake(snake, in);
			}
		}
		else {
			autoMove(snake);
		}
		if (!(Can_move_boundary(snake[0]) && Can_move_body(snake))) {
			end();
			return;
		}
		c_power++;
		lengthen(snake);
		if (snake.size() <= 1) {
			end();
			return;
		}
		Product_food();
		Sleep(200);
	}
}
void mouse_move(vector<Pair_lo>& snake) {
	while (true) {
		ExMessage m;//����һ����Ϣ����
		if (peekmessage(&m, EM_MOUSE)) {
			m = getmessage(EM_MOUSE);//��ȡ�����Ϣ
			cout << m.x << ' ' << m.y << endl;
			cout << snake[0].x << ' ' << snake[0].y << endl;
			cout << deraction_x << ' ' << deraction_y << endl;
			//�������λ���ƶ�
			m_moveSnake(snake, m.x, m.y);
			
		}
		if (!(Can_move_boundary(snake[0]) && Can_move_body(snake))) {
			end();
			return;
		}
		c_power++;
		lengthen(snake);
		if (snake.size() <= 1) {
			end();
			return;
		}
		Product_food();
		Sleep(200);
	}
	return;
}
int main() {
	initgraph(640, 480);
	setbkcolor(0x008F7A);
	cleardevice();
	int width = 20;
	//���߽�
	setcolor(line_color);
	for (int i = 0; i < 640 / width; i++) {
		line(origin_x + i * width, origin_y, origin_x + i * width, end_y);
	}
	for (int i = 0; i < 480 / width; i++) {
		line(origin_x, origin_y + i * width, end_x, origin_y + i * width);
	}
	//��ʼ����
	settextcolor(0x3B6676);
	settextstyle(60, 0, _T("����"));
	//���Ʊ���
	outtextxy(200, 50, _T("̰����"));
	//���ư�ť
	setfillcolor(0x3B6676);
	settextstyle(20, 0, _T("����"));
	bar(BUTTON1_X,BUTTON1_Y, BUTTON1_X + BUTTON_WIDTH, BUTTON1_Y + BUTTON_HEIGHT);
	outtextxy(BUTTON1_X + 40, BUTTON1_Y + 15, _T("����ģʽ"));
	bar(BUTTON2_X,BUTTON2_Y, BUTTON2_X + BUTTON_WIDTH, BUTTON2_Y + BUTTON_HEIGHT);
	outtextxy(BUTTON2_X + 40, BUTTON2_Y + 15, _T("���ģʽ"));
	int mode = 0;
	while (true){
		if (MouseHit()) {  // ��������Ϣ
			MOUSEMSG msg = GetMouseMsg();
			// �ж��������Ƿ���
			if (msg.uMsg == WM_LBUTTONDOWN) {
				// �ж��Ƿ����˰�ť1
				if (isInButton(msg.x, msg.y, BUTTON1_X, BUTTON1_Y, BUTTON_WIDTH, BUTTON_HEIGHT)) {
					mode = 1;
					break;
				}
				// �ж��Ƿ����˰�ť2
				if (isInButton(msg.x, msg.y, BUTTON2_X, BUTTON2_Y, BUTTON_WIDTH, BUTTON_HEIGHT)) {
					mode = 2;
					break;
				}
			}
		}
	}
	setbkcolor(0x008F7A);
	cleardevice();
	//���߽�
	setcolor(line_color);
	for (int i = 0; i < 640 / width; i++) {
		line(origin_x + i * width, origin_y, origin_x + i * width, end_y);
	}
	for (int i = 0; i < 480 / width; i++) {
		line(origin_x, origin_y + i * width, end_x, origin_y + i * width);
	}
	//��һ��Ԫ��Ϊ��ͷ��λ��
	vector<Pair_lo> snake = {
		{10, 10},
		{11, 10},
		{12, 11},
		{13, 12},
		{14, 12},
		{15, 11},
		{16, 10},
		{17, 10},
		{18, 11},
		{19, 12},
		{20, 12},
		{21, 11},
		{22, 10},
		{23, 10},
		{24, 11},
		{25, 12}
	};
	// ��ʾ�ߵĳ���
	settextcolor(0X8F72B9);
	settextstyle(30, 0, _T("����"));
	outtextxy(20, 20, _T("�߳���"));
	wstring leng = to_wstring(snake.size());
	outtextxy(100, 20,leng.c_str());
	//����
	DrawSnake(snake);
	if (mode == 1) {
		key_move(snake);
	}
	else if (mode == 2) {
		mouse_move(snake);
	}
	(void)_getch();
	closegraph();
	return 0;
}