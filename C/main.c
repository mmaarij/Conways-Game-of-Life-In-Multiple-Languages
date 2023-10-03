#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_ROWS 45
#define BOARD_COLS 200

void printBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            if (board[i][j] == 0)
                printf(" ");
            else if (board[i][j] == 1)
                printf("#");
        }
        printf("\n");
    }
}

void randomizeBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    srand(time(NULL));
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int randomValue = rand() % 10;

            if (randomValue < 1)
            {
                board[i][j] = 1;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void updateBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    int newBoard[BOARD_ROWS][BOARD_COLS];
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int liveNeighbors = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                    {
                        continue;
                    }

                    int ni = i + dx;
                    int nj = j + dy;

                    if (ni >= 0 && ni < BOARD_ROWS && nj >= 0 && nj < BOARD_COLS && board[ni][nj] == 1)
                    {
                        liveNeighbors++;
                    }
                }
            }

            if (board[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3))
            {
                newBoard[i][j] = 0;
            }
            else if (board[i][j] == 0 && liveNeighbors == 3)
            {
                newBoard[i][j] = 1;
            }
            else
            {
                newBoard[i][j] = board[i][j];
            }
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            board[i][j] = newBoard[i][j];
        }
    }
}

int main()
{
    int board[BOARD_ROWS][BOARD_COLS];

    randomizeBoard(board);

    while (1)
    {
        printBoard(board);
        updateBoard(board);
        usleep(100000);
        system("clear");
    }

    return 0;
}