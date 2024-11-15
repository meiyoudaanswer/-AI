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

	//评分计算最优落棋位置
	void calculateScore();
	//遍历scoreMap寻找评分最高的位置
	ChessPos think();
};

