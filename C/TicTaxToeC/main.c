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

const int InMiddle = 4;
const int Corners[4] = { 0, 2, 6, 8 };

int play = 0;
int positions = 0;
int maxPlay = 0;

int getNumForDir(int LastMoveMade, const int dir, const int *board, const int Side, const int check) {
    int found = 0;
    while(board[LastMoveMade] != BORDER) {
        if(board[LastMoveMade] != Side) {
            break;
        }
        found++;
        LastMoveMade += dir;
    }
    return found;
}

int findThreeInARow(const int *board, const int LastMoveMade, const int Side) {
    int dirIndex = 0;
    int dir = 0;
    int threeCount = 1;

    for(dirIndex = 0; dirIndex < 4; dirIndex++) {
        dir = Directions[dirIndex];
        // if the LastMoveMade is 12(the center) and dir is 5(horizontal line), it checks 17, 22
        threeCount += getNumForDir(LastMoveMade + dir, dir, board, Side, 1);
        // if the LastMoveMade is 12(the center) and dir is 5(horizontal line), it checks 7, 2
        threeCount += getNumForDir(LastMoveMade + (dir * -1), dir * -1, board, Side, 0);

        if(threeCount == 3) {
            break;
        }
        threeCount = 1;
    }
    return threeCount;
}

int findThreeInARowAllBoard(const int *board, const int Side) {
    int threeFound = 0;
    int index;
    for(index=0; index<9; index++) {
        if(board[ConvertTo25[index]]== Side) {
            if(findThreeInARow(board, ConvertTo25[index], Side) == 3) {
                threeFound = 1;
                break;
            }
        }
    }
    return threeFound;
}

int evalForWin(const int *board, const int Side) {
    if(findThreeInARowAllBoard(board, Side) != 0) {
        return 1;
    }
    if(findThreeInARowAllBoard(board, Side ^ 1) != 0) {
        return -1;
    }
    return 0;
}

int miniMax(int *board, int side) {
    int moveList[9];
    int moveCount = 0;
    int bestScore = -2;
    int score = -2;
    int bestMove = -1;
    int move;
    int index;

    if(play > maxPlay) {
        maxPlay = play;
    }
    positions++;

    if(play > 0) {
        score = evalForWin(board, side);
        if(score != 0) {
            return score;
        }
    }

    for(index=0; index<9; index++) {
        if(board[ConvertTo25[index]] == EMPTY) {
            moveList[moveCount++] = ConvertTo25[index];
        }
    }

    for(index=0; index<moveCount; index++) {
        move = moveList[index];
        board[move] = side;

        play++;
        score = -miniMax(board, side^1);

        if(score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        board[move] = EMPTY;
        play--;
    }

    if(moveCount == 0) {
        bestScore = findThreeInARowAllBoard(board, side);
    }

    if(play!=0) {
		return bestScore;
	} else {
		return bestMove;
	}

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

int getWinningMove(int *board, const int Side) {
    int ourMove = -1;
    int winFound = 0;
    int index = 0;

    for(index = 0; index < 9; index++) {
        if(board[ConvertTo25[index]] == EMPTY) {
            ourMove = ConvertTo25[index];
            board[ourMove] = Side;

            if(findThreeInARow(board, ourMove, Side) == 3) {
                winFound = 1;
            }
            board[ourMove] = EMPTY;
            if(winFound == 1) {
                return ourMove;
            }
            ourMove = -1;
        };
    }
    return ourMove;
}

void makeMove(int *board, const int LastMoveMade, const Side) {
    board[LastMoveMade] = Side;
}

int getNextBest(const int *board) {
    int ourMove = ConvertTo25[InMiddle];
    if(board[ourMove] == EMPTY) {
        return ourMove;
    }

    int index = 0;
    ourMove = -1;

    for(index = 0; index < 4; index++) {
        ourMove = ConvertTo25[Corners[index]];
        if(board[ourMove] == EMPTY) {
            return ourMove;
        }
        ourMove = -1;
    }
    return ourMove;
}

// for development stage: loop throgh all the calls. and store the idnex of the empty cell into availableMoves and randomly return the value stored in availableMoves.
int getComputerMove(int *board, const int Side) {
    int index = 0;
    int numFree = 0; // the number of empty cell
    int availableMoves[9];
    int randMove = 0;

    randMove = getWinningMove(board, Side);
    if(randMove != -1) {
        return randMove;
    }

    // Computer will prioritize to block you rather than wining over you
    randMove = getWinningMove(board, Side ^ 1);
    if(randMove != -1) {
        return randMove;
    }

    randMove = getNextBest(board);
    if(randMove != -1) {
        return randMove;
    }

    randMove = 0;
    for(index = 0; index < 9; ++index) {
        if(board[ConvertTo25[index]] == EMPTY) {
            availableMoves[numFree++] = ConvertTo25[index];
        }
    }

    randMove = (rand() % numFree);
    return availableMoves[randMove];
}


int getComputerMoveMiniMax(int *board, const int side) {
    play = 0;
    positions = 0;
    maxPlay = 0;
    int best = miniMax(board, side);
    printf("Finished searching positions: %d maxDepth: %d bestMove:%d\n", positions, maxPlay, best);
    return best;
}

int getHumanMove(const int *board) {
    char userInput[4];

    int moveOk = 0;
    int move = -1;

    while(moveOk == 0) {
        printf("Please enter a move form 1 to 9: ");
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
            LastMoveMade = getComputerMoveMiniMax(&board[0], Side);
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
