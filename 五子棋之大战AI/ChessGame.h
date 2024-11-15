#pragma once


class ChessGame
{
public:
	ChessGame(Man*, AI*, Chess*);
	void play();

private:
	Man* man;
	AI* ai;
	Chess* chess;
};
