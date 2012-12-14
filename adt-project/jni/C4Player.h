#ifndef _C4PLAYER_H
#define _C4PLAYER_H

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class C4Board {
protected:
    const static int rows_n = 6;
    const static int cols_n = 7;
    vector< vector<char> > board;
    char placeholder;
public:

    /**
     * Constructor of C4Board. Sets up board and initializes it to 0.
     * An empty board is 6 x 7 with '*' placeholder characters.
     *
     */
    C4Board(char placeholder='.') {
        this->placeholder = placeholder;
        board.resize(rows_n, vector<char>( cols_n, placeholder));
    };

    /**
     * Getter for placeholder.
     */
    char getPlaceholder() { return placeholder; };

    /**
     * Reset all values in the board to the placeholder placeholder
     */
    void reset() { board.assign(rows_n, vector<char>( cols_n, placeholder)); };

    /**
     * Makes a move, taking a column to make the move in and a marker to place
     *
     * @param col is the column for the move to be made in
     * @param marker is the character marker to be placed in the column
     * @return returns an integer representing the games current state.
     *         -1 for failed move, 0 for move success (No reall state change),
     *         1 for , 2 for draw condition met.
     */
    int makeMove(int col, char marker) {
        static int row;
        if (isColumnAvailable(col)) {
            for (int row_n = 0; row_n < rows_n; row_n++) {
                if (board[row_n][col] == placeholder) {
                    row = row_n;
                    board[row_n][col] = marker;
                    break;
                }
            }

            // Return 0 if just another move and 1 if winning move was played.
            if (checkWinningCondition(col, row, marker)) {
                return 1; // Won
            } else if (checkDrawCondition()) {
                return 2; // Draw
            } else {
                return 0; // Nothing special
            }
        } else {
            return -1; // Move was not successful. Handle appropriately.
        }
    };

    int checkDrawCondition() {
        int sum = 0;
        // Sum accross all cols if placeholder add a 0, otherwise add a 1.
        for (int i = 0; i < cols_n; i++) {
            sum += (board[rows_n-1][i] != placeholder)?1:0;
        }
        // If sum is 7 then all columns are full and we are in a draw state.
        return (sum == 7)?1:0;
    }
    /**
     * Checks for winning conditions, by going through columns,
     * rows and diagonals which are connected to the previous move point
     *
     * @param col is an integer which indicates the column of the last move
     * @param row is an integer which indicates the row of the last move
     * @param marker is a char which indicates which character we are matching
     * @return 0 if no win. 1 if win
     */
    int checkWinningCondition(int col, int row, char marker) {
        int winning_ctr = 0;

        // Search columns
        for (int c = col-1; c >= (col-3); c--) {
            if (c < 0) {
                break;
            } else if (board[row][c] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        for (int c = col+1; c <= (col+3); c++) {
            if (c >= cols_n) {
                break;
            } else if (board[row][c] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        if (winning_ctr >= 3) {
            return 1;
        } else {
            winning_ctr = 0;
        }

        // Search Rows
        for (int r = row-1; r >= (row-3); r--) {
            if (r < 0) {
                break;
            } else if (board[r][col] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        for (int r = row+1; r <= (row+3); r++) {
            if (r >= rows_n) {
                break;
            } else if (board[r][col] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        if (winning_ctr >= 3) {
            return 1;
        } else {
            winning_ctr = 0;
        }

        // Search diagonals
        for (int i = 1; i <= 3; i++) {
            if ((row+i >= rows_n) || (col+i >= cols_n)) {
                break;
            } else if(board[row+i][col+i] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        for (int i = 1; i <= 3; i++) {
            if ((row-i < 0) || (col-i < 0)) {
                break;
            } else if(board[row-i][col-i] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        if (winning_ctr >= 3) {
            return 1;
        } else {
            winning_ctr = 0;
        }

        // Search anti-diagonals
        for (int i = 1; i <= 3; i++) {
            if ((row+i >= rows_n) || (col-i < 0)) {
                break;
            } else if(board[row+i][col-i] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        for (int i = 1; i <= 3; i++) {
            if ((row-i < 0) || (col+i >= cols_n)) {
                break;
            } else if(board[row-i][col+i] == marker) {
                winning_ctr++;
            } else {
                break;
            }
        }

        if (winning_ctr >= 3) {
            return 1;
        } else {
            return 0;
        }
    };

    /**
     *  Looks for placeholder placeholder in top row of column to see if it has room for
     *  a move.
     *
     * @param  col is the column that we are testing availability for
     * @return A boolean with`true' if Column is available and `false' if column
     *         is full.
     */
    bool isColumnAvailable(int col) {
        if (board[rows_n-1][col] == placeholder) {
            return true;
        } else {
            return false;
        }
    };

    /**
     * Convert board into a string t be printed
     *
     * @param returns string representing board
     */
    string toString() {
        string res = "";
        for (int i = rows_n-1; i >= 0; i--) {
            for (int j = 0; j < cols_n; j++) {
                res.push_back(' ');
                res.push_back(board[i][j]);
                res.push_back(' ');
            }
            res.push_back('\n');
        }

        return res;
    };

    /**
     * Prints out the board to std out using cout
     */
    void debug_PrintBoard() {
        cout << this->toString();
    };
};


class C4Player {
protected:
    char marker; // The marker that indicats this player to the outside world
    bool ai;
    int last_move;
public:
    /**
     * Constructor function. sets marker
     *
     * @param marker a character which represents this player on the board
     */
    C4Player(char marker, bool ai) {
        this->marker = marker;
        this->ai = ai;
    };

    /**
     * Returns bool ai.
     */
    bool isAI() { return this->ai; }

    /**
     *  Getter for marker character
     *
     * @return returns marker character
     */
    char getMarker() { return marker; };

    /**
     * VIRTUAL: Makes a move on the C4Board according to some logic implemented
     * in child functions. This function must be implemented.
     *
     * @param board is the board
     * @return -1 for bad move, 0 for move complete, 1 for winning move, 2 for draw.
     */
    virtual int makeMove(C4Board* board) = 0; // Virtual Function

    /**
     * VIRTUAL: Makes a move on the C4Board according to some logic implemented
     * in child functions. This function must be implemented. This one passes a
     * move from elsewhere (example a callback from the UI).
     *
     * @param board is the board
     * @param move is an integer representing which column to move into.
     * @return -1 for bad move, 0 for move complete, 1 for winning move, 2 for draw.
     */
    virtual int makeMove(C4Board* board, int move) = 0;

    int lastMove() { return last_move; }
    /**
     * Creates an identifier string for this class.
     *
     * @return string of class name and marker
     */
    virtual string toString() {
        string res = "";
        res += "C4Player: " + marker;
        return res;
    }
};

class C4HumanPlayer : public C4Player {
public:
    C4HumanPlayer(char marker) : C4Player(marker, false) {};

    /**
     * Implements makeMove for a human player
     *
     * @param board is the board
     * @return -1 for bad move, 0 for move complete, 1 for winning move, 2 for draw.
     */
    virtual int makeMove(C4Board *board, int move) {
        last_move = move;
        return board->makeMove(move, marker);
    };

    virtual int makeMove(C4Board *board) {
        return -1;
    };

    /**
     * Creates an identifier string for this class.
     *
     * @return string of class name and marker
     */
    virtual string toString() {
        string res = "";
        res += "C4HumanPlayer: " + marker;
        return res;
    };
};



class C4AIPlayer : public C4Player {
public:
    C4AIPlayer(char marker) : C4Player (marker, true) {
        std::srand( std::time(NULL) );
    };

    /**
     * Implements makeMove for a human player
     *
     * @param board is the board
     * @return -1 for bad move, 0 for move complete, 1 for winning move, 2 for draw.
     */
    virtual int makeMove(C4Board *board) {
        int ret = -1;
        int move;
        while (ret < 0) {
            move = rand()%7; // Random integer between 0 and 7
            ret = board->makeMove(move, marker);
        }

        last_move = move;
//        move = last_move;
        return ret;
    }; // Simple Random AI

    /**
     * Implements make move where move is gotten from elsewhere...
     *
     * @return -1 because AIs don't take orders from others
     */
    virtual int makeMove(C4Board *board, int move) { return makeMove(board); };

    /**
     * Creates an identifier string for this class.
     *
     * @return string of class name and marker
     */
    virtual string toString() {
        string res = "";
        res += "C4AIPlayer: " + marker;
        return res;
    };
};

class C4Game {
protected:
    C4Board board; // The C4 board. Makes moves and gets passed to players
    int turn; // Whose turn is it (0 for player 1, 1 for player 2)
    int game_state; // -1 for draw, 0 for no call, 1 for game won (P1), 2 for game won (P2)
    C4Player *players[2]; // Array of two players... (possibly make an STL vector?)
public:
    /**
     * Initialize game.
     */
    C4Game(char placeholder='.') {
        board = C4Board(placeholder);
        reset();
    };

    /**
     *  resets game state and starts game over.
     */
    void reset() {
        board.reset();
        turn = 0;
        game_state = 0;
    };

    /**
     * @return int of player turn. 1 is player 1, 2 is player 2.
     */
    int getCurrentPlayer() { return turn + 1; }

    /**
     * Return game state.
     *
     * Game State | Value
     * -----------+-------
     * Draw       | -1
     * Winning P1 |  1
     * Winning P2 |  2
     * Normal     |  0
     *
     * @return int of game state.
     */
    int getGameState() { return game_state; }

    /** void init()
     *  Initializes a game (also restarts game) and sets up the two players.
     *
     * @params player1 is a reference to a C4Player object which will go into
     *                 this->players[0].
     *
     * @params player2 is a reference to a C4Player object which will go into
     *                 this->players[1].
     */
    void init(C4Player *player1, C4Player *player2){
        players[0] = player1;
        players[1] = player2;

        // Reset board
        reset();
    };

    bool isCurrentAI() { return players[turn]->isAI(); }

    /** void step()
     *  steps the game forward one move and uses checkCondition to look for
     *  any winning conditions that have occured (or tie).
     *
     *  Utilzes C4Player's to act on the C4Board
     */
    int step(int move) {
        int stat;
        // Handle players appropriatly. If it is an AI type player then
        // you let it make a move and then pass the move along. If the
        // player is human (not an AI), then you pass the move to the
        // player and let it act on the board.
        if (players[turn]->isAI()) {
            stat = players[turn]->makeMove(&board);
            move = players[turn]->lastMove();
        } else {
            stat = players[turn]->makeMove(&board, move);
        }

        /* Evaluate the status of the game!
         *
         * Game State | Value
         * -----------+-------
         * Draw       | -1
         * Winning P1 |  1
         * Winning P2 |  2
         * Normal     |  0
         */
        if (stat == 2) {
            game_state = -1; // Draw Condition
        } else if (stat == 1) {
            game_state = turn+1; // Winning character
        } else if (stat == -1) {
            move = -1; // Invalid move
            game_state = 0;
        } else {
            game_state = 0;
        }

        if (stat >= 0)
        	turn = (turn + 1) % 2;

        return stat;
    };

    /**
     * Wrapper for AI based step calls. Really should not be used ona human
     * turn. Just passes a -1 move to step.
     */
    int step() {
        return step(-1);
    }

    /**
     * returns the last move made by the previous player
     *
     * @return integer representing the last column played into by the previous
     *                 player.
     */
    int getLastMove() {
        return players[(turn+1)%2]->lastMove();
    }

    /** string toString()
     *  Displays game state as a string
     */
    string toString() {
        return board.toString();
    };
};


#endif
