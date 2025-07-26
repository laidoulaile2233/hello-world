#include<stdio.h>
#include<easyx.h>
/*
		���������ĵ�˼·
		1���˵���
		��ʼ��Ϸ������ ѡ����������/������
		������Ϸ��������һ�ֵ���Ϸ
		�������淨���ܣ������淨����
		��Ϸ���ã��������ý���
		�Ŷӽ��ܣ���������������
		��ֵ�������ֵ����
		�˳���Ϸ�������˳���Ϸ����

		2��a ��������Ϸ����
					���ʹ��������
					����˳���ť�����˳�����
					������尴ť����
					�ڰ�˫����Ѫ����һ��Ѫ��Ϊ0��һ��ʤ��
					4����������������ʱ�������Ӳ��ҼǷ֣���һ�غϽ�����������������۳�Ѫ����
					һ��Ѫ��С�ڵ���0����һ����Ϸʤ����
				b ��������Ϸ����
					���ʹ��������
					����˳���ť�����˳�����
					������尴ť����
					5������������ʱ�������ߵ��Ƿ�ʤ��

		3.���ý��� ��������Ϸ���ý���/�����������ý���
*/
//--------------------------------------�������------------------------------------------
/*
��¼���֣���Ӧ�Ž��棩ѡ���ӡ�Ľ���
*/
int controll;
/*
��ʾ��ǰ�غ���  ż����ʾ��������  ������ʾ��������
��: flag = 20 ��ʾ��ǰ�ǵ�[20]������  �ɺڷ�����
*/
int flag; //��¼�غ���

/*
0�յ� 1���� 2����
*/
int map[15][15];

/*
��������˫����Ѫ��
��������ڲ�ͬ�����д���Ѫ��
*/
int bloodBlack;
int bloodWhite;
/*
��������˫���ķ���
*/
int pointBlack;
int pointWhite;

//�Ż��߼�;���ӵ��ж����ο���Ŀ��ҵ���⣩

#define MenuView 0
#define GameChoiceView 1
#define GameFourView 2
#define GameFiveView 3
#define FourIntroductionView 4
#define SetView 5
#define ProducerView 6
#define MoneyView 7

//--------------------------------------�������------------------------------------------

//--------------------------------------service------------------------------------------
/*
	������:����
	����: ��ʼ����Ϸ����
			  �����̵�ֵ��ʼ��Ϊ0
			  ��ǰ�غ���Ϊ����(flag��Ϊ0)
			  bloodBlack==bloodWhite=5
	����: void
	����ֵ: void
*/
void init();

/*
		*�ѵ�
		�����ˣ�M
		���ܣ����eazyx�����ӵ�λ�ã��������Ӧ��map��x��y��ֵ���޸�map[x][y]��ֵ(����flag�жϸ�1/2)
					����map[x][y]�жϴ˴��Ƿ�������
					��������flag++
		������x y����Ӧ������
		����ֵ��0��������
						1��������
*/
int swichXYandJudgement(int x, int y);

/*
		*�ѵ�
		������ :��
		����:��������map[x][y]�е�ֵ �ж�����һ�������Ƿ�����4 / 5 / 6�����ο���Ŀ��ҵ���⣩
					 �������˾������Ӧ�����ӾͼӶ�Ӧ�ӷ֣�flag�жϣ�
		���� : void
		����ֵ : 0������4 / 5 / 6��
					   1����4 / 5 / 6��
*/
int plusPoint();

/*
		������ :Խ��
		����:��������map[x][y]�е�ֵ �ж�����һ�������Ƿ�����4 / 5 / 6�����ο���Ŀ��ҵ���⣩�������˾������Ӧ�����ӼӶ�Ӧ�ӷ֣�flag�жϣ�
				 ����������������۳���Ѫ��==������������Ĳ�
				  e.g.
						 pointBlack = 4 ; pointWhite  = 5;
						 bloodBlack = 5 ; bloodWhite = 5;
						 pointBlack-pointWhite==-1
						 �ڷ���1��Ѫ
						 ����bloodBlack = 4 ; bloodWhite = 5;���ǵø���Ѫ����
		���� : void
		����ֵ :0 û��Ѫ
					  1 ��Ѫ
*/
int lossBlood();

/*
	*�ѵ�
	������:����
	����:��������map[x][y]�е�ֵ �ж����Ӻ��Ƿ��ʤ���ο���Ŀ��ҵ���⣩
			 ����flag�ж�˭ʤ��
	����:void
	����ֵ:
		0��ʾû�л�ʤ
		1��ʾ����ʤ��
		2��ʾ����ʤ��
*/
int isWinFive();

/*
	������:M
	����:һ��Ѫ��С�ڵ���0��һ��ʤ��
	����:void
	����ֵ:
		0��ʾû�л�ʤ
		1��ʾ����ʤ��
		2��ʾ����ʤ��
*/
int isWinFour();
//--------------------------------------service------------------------------------------

//--------------------------------------view--------------------------------------------
/*
		�����ˣ�С��
		���ܣ�
					������غ�����ӡ��Ӧ���棨swich case �˵�Ϊ0......�����ο���Ŀ����˼· 1. ҳ���л���
		������void
		����ֵ��void
*/
void controller();

/*
		�����ˣ��Ѽ�
		���ܣ���ӡ�˵���esayx�о��κ�����
					�������Ӧ��ť ��controll��ֵ���������ʼ��Ϸ controll=1��
		������void
		����ֵ��void
*/
void menuView();

/*
		�����ˣ���Ƥ
		���ܣ������ʼ��Ϸ���ӡ ������/�����壨esayx�о��κ�����
					�������Ӧ��ť ��flag��ֵ������������� controll=2������������� controll=3��
		������void
		����ֵ��void
*/
void gameChoiceView();

/*
		�����ˣ�WK
		���ܣ�1.��ӡ��������Ϸ����
					2. ���ú���init��ʼ��
					3.��ȡ�����ʱ������x y
					4.����
							����swichXYandJudgement
							����printChess
							����plusPoint
							����lossBlood���ǵø���Ѫ����ʾ��
							����gameWinView
		������void
		����ֵ��void
*/
void gameFourView();

/*
		�����ˣ���ׯ
		���ܣ�1.��ӡ��������Ϸ����
					2. ���ú���init��ʼ��
					3.��ȡ�����ʱ������x y
					4.���ú���
							swichXYandJudgement
							printChess
							isWinFive
							gameWinView
		������void
		����ֵ��void
*/
void gameFiveView();

/*
		�����ˣ�С��  �Ѽ�
		���ܣ���ӡʤ�����棨��/�ף�
		������void
		����ֵ��void
*/
void gameWinView();


/*
		*�ѵ�
		�����ˣ���Ƥ
		���ܣ���ȡ�����ʱ������x y
					������������ӣ�����Ӧ���ӵ�ͼƬ����easyx�������ϣ�
		������void
		����ֵ��void
*/
void printChess(int x, int y);

/*
		�����ˣ�WK
		���ܣ���ӡ�������淨���ܽ��棨controll=4��
		������void
		����ֵ��void
*/
void fourIntroductionView();

/*
		�����ˣ���ׯ
		���ܣ���ӡ���ý��棨 controll=5��
		������void
		����ֵ��void
*/
void setView();

/*
		�����ˣ�WK
		���ܣ���ӡ�������������棨controll=6��
		������void
		����ֵ��void
*/
void producerView();

/*
		�����ˣ���ׯ
		���ܣ���ӡ��ֵ���棨 controll=7��
		������void
		����ֵ��void
*/
void moneyView();


//--------------------------------------view--------------------------------------------


int main() {
	controller();
	return 0;
}


void init() {}


int swichXYandJudgement(int x, int y) {
	return 0;
}


int plusPoint() {
	return 0;
}


int lossBlood(){
	int diff = pointBlack - pointWhite;
	if (diff < 0)
	{
		bloodBlack += diff;
		if (bloodBlack < 0)
		{
			bloodBlack = 0;
		}
		return 1;
	}
	else if (diff > 0)
	{
		bloodWhite -= diff;
		if (bloodWhite < 0)
		{
			bloodWhite = 0;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


int isWinFive() {
	return 0;
}


int isWinFour() {
	return 0;
}


void controller() {}


void menuView() {}


void gameChoiceView() {
	/*
	x��y�Ǿ��ε�����
	w��h�Ǿ��εĿ�ͳ�
	*/
	int x = 100;
	int y = 100;
	int w = 50;
	int h = 30;

	while (true) {

		//��ͼ
		setbkmode(TRANSPARENT);
		BeginBatchDraw();
		cleardevice;
		//���ư�ť
		setfillcolor(BLUE);
		fillroundrect(x, y, x + w, y + h, 5, 5);//�����尴ť
		fillroundrect(x + 100, y, x +100+w, y + h, 5, 5);//�����尴ť

		//��������
		int hSpace = (w - textwidth("������")) / 2;
		int wSpace = (h - textheight("������")) / 2;
		outtextxy(x + hSpace, y + wSpace, "������");
		hSpace = (w - textwidth("������")) / 2;
		wSpace = (h - textheight("������")) / 2;
		outtextxy(x + 100 + hSpace, y + wSpace, "������");
		EndBatchDraw();
		//�жϸ�controll��ֵ
		ExMessage msg = { 0 };
		if (peekmessage(&msg, EX_MOUSE)) {}
		if (msg.message==WM_LBUTTONDOWN&&msg.x>x&&msg.x<x+w&&msg.y>y&&msg.y<y+h)
		{
			controll = 2;
		}
		if (msg.message == WM_LBUTTONDOWN && msg.x > x+100 && msg.x<x +100+ w && msg.y>y && msg.y < y + h)
		{
			controll = 3;
		}
	}
}


void gameFourView() {}


void gameFiveView() {}


void gameFiveWinView() {}


void gameFourWinView() {}

void printChess(int x, int y) {
	/*�������̴�СΪ600*600*/
	int size = 600;
	//������
	int geizi = 15;
	//long���ӵĳ���
	int l = size / geizi;
	//�������̵���ʼ��Ϊ90��90
	int qx = 100;
	int qy = 100;
	if (x> qx&&x< qx+size&&y>qy&&y<qy+size){
		//�������̸�����������������xy��Сһ����
		int centerXY= (x - 90) / l + 1;
		//�����ӡͼƬ������
		int printXY = (centerXY - 1) * l+90;
		//��ӡͼƬ
		BeginBatchDraw();
		IMAGE B;
		IMAGE W;
		if (flag % 2 == 0) {
			loadimage(&B, "assets/B.png");
			putimage(printXY, printXY, &B);
		}
		else {
			loadimage(&W, "assets/W.png");
			putimage(printXY, printXY, &W);
		}
		EndBatchDraw();
	}
}


void fourIntroductionView(){}


void setView(){}


void producerView(){}


void moneyView(){}

