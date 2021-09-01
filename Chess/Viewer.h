#pragma once
#include "Board.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
class Viewer
{
	public:
		void view_menu();
		void view_board(Board& board, bool chosen_1 = false, vector<int>pos1 = { 0,0 }, bool chosen_2 = false, vector<int>pos2 = { 0,0 });
		void view_board(BoardVector bv, bool left_right = false);
		string choose_1(Board& board,bool invalid = false);
		string choose_2(Board& board,string last, bool invalid = false);
		void playBack(Board& board);
		void view_ending();
};