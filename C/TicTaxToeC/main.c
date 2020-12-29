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

/*
     x, x, x, x, x,
     x, 6, 7, 8, x,
	 x,11, o,13, x,
	 x,16,17,18, x,
	 x, x, x, x, x

	horizontal => 11 + 1 => 12
	vertical => 7 + 5 => 12
	diagnal => 16 - 4 | 18 - 6 => 12
*/
const int Directions[4] = { 1, 5, 4, 6 };

const int ConvertTo25[9] = {
    6, 7, 8,
    11, 12, 13,
    16, 17, 18
};

int getNumForDir(int startSQ, const int dir, const int *board, const int us) {
    int found = 0;
    while(board[startSQ] != BORDER) {
        if(board[startSQ] != us) {
            break;
        }
        found++;
        startSQ += dir;
    }
    return found;
}

int findThreeInARow(const int *board, const int ourIndex, const int us) {
    int dirIndex = 0;
    int dir = 0;
    int threeCount = 1;

    for(dirIndex = 0; dirIndex < 4; dirIndex++) {
        dir = Directions[dirIndex];
        threeCount += getNumForDir(ourIndex + dir, dir, board, us);
        threeCount += getNumForDir(ourIndex + dir * -1, dir * -1, board, us);

        if(threeCount == 3) {
            break;
        }
        threeCount = 1;
    }
    return threeCount;
}

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
int hasEmpty(const int *board) {
    int index = 0;
    for(index = 0; index < 9; index++) {
        if(board[ConvertTo25[index]] == EMPTY) {
            return 1;
        }
    }
    return 0;
}

void makeMove(int *board, const int sq, const side) {
    board[sq] = side;

}

// for development stage: loop throgh all the calls. and store the idnex of the empty cell into availableMoves and randomly return the value stored in availableMoves.
int getComputerMove(const int *board) {
    int index = 0;
    int numFree = 0; // the number of empty cell
    int availableMoves[9];
    int randMove = 0;

    for(index = 0; index < 9; ++index) {
        if(board[ConvertTo25[index]] == EMPTY) {
            availableMoves[numFree++] = ConvertTo25[index];
        }
    }

    randMove = (rand() % numFree);
    return availableMoves[randMove];
}

int getHumanMove(const int *board) {
    char userInput[4];

    int moveOk = 0;
    int move = -1;

    while(moveOk == 0) {
        printf("Please enter a move form 1 to 9:");
        fgets(userInput, 3, stdin); // take the first 3 chars of the given string as an input
        fflush(stdin); // clear up a buffer

        // if the correct input is given, the strlen(userInput) returns 2. ex. 7\n
        if(strlen(userInput) != 2) {
            printf("Invalid strlen()\n");
            continue;
        }

        // transfer userInput into move
        if(sscanf(userInput, "%d", &move) != 1) {
            move = -1;
            printf("Invalid sscanf()\n");
            continue;
        }


        if(move < 1 || move > 9) {
            move = -1;
            printf("Invalid range\n");
            continue;
        }

        move--; // indexing

        if(board[ConvertTo25[move]] != EMPTY) {
            move = -1;
            printf("The given cell number is not available\n");
            continue;
        }

        moveOk = 1;
    }

    printf("Making move ... %d\n", (move + 1));
    return ConvertTo25[move];
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
            LastMoveMade = getHumanMove(&board[0]);
            makeMove(&board[0], LastMoveMade, Side);
            Side = CROSSES;
        } else {
            // AI move
            LastMoveMade = getComputerMove(&board[0]);
            makeMove(&board[0], LastMoveMade, Side);
            Side = NOUGHTS;
            printBoard(&board[0]);
        }

        /*
            Side: 0
            Side ^ 1 => Side: 1
            if side is 0, then ^ would flip the value to 1. 
        */
        if(findThreeInARow(board, LastMoveMade, Side ^ 1) == 3) {
            printf("--- Game Over ---\n");
            GameOver = 1;
            if(Side == NOUGHTS) {
                printf("Computer Wins\n");
            } else {
                printf("Human Wins\n");
            }
        }

        if(!hasEmpty(board)) {
            printf("Game Over!\n");
            GameOver = 1;
            printf("It's a draw");
        }
    }
    printBoard(&board[0]);
}

int main()
{
    printf("Tic Tac Toe w/ MiniMax Algorithm\n");

    srand(time(NULL));
    runGame();


    return 0;
}
