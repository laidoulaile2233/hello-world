#include<stdio.h>
#include<easyx.h>
/*
		整理需求文档思路
		1。菜单：
		开始游戏：进入 选择玩四子棋/五子棋
		继续游戏：返回上一局的游戏
		四子棋玩法介绍：进入玩法界面
		游戏设置：进入设置界面
		团队介绍：进入制作者名单
		充值：进入充值界面
		退出游戏：进入退出游戏界面

		2。a 四子棋游戏界面
					玩家使用鼠标操作
					点击退出按钮进入退出界面
					点击悔棋按钮悔棋
					黑白双方有血量，一方血量为0另一方胜利
					4个以上棋子连成线时消除棋子并且记分，过一回合将两方分相减，相减后扣除血量，
					一方血量小于等于0则另一方游戏胜利。
				b 五子棋游戏界面
					玩家使用鼠标操作
					点击退出按钮进入退出界面
					点击悔棋按钮悔棋
					5个棋子连成线时，连成线的那方胜利

		3.设置界面 ：进入游戏设置界面/进入音乐设置界面
*/
//--------------------------------------数据设计------------------------------------------
/*
记录数字（对应着界面）选择打印的界面
*/
int controll;
/*
表示当前回合数  偶数表示黑棋落子  奇数表示白棋落子
如: flag = 20 表示当前是第[20]次落子  由黑方落子
*/
int flag; //记录回合数

/*
0空地 1黑子 2白子
*/
int map[15][15];

/*
四子棋中双方的血量
数组便于在不同函数中传递血量
*/
int bloodBlack;
int bloodWhite;
/*
四子棋中双方的分数
*/
int pointBlack;
int pointWhite;

//优化逻辑;连子的判定（参考项目作业讲解）

#define MenuView 0
#define GameChoiceView 1
#define GameFourView 2
#define GameFiveView 3
#define FourIntroductionView 4
#define SetView 5
#define ProducerView 6
#define MoneyView 7

//--------------------------------------数据设计------------------------------------------

//--------------------------------------service------------------------------------------
/*
	负责人:洛泱
	功能: 初始化游戏数据
			  将棋盘的值初始化为0
			  当前回合设为黑棋(flag设为0)
			  bloodBlack==bloodWhite=5
	参数: void
	返回值: void
*/
void init();

/*
		*难点
		负责人：M
		功能：获得eazyx中落子的位置，求出鼠标对应在map中x，y的值并修改map[x][y]的值(根据flag判断改1/2)
					搜索map[x][y]判断此处是否能落子
					可以落子flag++
		参数：x y鼠标对应的坐标
		返回值：0不能落子
						1可以落子
*/
int swichXYandJudgement(int x, int y);

/*
		*难点
		负责人 :翔
		功能:根据数组map[x][y]中的值 判断落点后一方棋子是否连成4 / 5 / 6个（参考项目作业讲解）
					 若连成了就清除对应的棋子就加对应加分（flag判断）
		参数 : void
		返回值 : 0无连成4 / 5 / 6个
					   1连成4 / 5 / 6个
*/
int plusPoint();

/*
		负责人 :越钢
		功能:根据数组map[x][y]中的值 判断落点后一方棋子是否连成4 / 5 / 6个（参考项目作业讲解）若连成了就清除对应的棋子加对应加分（flag判断）
				 将两方分数相减，扣除的血量==两方分数相减的差
				  e.g.
						 pointBlack = 4 ; pointWhite  = 5;
						 bloodBlack = 5 ; bloodWhite = 5;
						 pointBlack-pointWhite==-1
						 黑方扣1滴血
						 最终bloodBlack = 4 ; bloodWhite = 5;（记得更改血量）
		参数 : void
		返回值 :0 没扣血
					  1 扣血
*/
int lossBlood();

/*
	*难点
	负责人:洛泱
	功能:根据数组map[x][y]中的值 判断落子后是否获胜（参考项目作业讲解）
			 根据flag判断谁胜利
	参数:void
	返回值:
		0表示没有获胜
		1表示黑子胜利
		2表示白子胜利
*/
int isWinFive();

/*
	负责人:M
	功能:一方血量小于等于0另一方胜利
	参数:void
	返回值:
		0表示没有获胜
		1表示黑子胜利
		2表示白子胜利
*/
int isWinFour();
//--------------------------------------service------------------------------------------

//--------------------------------------view--------------------------------------------
/*
		负责人：小新
		功能：
					调用相关函数打印对应界面（swich case 菜单为0......）（参考项目常用思路 1. 页面切换）
		参数：void
		返回值：void
*/
void controller();

/*
		负责人：佳佳
		功能：打印菜单（esayx中矩形函数）
					鼠标点击对应按钮 将controll赋值（鼠标点击开始游戏 controll=1）
		参数：void
		返回值：void
*/
void menuView();

/*
		负责人：蛇皮
		功能：点击开始游戏后打印 四子棋/五子棋（esayx中矩形函数）
					鼠标点击对应按钮 将flag赋值（鼠标点击四子棋 controll=2，鼠标点击五子棋 controll=3）
		参数：void
		返回值：void
*/
void gameChoiceView();

/*
		负责人：WK
		功能：1.打印四子棋游戏界面
					2. 调用函数init初始化
					3.获取鼠标点击时的坐标x y
					4.调用
							函数swichXYandJudgement
							函数printChess
							函数plusPoint
							函数lossBlood（记得更新血量显示）
							函数gameWinView
		参数：void
		返回值：void
*/
void gameFourView();

/*
		负责人：月庄
		功能：1.打印四子棋游戏界面
					2. 调用函数init初始化
					3.获取鼠标点击时的坐标x y
					4.调用函数
							swichXYandJudgement
							printChess
							isWinFive
							gameWinView
		参数：void
		返回值：void
*/
void gameFiveView();

/*
		负责人：小新  佳佳
		功能：打印胜利界面（黑/白）
		参数：void
		返回值：void
*/
void gameWinView();


/*
		*难点
		负责人：蛇皮
		功能：获取鼠标点击时的坐标x y
					鼠标点击棋盘落子（将对应棋子的图片贴在easyx的棋盘上）
		参数：void
		返回值：void
*/
void printChess(int x, int y);

/*
		负责人：WK
		功能：打印四子棋玩法介绍界面（controll=4）
		参数：void
		返回值：void
*/
void fourIntroductionView();

/*
		负责人：月庄
		功能：打印设置界面（ controll=5）
		参数：void
		返回值：void
*/
void setView();

/*
		负责人：WK
		功能：打印制作者名单界面（controll=6）
		参数：void
		返回值：void
*/
void producerView();

/*
		负责人：月庄
		功能：打印充值界面（ controll=7）
		参数：void
		返回值：void
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
	x，y是矩形的坐标
	w，h是矩形的宽和长
	*/
	int x = 100;
	int y = 100;
	int w = 50;
	int h = 30;

	while (true) {

		//绘图
		setbkmode(TRANSPARENT);
		BeginBatchDraw();
		cleardevice;
		//绘制按钮
		setfillcolor(BLUE);
		fillroundrect(x, y, x + w, y + h, 5, 5);//四子棋按钮
		fillroundrect(x + 100, y, x +100+w, y + h, 5, 5);//五子棋按钮

		//绘制文字
		int hSpace = (w - textwidth("四子棋")) / 2;
		int wSpace = (h - textheight("四子棋")) / 2;
		outtextxy(x + hSpace, y + wSpace, "四子棋");
		hSpace = (w - textwidth("五子棋")) / 2;
		wSpace = (h - textheight("五子棋")) / 2;
		outtextxy(x + 100 + hSpace, y + wSpace, "五子棋");
		EndBatchDraw();
		//判断改controll的值
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
	/*假设棋盘大小为600*600*/
	int size = 600;
	//格子数
	int geizi = 15;
	//long格子的长宽
	int l = size / geizi;
	//假设棋盘的起始点为90，90
	int qx = 100;
	int qy = 100;
	if (x> qx&&x< qx+size&&y>qy&&y<qy+size){
		//计算棋盘格索引（正方形所以xy大小一样）
		int centerXY= (x - 90) / l + 1;
		//计算打印图片的坐标
		int printXY = (centerXY - 1) * l+90;
		//打印图片
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

