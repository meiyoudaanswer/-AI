#include "Man.h"
#include "AI.h"
#include "Chess.h"
#include "ChessGame.h"
#include <iostream>

int main(void) {
	Chess chess(13, 44, 43, 67.4);
	Man man;
	AI ai;
	printf("�������Ծ�֮��սAI�����������������Ļ��\n");
	printf("���Ǻڷ�\n׼��������\nף��ʤ��~");
	Sleep(2500);
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}