#pragma once
#include <graphics.h>
#include <vector>
using namespace std;


//��������ö�����͵����������ڴ���������ɫ
typedef enum {
	CHESS_BLACK = 1,//�ڷ�
	CHESS_WHITE = -1//�׷�
}chess_kind_t;

struct ChessPos {
	int row;
	int col;
	// ���캯��
	ChessPos(int r = 0, int c = 0);
};

class Chess
{
public:
	//���캯��
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//�������̵�ͼƬ��Դ����ʼ�������������
	void init();

	//�жϵ���Ƿ���Ч������Ч�����걣����pos
	bool clickBoard(int x, int y, ChessPos* pos);

	//�����̵�ָ��λ����ָ����ɫ������
	void chessDown(ChessPos* pos, chess_kind_t kind);

	//��ȡָ��λ������������ڡ��ס���
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//��ȡ���̴�С
	int getGradeSize();

	//�ж�����Ƿ����
	bool checkOver();

	//�ж����ʤ��
	bool checkWin();

	//��������ͼƬ��ͼ����Ⱦ�ӿ�
	void putimagePNG(int x, int y, IMAGE* picture);

private:
	//���̳ߴ�
	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	//���浱ǰ���������ӵ��������Ϊ0����Ϊ1����Ϊ0
	vector<vector<int>> chessMap;

	//��ʾ���巽����Ϊtrue����Ϊfalse
	bool playerFlag;

	//�������λ��
	ChessPos lastPos;

	//������������
	void updateGameMap(ChessPos* pos);
};

