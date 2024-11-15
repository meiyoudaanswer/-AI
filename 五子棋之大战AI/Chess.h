#pragma once
#include <graphics.h>
#include <vector>
using namespace std;


//定义两个枚举类型的整数，用于代表棋子颜色
typedef enum {
	CHESS_BLACK = 1,//黑方
	CHESS_WHITE = -1//白方
}chess_kind_t;

struct ChessPos {
	int row;
	int col;
	// 构造函数
	ChessPos(int r = 0, int c = 0);
};

class Chess
{
public:
	//构造函数
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//加载棋盘的图片资源，初始化棋盘相关数据
	void init();

	//判断点击是否有效，若有效则将坐标保存至pos
	bool clickBoard(int x, int y, ChessPos* pos);

	//在棋盘的指定位置落指定颜色的棋子
	void chessDown(ChessPos* pos, chess_kind_t kind);

	//获取指定位置棋子情况：黑、白、空
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//获取棋盘大小
	int getGradeSize();

	//判断棋局是否结束
	bool checkOver();

	//判断棋局胜负
	bool checkWin();

	//处理棋子图片的图形渲染接口
	void putimagePNG(int x, int y, IMAGE* picture);

private:
	//棋盘尺寸
	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	//储存当前棋盘与棋子的情况：空为0，黑为1，白为0
	vector<vector<int>> chessMap;

	//表示下棋方：黑为true，白为false
	bool playerFlag;

	//最近落子位置
	ChessPos lastPos;

	//更新棋盘数据
	void updateGameMap(ChessPos* pos);
};

