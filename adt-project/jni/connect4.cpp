#include <iostream>
#include <string>
#include "C4Game.h"
#include "C4Board.h"
#include "C4Player.h"
#include "C4HumanPlayer.h"
#include "C4AIPlayer.h"
using namespace std;

int main() {
    C4Game c4_game;
    C4Player *p1 = new C4AIPlayer('X');
    C4Player *p2 = new C4AIPlayer('0');

    c4_game.init(p1, p2);
    int move;
    
    string header = " 0  1  2  3  4  5  6 ";
    cout << header << endl;
    cout << c4_game.toString() << endl;

    while (1) {
        if (c4_game.isCurrentAI()){
            c4_game.step();
        } else {
            cout << "Make Move: ";
            cin >> move;
            cout << endl;
            c4_game.step(move);
        }
        cout << header << endl;
        cout << c4_game.toString() << endl;
        if (c4_game.getGameState() != 0) {
            if (c4_game.getGameState() > 0) {
                cout << "Game End! Congrats Player " << c4_game.getGameState() << endl;
            } else {
                cout << "Game End! Draw" << endl;
            }
            break;
        }
    }

    delete p1;
    delete p2;
    return 0;
}
