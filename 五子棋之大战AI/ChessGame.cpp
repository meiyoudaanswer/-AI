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
	man->init(chess);//��ʼ������
}

void ChessGame::play()
{
	chess->init();
	while (1) {
		man->go();
		if (chess->checkOver()) {//�ж�����Ƿ����
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

