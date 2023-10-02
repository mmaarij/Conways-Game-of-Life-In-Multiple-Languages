#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BOARD_ROWS 45
#define BOARD_COLS 200

void printBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            if (board[i][j] == 0)
                cout << " ";
            else if (board[i][j] == 1)
                cout << "#";
        }
        cout << endl;
    }
}

void randomizeBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            // Generate a random number between 0 and 9.
            int randomValue = rand() % 10;

            // If the random value is less than 3 (30% chance), set the cell to 1 (alive).
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

            // Check 8 neighbors
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue; // Skip the current cell
                    int x = i + dx;
                    int y = j + dy;
                    if (x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS)
                    {
                        if (board[x][y] == 1)
                        {
                            liveNeighbors++;
                        }
                    }
                }
            }

            // Apply the rules
            if (board[i][j] == 1)
            {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                {
                    newBoard[i][j] = 0; // Cell dies
                }
                else
                {
                    newBoard[i][j] = 1; // Cell survives
                }
            }
            else
            {
                if (liveNeighbors == 3)
                {
                    newBoard[i][j] = 1; // Cell reproduces
                }
                else
                {
                    newBoard[i][j] = 0; // Cell remains dead
                }
            }
        }
    }

    // Copy the new board to the current board
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            board[i][j] = newBoard[i][j];
        }
    }
}

int main(void)
{
    int board[BOARD_ROWS][BOARD_COLS];

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            board[i][j] = 0;
        }
    }

    int input = 0;

    while (true)
    {
        // Print the current board
        printBoard(board);

        // Prompt the user for input
        cout << "1. Make Alive\n2. Make Dead\n3. Start Simulation\n4. Random\n5. Quit" << endl;
        cin >> input;
        system("clear");

        if (input == 1)
        {
            // Make a cell alive based on user input
            int x, y;
            cout << "Enter the row and column (0 to " << BOARD_ROWS - 1 << "): ";
            cin >> x >> y;

            if (x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS)
            {
                board[x][y] = 1;
                cout << "Cell at (" << x << ", " << y << ") is now alive." << endl;
            }
            else
            {
                cout << "Invalid input. Please enter valid coordinates." << endl;
            }
        }
        else if (input == 2)
        {
            // Make a cell dead based on user input
            int x, y;
            cout << "Enter the row and column (0 to " << BOARD_ROWS - 1 << "): ";
            cin >> x >> y;

            if (x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS)
            {
                board[x][y] = 0;
                cout << "Cell at (" << x << ", " << y << ") is now dead." << endl;
            }
            else
            {
                cout << "Invalid input. Please enter valid coordinates." << endl;
            }
        }
        else if (input == 3)
        {
            cout << "Number of generations: ";
            cin >> input;
            for (int i = 0; i < input; i++)
            {
                printBoard(board);
                updateBoard(board);
                usleep(100000); // 100 milliseconds
                system("clear");
            }
            input = 0;
        }
        else if (input == 4)
        {
            randomizeBoard(board);
            cout << "Board randomized." << endl;
        }

        else if (input == 5)
        {
            // Quit the program
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 1, 2, 3, or 4." << endl;
        }
    }

    return 0;
}