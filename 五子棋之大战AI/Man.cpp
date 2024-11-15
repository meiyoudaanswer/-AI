#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;//判断鼠标左键是否点击并且点击是否有效
		}
	}

	chess->chessDown(&pos, CHESS_BLACK);//人落黑子
}
