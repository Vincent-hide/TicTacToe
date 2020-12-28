#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  const NOUGHTS = 1;  // Player
  const CROSSES = 2;  // AI
  const BORDER = 3;
  const EMPTY = 0;
*/

enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN = 4, COMPWIN, DRAW }; // 4, 5, 6, as they are not specified

const int ConvertTo25[9] = {
    6, 7, 8,
    11, 12, 13,
    16, 17, 18
};

void initializeBord(int *board) {
    int index = 0;

    for(index = 0; index < 25; index++) {
        board[index] = BORDER;
    };

    for(index = 0; index < 9; index++) {
        board[ConvertTo25[index]] = EMPTY;
    };
};

void printBoard(const int *board) {
    int index = 0;
    char symbol[] = "OX|-";
    printf("\nBoard\n");
    for(index = 0; index < 9; index++) {
        if(index != 0 && index%3 == 0) {
            printf("\n\n");
        };

        printf("%4c", symbol[board[ConvertTo25[index]]]);
    };
    printf("\n");
};

// Checks if there is still an empty spot
int HasEmpty(const int *board) {
    int index = 0;
    for(index = 0; index < 9; index++) {
        if(board[ConvertTo25[index]] == EMPTY) {
            return true;
        }
    }
    return 0;
}

void MakeMove(int *board, const int sq, const side) {
    board[sq] = side;

}

// Initiate a game and facilitate a game
void runGame() {
    int GameOver = 0;
    int Side = NOUGHTS;
    int LastMoveMade = 0;
    int board[25];

    initializeBord(&board[0]); // index 0 starts where the board data is stored
    printBoard(&board[0]);

    while(!GameOver) {
        if(Side == NOUGHTS) {
            // player move

        } else {
            // AI move
            printBoard(&board[0]);
        }
    }
}

int main()
{
    printf("Tic Tac Toe w/ MiniMax Algorithm\n");

    srand(time(NULL));
    runGame();


    return 0;
}
