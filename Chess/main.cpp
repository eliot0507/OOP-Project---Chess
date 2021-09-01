#include <iostream>
#include "Gamemanager.h"
int main()
{
    GameManager game;
    game.view_menu();
    game.setMode();
    while (game.getMode() != 0)
    {
        game.play();
        game.ask_again();
        game.setMode_replay();
        if (game.getMode() != 3)//not replay
            game.reset();
        else//replay
        {
            game.playBack();
            game.setMode();
            game.reset();
        }
            
    }
    game.view_ending();
    return 0;
}
