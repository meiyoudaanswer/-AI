#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);//��ʼ����ֵ
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);//ͣ��һ���װ˼��
	chess->chessDown(&pos, CHESS_WHITE);
}


//���ּ�����������λ��
void AI::calculateScore()
{
	//ͳ���Ѿ����ɵ�ͬɫ����
	int personNum = 0;//�������Ӹ���
	int aiNum = 0;//�������Ӹ���
	int emptyNum = 0;//�������λ��

	//��ʼ����������
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap.size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//��ÿ������м��㣬������������
			if (chess->getChessData(row, col)) continue;

			//�����˸������е�һ�࣬���ĸ�����-1��-1����0��-1����1��-1����1,0��
			for (int y = -1; y <= 0; y++) {        //Y�ķ�Χ��-1�� 0
				for (int x = -1; x <= 1; x++) {    //X�ķ�Χ�� -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //��y=0ʱ��������x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// �Ժ�������
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;//�˴��к���
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;//�˴��ǿ�λ
							break;
						}
						else {
							break;//���߽���
						}
					}

					// �����������
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

					if (personNum == 1) { //��2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {//��3
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;//��3
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;//��3
						}
					}
					else if (personNum == 3) {//��4
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;//��4
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 5000;//��4
						}
					}
					else if (personNum == 4) {//��5
						scoreMap[row][col] = 20000;
					}

					// �԰������֣�ֻ���ۼӵķ�ֵ����岻ͬ��
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

					if (aiNum == 0) {//��ͨ����
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {//��2
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {//����
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;//��3
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;//��3
						}
					}
					else if (aiNum == 3) {//��4
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;//��4
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;//��4
						}
					}
					else if (aiNum >= 4) {//��5
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	//��������
	calculateScore();

	int maxScore = 0;
	vector<ChessPos> maxPoints;
	int k = 0;

	//����scoreMap
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//��λ���ǿյĲŴ�
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {//����ж��������������
					maxPoints.push_back(ChessPos(row, col));
				 }
			}
		}
	}

	//������˶���㣬�����һ��
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
