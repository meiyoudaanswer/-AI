#include "Man.h"
#include "AI.h"
#include "Chess.h"
#include "ChessGame.h"
#include <iostream>

int main(void) {
	Chess chess(13, 44, 43, 67.4);
	Man man;
	AI ai;
	printf("《棋力对决之大战AI》五子棋大赛即将开幕！\n");
	printf("你是黑方\n准备好了吗？\n祝你胜利~");
	Sleep(2500);
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}