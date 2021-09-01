#pragma once
#include "Piece.h"
#include <vector>
#include<string>
#include<iostream>
using namespace std;
typedef vector<vector<Piece>> BoardVector;
class Board
{
private:
	BoardVector board_v;
	vector<BoardVector> history;
	bool end;
	char result;
	char turn;
public:
	Board();
	void check();
	void give_up(char);
	bool single_check(string, string);
	bool loop_check(string, int, int);
	void B_Reset();
	bool isEnd();
	void setTeam(char);
	char getTeam();
	void putHistory();
	BoardVector getHistory(int x);
	int historyLen();
	bool check_blocked(string, string);
	bool check_castling(int type); //1 for long 0 for short
	bool player_didnt_passant(string, string);
	bool cant_be_checked();			//true is checked false is not checked
	vector<int> getKing_pos();
	bool checkavailable(char team, string a, string b);	//true is available false is can't
	vector<Piece>& operator[](int a);
	void move(string a, string b);
	bool fake_move(string a, string b);	//true is available (after move is not checked)
	const char getResult() const;
	bool find(int, int, char);
	bool loopfind(int, int, int, int, char);
};