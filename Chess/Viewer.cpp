#include "Viewer.h"
#include <iostream>
#include <stdlib.h>
#include <map>
#define ESC "\033["
#define DARK_BKG "100" //dark gray
#define WHITE_TXT "37" //white
#define LIGHT_BKG "43" //yellow
#define BLACK_TXT "30" //black
#define WHITE_BKG "107"//BKG white
#define BLACK_BKG "30" //BKG black
#define RESET "\033[m"
using namespace std;
namespace
{
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
string chess_P[8] = {"                ", "                ","        _       ","       (_)      ","       / \\      ","      (___)     ","                " ,"                " };
string chess_R[8] = { "                ", "     WWWWWW     ", "      |  |      " ,"      |__|      " ,"      /__\\      " ,"     (____)     " ,"                " ,"                "};
string chess_N[8] = { "                ","     __/'''\\    " ,"    ]___ 0 }    " ,"       /   }    " ,"      /____\\    " ,"     (______)   " ,"                ", "                " };
string chess_B[8] = { "                ","       _O_      " ,"     _(_+_)_    " ,"     \\_____/    " ,"      /___\\     " ,"     (_____)    ","                " , "                "};
string chess_Q[8] = { "                ", "                " ,"       **       " ,"    **\\  /**    " ,"     \\\\||//     " ,"     (____)     " ,"                " , "                "};
string chess_K[8] = { "                ","                " ,"      _.+._     " ,"    (^\\/^\\/^)   " ,"     \\@*@*@/    " ,"     {_____}    " ,"                ", "                " };
string blank[8] = {"                ","                ","                " ,"                " ,"                " ,"                " ,"                " ,"                " };
map<char, string* >chess_pic = { {'P',chess_P},{'R',chess_R},{'N',chess_N},{'B',chess_B},{'Q',chess_Q},{'K',chess_K},{'0',blank} };
string bkg_color[2] = { DARK_BKG, LIGHT_BKG };
map<char, string> txt_color = { {'0', WHITE_TXT}, {'w', WHITE_TXT}, {'b', BLACK_TXT} };
map<char, string> border_color = { {'0',WHITE_BKG} ,{'w',WHITE_BKG} ,{'b',BLACK_BKG} };
bool keyPressed(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

void setCursorPos(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Viewer::view_menu()
{
	system("CLS");
	//full screen
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	cout << "    _                                      _  " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "   (_)          _                         (_) " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "  (___)    ____| |__   ____  ____ ____   (___)" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "  _|_|_   / ___|  _ \\ /  _ \\/  __/  __|  _|_|_ " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " (_____) | (___| | | |   __/\\__  \\__  \\ (_____)" <<endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " /_____\\  \\____|_| |_|\\____|\\____/____/ /_____\\ " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << endl;
	cout << "*************************************************" << endl;
}
void Viewer::view_board(Board& board, bool chosen_1, vector<int>pos1, bool chosen_2, vector<int>pos2)
{
	//clear console
	system("cls");
	//print board
	int row, col, i, j;
	//int block_w = 12, block_l = 6;
	int block_w = 16, block_l = 8;
	int border_vertical_w = 2, border_horizontal_w = 1;
	//vertical border (showing 8 to 1)
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < block_l; j++)
		{
			setCursorPos(0, i * block_l + j);
			if (j == block_l / 2)
				cout << 8 - i;
			else
				cout << ' ';
		}
	}
	//horizontal border (showing a to h)
	string ch_hor = "abcdefgh";
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < block_w; j++)
		{
			setCursorPos(border_vertical_w + i * block_w + j, 8 * block_l);
			if (j == block_w / 2)
				cout << ch_hor[i];
			else
				cout << ' ';
		}
	}
	//print board
	for (col = 0; col < 8; col++)
	{
		for (row = 7; row >= 0; row--)
		{
			const Piece p = board[row][col];
			for (i = 0; i < block_l; i++)
			{
				setCursorPos(border_vertical_w + col * block_w, (7 - row) * block_l + i);

				//畫白框
				if(chosen_1 && row == pos1[0] && col == pos1[1])
				{
					if(i == 0 || i == 7) //上下
					{
						cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << blank[i] << RESET;
					}
					else
					{
						for (int k = 0 ; k < 2 ; k++) //左
						{
							cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
						for (int k = 2 ; k < 14 ; k++) 
						{
							cout << ESC << bkg_color[(row + col) % 2] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
						for (int k = 14 ; k < 16 ; k++) //右
						{
							cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
					}
				}
				else if (chosen_2 && row == pos2[0] && col == pos2[1]) 
				{
					if(i == 0 || i == 7) //上下
					{
						cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << blank[i] << RESET;
					}
					else
					{
						for (int k = 0 ; k < 2 ; k++) //左
						{
							cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
						for (int k = 2 ; k < 14 ; k++) 
						{
							cout << ESC << bkg_color[(row + col) % 2] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
						for (int k = 14 ; k < 16 ; k++) //右
						{
							cout << ESC << border_color[board.getTeam()] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i][k] << RESET;
						}
					}
				}
				else
				{
					cout << ESC << bkg_color[(row + col) % 2] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i] << RESET;
				}
			}
			if(!(chosen_1||chosen_2))
				this_thread::sleep_for(chrono::milliseconds(25));
		}
	}
	setCursorPos(0, 8 * block_l + border_horizontal_w);
}
string Viewer::choose_1(Board& board, bool invalid)
{
	clearInput();
	vector<int> pos = { 0, 0 };
	while (1)
	{
		if (keyPressed(VK_UP))
			pos[0] < 7 ? pos[0]++ : pos[0] = 7;
		if (keyPressed(VK_DOWN))
			pos[0] > 0 ? pos[0]-- : pos[0] = 0;
		if (keyPressed(VK_LEFT))
			pos[1] > 0 ? pos[1]-- : pos[1] = 0;
		if (keyPressed(VK_RIGHT))
			pos[1] < 7 ? pos[1]++ : pos[1] = 7;
		if (keyPressed(VK_ESCAPE))
			return "giveup";
		if (keyPressed(VK_RETURN))
			break;

		this_thread::sleep_for(chrono::milliseconds(50));

		LockWindowUpdate(GetConsoleWindow());
		view_board(board, true, pos);
		cout << "Use arrow keys to choose. If you want to surrender, press Esc.\n";
		if (board.cant_be_checked())//被將軍
			cout << (board.getTeam() == 'w' ? "White team" : "Black team") << "is checked!\n";
		if(invalid)
			cout << "Invalid, please try again.\n";
		LockWindowUpdate(NULL);
	}	
	string s_pos = "a1";
	s_pos[0] += pos[1];
	s_pos[1] += pos[0];
	this_thread::sleep_for(chrono::milliseconds(500));
	return s_pos;
}
string Viewer::choose_2(Board& board, string last, bool invalid)
{
	clearInput();
	vector<int> pos_last = { last[1] - '1',last[0] - 'a' };
	vector<int> pos = pos_last;
	while (1)
	{
		if (keyPressed(VK_UP))
			pos[0] < 7 ? pos[0]++ : pos[0] = 7;
		if (keyPressed(VK_DOWN))
			pos[0] > 0 ? pos[0]-- : pos[0] = 0;
		if (keyPressed(VK_LEFT))
			pos[1] > 0 ? pos[1]-- : pos[1] = 0;
		if (keyPressed(VK_RIGHT))
			pos[1] < 7 ? pos[1]++ : pos[1] = 7;
		if (keyPressed(VK_ESCAPE))
			return "giveup";
		if (keyPressed(VK_RETURN))
			break;

		this_thread::sleep_for(chrono::milliseconds(50));

		LockWindowUpdate(GetConsoleWindow());
		view_board(board, true, pos_last, true, pos);
		cout << "Use arrow keys to choose. If you want to surrender, press Esc.\n";
		if (board.cant_be_checked())//被將軍
			cout << (board.getTeam() == 'w' ? "White team" : "Black team") << "is checked!\n";
		if (invalid)
			cout << "Invalid, please try again.\n";
		LockWindowUpdate(NULL);
	}
	string s_pos = "a1";
	s_pos[0] += pos[1];
	s_pos[1] += pos[0];
	this_thread::sleep_for(chrono::milliseconds(500));
	return s_pos;
}
void Viewer::playBack(Board& board)
{
	int index = 0;
	view_board(board.getHistory(0), true);
	while (1)
	{
		if (keyPressed(VK_LEFT))
		{
			if (index == 0)
				index++;
			view_board(board.getHistory(--index), true);
		}
			
		if (keyPressed(VK_RIGHT))
		{
			if (index == board.historyLen() - 1)
				index--;
			view_board(board.getHistory(++index), true);
		}
		if (keyPressed(VK_ESCAPE))
			break;
		this_thread::sleep_for(chrono::milliseconds(50));
		//LockWindowUpdate(GetConsoleWindow());
		//LockWindowUpdate(NULL);
	}
}
void Viewer::view_board(BoardVector bv, bool left_right)
{
	//clear console
	system("cls");
	//print board
	int row, col, i, j;
	int block_w = 16, block_l = 8;
	int border_vertical_w = 2, border_horizontal_w = 1;
	//vertical border (showing 8 to 1)
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < block_l; j++)
		{
			setCursorPos(0, i * block_l + j);
			if (j == block_l / 2)
				cout << 8 - i;
			else
				cout << ' ';
		}
	}
	//horizontal border (showing a to h)
	string ch_hor = "abcdefgh";
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < block_w; j++)
		{
			setCursorPos(border_vertical_w + i * block_w + j, 8 * block_l);
			if (j == block_w / 2)
				cout << ch_hor[i];
			else
				cout << ' ';
		}
	}
	//print board
	for (col = 0; col < 8; col++)
	{
		for (row = 7; row >= 0; row--)
		{
			Piece p = bv[row][col];
			for (i = 0; i < block_l; i++)
			{
				setCursorPos(border_vertical_w + col * block_w, (7 - row) * block_l + i);
				cout << ESC << bkg_color[(row + col) % 2] << ";" << txt_color[p.getTeam()] << "m" << chess_pic[p.getType()][i] << RESET;
			}
		}
	}
	setCursorPos(0, 8 * block_l + border_horizontal_w);
	if (left_right)
	{
		cout << "Press right arrow to see the next move\n";
		cout << "Press left arrow to see the prewvious move\n";
	}
}
void Viewer::view_ending()
{
	system("CLS");
	cout << "  ____ " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " |  _ \\" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " | |_) |              __/'''\\" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " |   __/ _   _  ___  ]___ ^ }" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " |  _  \\| | | |/ _ \\    /   }" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " | |_)  | |_| |  __/   /____\\" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << " |_.__ / \\__, |\\___|  (______)" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "         __/  |" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "        |____/" << endl;
}
