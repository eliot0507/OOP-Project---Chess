#pragma once
#include "Board.h"
#include "Viewer.h"
#include "Player.h"
class GameManager
{
	private:
		int mode;
		int turn;
		Player* players[2];   
		Board board;
		Viewer viewer;
	public:
		GameManager();
		~GameManager();
		void view_menu();
		void view_ending();
		void setMode();
		void setMode_replay();
		int getMode();
		void play();
		void ask_again();
		void playBack();
		void reset();
};