#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);//初始化分值
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);//停顿一秒假装思考
	chess->chessDown(&pos, CHESS_WHITE);
}


//评分计算最优落棋位置
void AI::calculateScore()
{
	//统计已经连成的同色棋子
	int personNum = 0;//连续黑子个数
	int aiNum = 0;//连续白子个数
	int emptyNum = 0;//各方向空位数

	//初始化评分数组
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap.size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//对每个点进行计算，有棋子则跳过
			if (chess->getChessData(row, col)) continue;

			//遍历八个方向中的一侧，共四个方向（-1，-1）（0，-1）（1，-1）（1,0）
			for (int y = -1; y <= 0; y++) {        //Y的范围是-1， 0
				for (int x = -1; x <= 1; x++) {    //X的范围是 -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //当y=0时，仅允许x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// 对黑棋评分
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;//此处有黑子
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;//此处是空位
							break;
						}
						else {
							break;//出边界了
						}
					}

					// 反向继续计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personNum == 1) { //连2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {//连3
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;//死3
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;//活3
						}
					}
					else if (personNum == 3) {//连4
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;//死4
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 5000;//活4
						}
					}
					else if (personNum == 4) {//连5
						scoreMap[row][col] = 20000;
					}

					// 对白棋评分（只有累加的分值与黑棋不同）
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {//普通下子
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {//连2
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {//连三
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;//死3
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;//活3
						}
					}
					else if (aiNum == 3) {//连4
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;//死4
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;//活4
						}
					}
					else if (aiNum >= 4) {//连5
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	//进行评分
	calculateScore();

	int maxScore = 0;
	vector<ChessPos> maxPoints;
	int k = 0;

	//遍历scoreMap
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//该位置是空的才存
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {//如果有多个最大的数，都存
					maxPoints.push_back(ChessPos(row, col));
				 }
			}
		}
	}

	//如果存了多个点，随机落一个
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
