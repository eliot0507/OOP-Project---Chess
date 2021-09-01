#pragma once
#include <vector>
using namespace std;
class Piece {
	private:
	char type;
	char team;
	unsigned int mov_count;
	public:
		Piece();
		Piece(char tm, char tp);
		Piece(const Piece& rhs);
		const char getType() const;
		void setType(char t);
		const char getTeam() const;
		void plusCount();
		const unsigned int count() const;
		Piece& operator=(const Piece& rhs);
		void clear();
};