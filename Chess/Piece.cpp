#include "Piece.h"
Piece::Piece() :type('0'), team('0'), mov_count(0)
{
}
Piece::Piece(char tm, char tp) :type(tp), team(tm), mov_count(0)
{
}
Piece::Piece(const Piece& rhs)
{
	type = rhs.type;
	team = rhs.team;
	mov_count = rhs.mov_count;
}
Piece& Piece::operator=(const Piece& rhs)
{
	type = rhs.type;
	team = rhs.team;
	mov_count = rhs.mov_count;
	return *this;
}
const char Piece::getType() const
{
	return type;
}
void Piece::setType(char t)
{
	type = t;
}
const char Piece::getTeam() const
{
	return team;
}
void Piece::plusCount()
{
	mov_count++;
}
const unsigned int Piece::count() const
{
	return mov_count;
}

void Piece::clear()
{
	type = '0';
	team = '0';
	mov_count = 0;
}