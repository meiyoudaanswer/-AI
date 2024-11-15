#include "Man.h"
#include "AI.h"
#include "Chess.h"
#include "ChessGame.h"
#include <iostream>


ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	ai->init(chess);
	man->init(chess);//初始化棋手
}

void ChessGame::play()
{
	chess->init();
	while (1) {
		man->go();
		if (chess->checkOver()) {//判断棋局是否结束
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}

