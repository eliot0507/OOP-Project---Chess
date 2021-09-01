#include "Gamemanager.h"
#include <iostream>
using namespace std;
#define MAXMODE 2
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
GameManager::GameManager()
{
    mode = 0;
    turn = 0;
    players[0] = NULL;
    players[1] = NULL;
}
GameManager::~GameManager()
{
    if (players[0] != NULL)
    {
        delete players[0];
        delete players[1];
        players[0] = players[1] = NULL;
    }
}
void GameManager::view_menu()
{
    viewer.view_menu();
}
void GameManager::view_ending()
{
    viewer.view_ending();
}
void GameManager::setMode()
{
    //prevention for memory leak
    if (players[0] != NULL)
    {
        delete players[0];
        delete players[1];
        players[0] = players[1] = NULL;
    }
    //the real setMode
    bool flag;
    cout << "Please enter gamemode:\n0 -> exit\n1 -> 2P\n2 -> CPU\n";
    do
    {
        flag = false;
        clearInput();
        mode = _getch()-'0';
        switch (mode)
        {
        case 0:
            break;
        case 1:
            players[0] = new HumanPlayer('w');
            players[1] = new HumanPlayer('b');
            break;
        case 2:
            players[0] = new HumanPlayer('w');
            players[1] = new AIPlayer('b');
            break;
        default:
            cout << "\nInvalid, please try again: ";
            flag = true;
            break;
        }
    } while (flag);
}
void GameManager::setMode_replay()
{
    //prevention for memory leak
    if (players[0] != NULL)
    {
        delete players[0];
        delete players[1];
        players[0] = players[1] = NULL;
    }
    //the real setMode
    bool flag;
    cout << "Please enter gamemode:\n0 -> exit\n1 -> 2P\n2 -> CPU\n3 -> Playback";
    do
    {
        flag = false;
        clearInput();
        mode = _getch() - '0';
        switch (mode)
        {
            case 0:
                break;
            case 1:
                players[0] = new HumanPlayer('w');
                players[1] = new HumanPlayer('b');
                break;
            case 2:
                players[0] = new HumanPlayer('w');
                players[1] = new AIPlayer('b');
                break;
            case 3:
                break;
            default:
                cout << "\nInvalid, please try again: ";
                flag = true;
                break;
        }
    } while (flag);
}
int GameManager::getMode()
{
    return mode;
}
void GameManager::play()
{
    viewer.view_board(board);
    turn = 0;
    while (!board.isEnd())
    {
        players[turn]->OnMove(board, viewer);
        if(!board.isEnd())//doesn't give up
            players[turn]->OnPromote(board, viewer);
        turn = (turn + 1) % 2;
        if(!board.isEnd())//doesn't give up
            board.check();
    }
}
void GameManager::ask_again()
{
    //view wanna_try_again ?
    switch (board.getResult())
    {
        case 'w':
            cout << "White wins!\n";
            break;
        case 'b':
            cout << "Black wins!\n";
            break;
        case 'd':
            cout << "Draw!\n";
            break;
    }
    cout << "Wanna try again?\n";

}
void GameManager::playBack()
{
    viewer.playBack(board);
}
void GameManager::reset()
{
    //no need to reset mode and players
    turn = 0;
    board.B_Reset();
}