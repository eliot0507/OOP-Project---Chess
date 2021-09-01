#pragma once
#include "Board.h"
#include "Viewer.h"
class Player
{
	protected:
		char team;
	public:
		Player();
		Player(char tm);
		const char getTeam() const;
		virtual void OnMove(Board& board, Viewer viewer) = 0;
		virtual void OnPromote(Board& board, Viewer viewer) = 0;
};
class HumanPlayer : public Player
{
	public:
		HumanPlayer();
		HumanPlayer(char tm);
		void OnMove(Board& board, Viewer viewer);
		void OnPromote(Board& board, Viewer viewer);
};
class AIPlayer :public Player
{
	public:
		AIPlayer();
		AIPlayer(char tm);
		void OnMove(Board& board, Viewer viewer);
		void OnPromote(Board& board, Viewer viewer);
};