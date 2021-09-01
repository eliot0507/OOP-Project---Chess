#include "Player.h"
#include <iostream>
#include <string>
#include <random>
using namespace std;
namespace {
	bool ifgiveup(string flag, char team, Board& board)
	{
		if (flag == "giveup")
		{
			board.give_up(team);
			return true;
		}
		else
			return false;
	}
	void clearInput()
	{
		int k;
		while (1) {
			if (_kbhit()) {
				k = _getch();
				if (0 == k || 0xE0 == k) k = k << 8 | _getch();
			}
			else break;
		}
	}
}
Player::Player()
{
	team = 'w';//default team: white
}
Player::Player(char tm)
{
	team = tm;
}
const char Player::getTeam() const
{
	return team;
}
HumanPlayer::HumanPlayer() :Player('w')//default team: white
{
}
HumanPlayer::HumanPlayer(char tm):Player(tm)
{
}
void HumanPlayer::OnMove(Board& board, Viewer viewer)
{
	/*string pos1, pos2;
	if (board.cant_be_checked())//³Q±N­x
		cout << (getTeam() == 'w' ? "White team" : "Black team") << "is checked!\n";
	cout << "Enter the start and end position.\n";
	cin >> pos1 >> pos2;
	while((!board.checkavailable(getTeam(), pos1, pos2)) || (!board.fake_move(pos1,pos2))){	//bool type
		cout << "Invalid, please try again.\n";
		cin >> pos1 >> pos2;
	}
	board.move(pos1, pos2);
	board.putHistory();
	viewer.view_board(board);//*/
	//move by arrow keys
	string pos1, pos2;
	pos1 = viewer.choose_1(board);
	if (ifgiveup(pos1, team, board))
		return;
	pos2 = viewer.choose_2(board, pos1);
	if (ifgiveup(pos2, team, board))
		return;
	//cout << pos1 << endl << pos2 << endl;
	while((!board.checkavailable(getTeam(), pos1, pos2)) || (!board.fake_move(pos1,pos2))){	//bool type
		pos1 = viewer.choose_1(board, true);
		if (ifgiveup(pos1, team, board))
			return;
		pos2 = viewer.choose_2(board, pos1, true);
		if (ifgiveup(pos1, team, board))
			return;
	}
	board.move(pos1, pos2);
	board.putHistory();
	//viewer.view_board(board);
	
}
void HumanPlayer::OnPromote(Board& board, Viewer viewer)
{
	//check promote or not
	//promotions will happen just after the player's move, so there's no need to check player's team.
	for (int j = 0; j < 8; j += 7)
	{
		char type;
		bool flag = true;
		for (int i = 0; i < 8; i++)
		{
			//if promote
			if (board[j][i].getType() == 'P')
			{
				cout << "You can promote your Pawn!\nPlease enter the type you want to promote.(q/r/b/n)";
				clearInput();
				do
				{
					flag = false;
					type = _getch();
					switch (type)
					{
					case 'q':
						board[j][i].setType('Q');
						break;
					case 'r':
						board[j][i].setType('R');
						break;
					case 'b':
						board[j][i].setType('B');
						break;
					case 'n':
						board[j][i].setType('N');
						break;
					default:
						cout << "\nInvalid, please try again.";
						flag = true;
						break;
					}
				} while (flag);
				board.putHistory();
			}
			if (!flag)
				break;
		}
		if (!flag)
			break;
	}
}
AIPlayer::AIPlayer() :Player('w')//default team: white
{
}
AIPlayer::AIPlayer(char tm) : Player(tm)
{
}
void AIPlayer::OnMove(Board& board, Viewer viewer)
{
	string pos1, pos2;
	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_int_distribution<int> dis(0, 7);
	pos1 = pos2 = "a1";
	for (char& i : pos1)
	{
		i += dis(gen);
	}
	for (char& i : pos2)
		i += dis(gen);
	while ((!board.checkavailable(getTeam(), pos1, pos2)) || (!board.fake_move(pos1, pos2))) {	//bool type
		pos1 = pos2 = "a1";
		for (char& i : pos1)
			i += dis(gen);
		for (char& i : pos2)
			i += dis(gen);
	}
	board.move(pos1, pos2);
	board.putHistory();
}
void AIPlayer::OnPromote(Board& board, Viewer viewer)
{
	for (int j = 0; j < 8; j += 7)
	{
		int type;
		bool flag = true;
		for (int i = 0; i < 8; i++)
		{
			//if promote
			if (board[j][i].getType() == 'P')
			{
				std::random_device rd;
				std::default_random_engine gen = std::default_random_engine(rd());
				std::uniform_int_distribution<int> dis(0, 3);
				do
				{
					flag = false;
					type = dis(gen);
					switch (type)
					{
						case 0:
							board[j][i].setType('Q');
							break;
						case 1:
							board[j][i].setType('R');
							break;
						case 2:
							board[j][i].setType('B');
							break;
						case 3:
							board[j][i].setType('N');
							break;
						default:
							flag = true;
							break;
					}
				} while (flag);
				board.putHistory();
			}
			if (!flag)
				break;
		}
		if (!flag)
			break;
	}
}