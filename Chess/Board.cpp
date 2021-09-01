#include "Board.h"
#include<string>
#include<cmath>
Board::Board() :turn('w')//initialization
{
	result = '0';
	end = false;
	//null pieces
	board_v = BoardVector(8, vector<Piece>(8, Piece()));
	//Pawns
	for (int j = 0; j < 8; j++)
		board_v[1][j] = Piece('w', 'P');
	for (int j = 0; j < 8; j++)
		board_v[6][j] = Piece('b', 'P');
	//Other pieces
	char team[2] = { 'w','b' };
	char type[8] = { 'R','N','B','Q','K','B','N','R' };
	for (int i = 0; i < 8; i += 7)
	{
		for (int j = 0; j < 8; j++)
		{
			board_v[i][j] = Piece(team[i % 2], type[j]);
		}
	}
	history.push_back(board_v);
}

void Board::B_Reset() {
	result = '0';
	end = false;
	turn = 'w';
	history.clear();
	board_v = BoardVector(8, vector<Piece>(8, Piece()));
	//Pawns
	for (int j = 0; j < 8; j++)
		board_v[1][j] = Piece('w', 'P');
	for (int j = 0; j < 8; j++)
		board_v[6][j] = Piece('b', 'P');
	//Other pieces
	char team[2] = { 'w','b' };
	char type[8] = { 'R','N','B','Q','K','B','N','R' };
	for (int i = 0; i < 8; i += 7)
	{
		for (int j = 0; j < 8; j++)
		{
			board_v[i][j] = Piece(team[i % 2], type[j]);
		}
	}
	history.push_back(board_v);
}

bool Board::isEnd()
{
	return end;
}

void Board::setTeam(char a) {
	turn = a;
	return;
}

char Board::getTeam() {
	return turn;
}

void Board::check() {
	string pos1 = "a1";
	string pos2 = "a1";
	if (turn == 'w')
		turn = 'b';
	else if (turn == 'b')
		turn = 'w';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board_v[j][i].getType() != '0' && board_v[j][i].getTeam() == turn) {
				pos2 = "a1";
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (pos1 != pos2) {
							//cout << "position 1 " << pos1 << " position 2 " << pos2 << endl;
							//cout << "par 1 " << i << " par 2 " << j << endl;
							//cout << "now grid: type " << board_v[i][j].getType() << " team " << board_v[i][j].getTeam() << endl;
							if (checkavailable(turn, pos1, pos2) && fake_move(pos1, pos2)) {
								//cout << "position 1 " << pos1 << " position 2 " << pos2 << endl;
								//cout << "par 1 " << i << " par 2 " << j << endl;
								//cout << "now grid: type " << board_v[i][j].getType() << " team " << board_v[i][j].getTeam() << endl;
								//cout << "available move" << endl;
								//cout << "available" << endl;
								result = '0';
								end = false;
								return;
							}
							//return;
						}
						pos2[1]++;
					}
					pos2[0]++;
					pos2[1] = '1';
				}
			}
			pos1[1]++;
		}
		pos1[0]++;
		pos1[1] = '1';
	}

	if (!cant_be_checked()) {
		result = 'd';
		end = true;
	}
	else if (turn == 'b') {
		result = 'w';
		end = true;
	}
	else if (turn == 'w') {
		result = 'b';
		end = true;
	}
	return;
}

void Board::give_up(char t) {
	if (t == 'w') {
		end = true;
		result = 'b';
	}
	else if (t == 'b') {
		end = true;
		result = 'w';
	}
	return;
}

void Board::putHistory()
{
	history.push_back(board_v);
}
BoardVector Board::getHistory(int x)
{
	return history[x];
}
int Board::historyLen()
{
	return history.size();
}
bool Board::check_blocked(string start, string end) {
	if (start[0] == end[0]) {//vertical
		if (start[1] < end[1]) {
			for (char i = start[1] + 1; i < end[1]; i++) {
				if (board_v[i - '1'][start[0] - 'a'].getType() != '0')return false;
			}
			return true;
		}
		else {
			for (char i = end[1] + 1; i < start[1]; i++) {
				if (board_v[i - '1'][start[0] - 'a'].getType() != '0')return false;
			}
			return true;
		}
		return true;
	}
	else if (start[1] == end[1]) {//horizontal
		if (start[0] < end[0]) {
			for (char i = start[0] + 1; i < end[0]; i++) {
				if (board_v[start[1] - '1'][i - 'a'].getType() != '0')return false;
			}
			return true;
		}
		else {
			for (char i = end[0] + 1; i < start[0]; i++) {
				if (board_v[start[1] - '1'][i - 'a'].getType() != '0')return false;
			}
			return true;
		}
		return true;
	}
	else if (abs(start[0] - end[0]) == abs(start[1] - end[1])) {//diagonal
		char h, v;
		h = start[0];
		v = start[1];
		if (start[0] > end[0] && start[1] > end[1]) {		//left down
			for (int i = 0; i < abs(start[0] - end[0]) - 1; i++) {
				h--;
				v--;
				if (board_v[v - '1'][h - 'a'].getType() != '0')return false;
			}
		}
		else if (start[0] > end[0] && start[1] < end[1]) {	//left up
			for (int i = 0; i < abs(start[0] - end[0]) - 1; i++) {
				h--;
				v++;
				if (board_v[v - '1'][h - 'a'].getType() != '0')return false;
			}
		}
		else if (start[0] < end[0] && start[1] > end[1]) {	//right down
			for (int i = 0; i < abs(start[0] - end[0]) - 1; i++) {
				h++;
				v--;
				if (board_v[v - '1'][h - 'a'].getType() != '0')return false;
			}
		}
		else if (start[0] < end[0] && start[1] < end[1]) {	//right up
			for (int i = 0; i < abs(start[0] - end[0]) - 1; i++) {
				h++;
				v++;
				if (board_v[v - '1'][h - 'a'].getType() != '0')return false;
			}
		}
		return true;
	}
	else return false;
}

bool Board::cant_be_checked() {
	vector<int> king_pos(getKing_pos());	//king_pos[0] for horizontal king_pos[1] for vertical
	int p = 0;
	if (turn == 'w') p = 1;			//not sure
	else if (turn == 'b') p = -1;
	else return false;
	return(find(king_pos[0] - 1, king_pos[1] - 2, 'N') || find(king_pos[0] - 2, king_pos[1] - 1, 'N')
		|| find(king_pos[0] + 1, king_pos[1] - 2, 'N') || find(king_pos[0] + 2, king_pos[1] - 1, 'N')
		|| find(king_pos[0] + 1, king_pos[1] + 2, 'N') || find(king_pos[0] + 2, king_pos[1] + 1, 'N')
		|| find(king_pos[0] - 1, king_pos[1] + 2, 'N') || find(king_pos[0] - 2, king_pos[1] + 1, 'N')
		|| find(king_pos[0] - 1, king_pos[1] + p, 'P') || find(king_pos[0] + 1, king_pos[1] + p, 'P')
		|| find(king_pos[0] - 1, king_pos[1] - 1, 'K') || find(king_pos[0], king_pos[1] - 1, 'K')
		|| find(king_pos[0] + 1, king_pos[1] - 1, 'K') || find(king_pos[0] + 1, king_pos[1], 'K')
		|| find(king_pos[0] + 1, king_pos[1] + 1, 'K') || find(king_pos[0], king_pos[1] + 1, 'K')
		|| find(king_pos[0] - 1, king_pos[1] + 1, 'K') || find(king_pos[0] - 1, king_pos[1], 'K')
		|| loopfind(king_pos[0] - 1, king_pos[1] - 1, -1, -1, 'B') || loopfind(king_pos[0], king_pos[1] - 1, 0, -1, 'R')
		|| loopfind(king_pos[0] + 1, king_pos[1] - 1, 1, -1, 'B') || loopfind(king_pos[0] + 1, king_pos[1], 1, 0, 'R')
		|| loopfind(king_pos[0] + 1, king_pos[1] + 1, 1, 1, 'B') || loopfind(king_pos[0], king_pos[1] + 1, 0, 1, 'R')
		|| loopfind(king_pos[0] - 1, king_pos[1] + 1, -1, 1, 'B') || loopfind(king_pos[0] - 1, king_pos[1], -1, 0, 'R')
		);
}

bool Board::find(int a, int b, char t) {	//a for horizontal b for vertical
	if (a < 0 || a > 7 || b < 0 || b > 7) return false;
	if (board_v[b][a].getType() == t && board_v[b][a].getTeam() != turn) return true;
	return false;
}

bool Board::loopfind(int a, int b, int dx, int dy, char t) { //a for horizontal b for vertical
	if (a < 0 || a > 7 || b < 0 || b > 7) return false;
	if (board_v[b][a].getType() == '0') return loopfind(a + dx, b + dy, dx, dy, t);
	else if ((board_v[b][a].getType() == t || board_v[b][a].getType() == 'Q') && board_v[b][a].getTeam() != turn) return true;
	return false;
}

bool Board::check_castling(int type) {
	int hpos;				//horizontal place
	string hspos;
	string mpos;			//before place
	string h;
	if (turn == 'w') {
		hpos = 0;		//White y axis
		h = "1";
		mpos = "e1";
	}
	else if (turn == 'b') {
		hpos = 7;		//Black y axis
		h = "8";
		mpos = "e8";
	}
	if (type == 1) {	//long castling
		if (board_v[hpos][0].count() == 0 && board_v[hpos][4].count() == 0) {
			if (board_v[hpos][1].getType() == '0'
				&& board_v[hpos][2].getType() == '0'
				&& board_v[hpos][3].getType() == '0') {
				hspos = 'e' + h;
				hspos[0]--;
				if (cant_be_checked()) return false;
				if (fake_move(mpos, hspos)) {
					hspos[0]--;
					if (fake_move(mpos, hspos)) {
						mpos[0]--;
						hspos[0] -= 2;
						move(hspos, mpos);	//rook move
						return true;
					}
				}
			}
		}
	}
	else if (type == 0) {	//short castling
		if (board_v[hpos][7].count() == 0 && board_v[hpos][4].count() == 0) {
			if (board_v[hpos][5].getType() == '0'
				&& board_v[hpos][6].getType() == '0') {
				hspos = 'e' + h;
				hspos[0]++;
				if (cant_be_checked()) return false;
				if (fake_move(mpos, hspos)) {
					hspos[0]++;
					if (fake_move(mpos, hspos)) {
						mpos[0]++;
						hspos[0]++;
						move(hspos, mpos);	//rook move
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::player_didnt_passant(string pos1, string pos2){
	BoardVector temp;	//put last board_v in to temp;
	temp = history[history.size() - 3];		//get this->[b1] b2 now
	if(turn == 'w'){
		if(temp[pos2[1] - '1' - 1][pos2[0] - 'a'].getType() == '0'){
			return true;
		}
	}
	else if(turn == 'b'){
		if(temp[pos2[1] - '1' + 1][pos2[0] - 'a'].getType() == '0'){
			return true;
		}
	}
	return false;
}

bool Board::checkavailable(char team, string a, string b) {	//a=e2
	turn = team;
	if (team != board_v[a[1] - '1'][a[0] - 'a'].getTeam())return false;//can't move the other team's pieces
	if (a == b)return false;
	switch (board_v[a[1] - '1'][a[0] - 'a'].getType()) {
	case 'K':		//King
		if (abs(a[0] - b[0]) == 2) {	//castling
			if (board_v[a[1] - '1'][a[0] - 'a'].count() != 0) return false;
			if (a[0] > b[0]) {			//long castle
				if (check_castling(1)) return true;
			}
			else if (a[0] < b[0]) {		//short castle
				if (check_castling(0)) return true;
			}
			return false;
		}
		else {						//normal move
			if (abs(a[0] - b[0]) <= 1 && abs(a[1] - b[1]) <= 1) {	//movement <= 1
				if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
					return true;
				}
				else if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0' /*&& cant_be_checked()*/) {		//check that grid has sth
					if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()
						!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {	//not same team
						return true; // normal eat
					}
					return false;
				}
			}
			else {
				return false;
			}
		}
		return false;
	case 'Q':		//Queen
		//horizontal
		if ((a[1] == b[1] && abs(a[0] - b[0]) > 0)				//horizontal
			|| (a[0] == b[0] && abs(a[1] - b[1]) > 0)			//vertical
			|| (abs(a[0] - b[0]) == abs(a[1] - b[1]))) {			//diagonal											
			if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
				if (check_blocked(a, b)) {
					//cout << "queen go" << endl;
					return true;
				}
				return false;
			}
			else if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//check that grid has sth
				if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()
					!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {	//if not same team
					if (check_blocked(a, b)) {
						//cout << "queen eat" <<
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		return false;
		break;
	case 'B':		//Bishop	
		if (abs(a[0] - b[0]) == abs(a[1] - b[1])) {
			if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {	//move
				if (check_blocked(a, b)) {
					return true;
				}
				return false;
			}
			else if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0' /*&& cant_be_checked()*/) {		//check that grid has sth
				if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()
					!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {	//if not same team
					if (check_blocked(a, b)) {
						return true;
					}
					return false;
				}
				return false;
			}
			else return false;
		}
		return false;
		break;
	case 'N':		//Knight
		if ((abs(a[0] - b[0]) == 2 && abs(a[1] - b[1]) == 1)		//move horizontal two steps and vertical 1 steps
			|| (abs(a[0] - b[0]) == 1 && abs(a[1] - b[1]) == 2)) {	//move vertical two steps and horizontal 1 steps
			if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
				return true;	//knight don't have to check if it is blocked
			}
			else if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0' /*&& cant_be_checked()*/) {//check that grid has sth
				if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()
					!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {	//if not same team
					return true; // normal eat.
				}
				return false;
			}
		}
		return false;
		break;
	case 'R':		//Rook
		//castling working on it
		if ((abs(a[1] - b[1]) == 0 && abs(a[0] - b[0]) > 0)				//	vertical
			|| (abs(a[0] - b[0]) == 0 && abs(a[1] - b[1]) > 0)) {		//horizontal
			if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
				if (check_blocked(a, b)) {
					return true;
				}
			}
			else if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//check that grid has sth
				if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()
					!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {	//if not same team
					if (check_blocked(a, b)) {
						return true;
					}
				}
			}
		}
		return false;
		break;
	case 'P':
		switch (turn) {
		case 'w':		//white team
			if (board_v[a[1] - '1'][a[0] - 'a'].count() == 0) {			//pawn didn't move
				if (a[0] == b[0]) {
					if (a[1] - b[1] == -1) {			//normal front move white team
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
							return true;	//normal first time moved
						}
						return false;
					}
					else if (a[1] - b[1] == -2) {
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0'
							&& board_v[b[1] - '1' - 1][b[0] - 'a'].getType() == '0') {
							return true;	//normal first time moved two grid
						}
						return false;
					}
					return false;
				}
				else if (abs(a[0] - b[0]) == 1 && a[1] - b[1] == -1) {			//normal eat time
					if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//grid has sth
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//same team
							!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {
							return true;
						}
						return false;			//normal eaten
					}
					return false;										//nothing on the grid
				}
				return false;											//input something wrong
			}
			else if (board_v[a[1] - '1'][a[0] - 'a'].count() > 0) {		//pawn moved
				if (a[0] == b[0]) {
					if (a[1] - b[1] == -1) {			//normal front move
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {	//grid has nothing
							return true;	//normal moved
						}
						return false;
					}
					return false;
				}
				else if (abs(a[0] - b[0]) == 1 && a[1] - b[1] == -1) {	//eat function
					if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//grid has sth
						//normal eat
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//not same team 
							!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {
							//cout << "Normal eat" << endl;
							return true;
						}
						return false;		//didn't eat same team
					}
					//passant
					else if (board_v[(b[1] - '1') - 1][b[0] - 'a'].count() == 1		//check if it is passent
						&& board_v[(b[1] - '1') - 1][b[0] - 'a'].getType() == 'P') {
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//not same team , eat.
							!= board_v[(b[1] - '1') - 1][b[0] - 'a'].getTeam()) {
							if (player_didnt_passant(a, b)) {
								board_v[(b[1] - '1') - 1][b[0] - 'a'].clear();
								return true;
							}
							return false;
						}
						//set board_v[b[0] - 'a'][(b[1] - '1') - 1] = '0';
						return false;		//passent didn't eaten same team
					}
					return false;
				}
				return false;
			}
			return false;
			break;
		case 'b':	//black team
			if (board_v[a[1] - '1'][a[0] - 'a'].count() == 0) {			//pawn didn't move
				if (a[0] == b[0]) {
					if (a[1] - b[1] == 1) {
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {
							return true;	//normal moved
						}
						return false;
					}
					else if (a[1] - b[1] == 2) {
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0'
							&& board_v[b[1] - '1' + 1][b[0] - 'a'].getType() == '0') {
							return true;	//normal moved
						}
						return false;
					}
					return false;
				}
				else if (abs(a[0] - b[0]) == 1 && a[1] - b[1] == 1) {			//eat time
					if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//grid has sth
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//not same team
							!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {
							return true;
						}
						return false;	//normal not eaten
					}
					return false;										//nothing on the grid
				}
				return false;											//input something wrong
			}
			else if (board_v[a[1] - '1'][a[0] - 'a'].count() > 0) {		//pawn moved
				if (a[0] == b[0]) {
					if (a[1] - b[1] == 1) {
						if (board_v[b[1] - '1'][b[0] - 'a'].getType() == '0') {	//grid has nothing
							return true;	//normal moved
						}
						return false;
					}
					return false;
				}
				else if (abs(a[0] - b[0]) == 1 && a[1] - b[1] == 1) {
					//normal eat
					if (board_v[b[1] - '1'][b[0] - 'a'].getType() != '0') {		//grid has sth
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//not same team
							!= board_v[b[1] - '1'][b[0] - 'a'].getTeam()) {
							return true;		//normal eaten
						}
						return false;	//same team
					}
					else if (board_v[(b[1] - '1') + 1][b[0] - 'a'].count() == 1		//check if it is passent
						&& board_v[(b[1] - '1') + 1][b[0] - 'a'].getType() == 'P') {
						if (board_v[a[1] - '1'][a[0] - 'a'].getTeam()			//same team eaten
							!= board_v[(b[1] - '1') + 1][b[0] - 'a'].getTeam()) {
							if (player_didnt_passant(a, b)) {
								board_v[(b[1] - '1') + 1][b[0] - 'a'].clear();
								return true;
							}
							return false;
						}
						return false;	//passent didn't eaten same team
					}
					return false;
				}
				return false;
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	default:
		return false;
		break;
	}
}


vector<Piece>& Board::operator[](int a)
{
	return board_v[a];
}
void Board::move(string a, string b)
{
	int pos1[2] = { a[0] - 'a',a[1] - '1' }, pos2[2] = { b[0] - 'a',b[1] - '1' };
	board_v[pos2[1]][pos2[0]] = board_v[pos1[1]][pos1[0]];
	board_v[pos2[1]][pos2[0]].plusCount();
	board_v[pos1[1]][pos1[0]].clear();
}

bool Board::fake_move(string a, string b) {
	int pos1[2] = { a[0] - 'a',a[1] - '1' }, pos2[2] = { b[0] - 'a',b[1] - '1' };
	Piece temp1 = board_v[pos1[1]][pos1[0]];
	Piece temp2 = board_v[pos2[1]][pos2[0]];
	board_v[pos2[1]][pos2[0]] = board_v[pos1[1]][pos1[0]];
	board_v[pos1[1]][pos1[0]].clear();
	if (cant_be_checked()) {
		board_v[pos1[1]][pos1[0]] = temp1;
		board_v[pos2[1]][pos2[0]] = temp2;
		return false;
	}
	else {
		board_v[pos1[1]][pos1[0]] = temp1;
		board_v[pos2[1]][pos2[0]] = temp2;
		return true;
	}
}

const char Board::getResult() const
{
	return result;
}

vector<int> Board::getKing_pos() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board_v[j][i].getType() == 'K') {
				if (board_v[j][i].getTeam() == turn) {
					return vector<int> { i, j };	//par 1 for horizontal par 2 for vertical
				}
			}
		}
	}
}


/* if you want better speed but more complex
switch (board_v[i][j].type) {
				case 'P':
					switch (turn) {
					case 'w':

						break;
					case 'b':

						break;
					}
					break;
				case 'R':
					if (loop_check(pos1, 0, 1) || loop_check(pos1, 1, 0)
						|| loop_check(pos1, -1, 0) || loop_check(pos1, 0, -1))return;
					break;
				case 'N':
					pos2 = pos1;
					pos2[0] -= 2;
					pos2[1] += 1;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] -= 1;
					pos2[1] += 2;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] += 1;
					pos2[1] += 2;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] += 2;
					pos2[1] += 1;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] += 2;
					pos2[1] -= 1;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] += 1;
					pos2[1] -= 2;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] -= 1;
					pos2[1] -= 2;
					if (single_check(pos1, pos2))return;
					pos2 = pos1;
					pos2[0] -= 2;
					pos2[1] -= 1;
					if (single_check(pos1, pos2))return;
					break;
				case 'B':
					if (loop_check(pos1, 1, 1) || loop_check(pos1, -1, 1)
						|| loop_check(pos1, -1, -1) || loop_check(pos1, 1, 1))return;
					break;
				case 'Q':

					break;
				case 'K':

					break;
				}*/