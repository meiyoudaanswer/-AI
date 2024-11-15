#pragma once
#include "Chess.h"

class AI
{
public:
	void init(Chess* chess);
	void go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

	//���ּ�����������λ��
	void calculateScore();
	//����scoreMapѰ��������ߵ�λ��
	ChessPos think();
};

