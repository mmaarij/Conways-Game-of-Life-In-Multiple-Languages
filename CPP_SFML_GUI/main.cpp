#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cstdlib>
#include <time.h>

using namespace std;

#define BOARD_ROWS 150
#define BOARD_COLS 200

struct timespec delay = {.tv_sec = 0, .tv_nsec = 100000000}; // for use in nanosleep later

void drawBoard(sf::RenderWindow &window, int board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(10, 10));
            cell.setPosition(j * 10, i * 10);
            if (board[i][j] == 0)
                cell.setFillColor(sf::Color::White);
            else if (board[i][j] == 1)
                cell.setFillColor(sf::Color::Black);
            window.draw(cell);
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

void clearBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            board[i][j] = 0; // Set all cells to dead
        }
    }
}

void randomizeBoard(int board[BOARD_ROWS][BOARD_COLS])
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int randomValue = rand() % 10;
            if (randomValue < 1)
            {
                board[i][j] = 1; // Randomly set some cells to alive
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_COLS * 10, BOARD_ROWS * 10), "Conway's Game of Life");

    int board[BOARD_ROWS][BOARD_COLS];
    // Initialize the board...

    bool simulationRunning = false;
    int numGenerations = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Handle mouse click events to toggle cell state
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / 10;
                int col = mousePos.x / 10;
                if (row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS)
                {
                    board[row][col] = 1 - board[row][col];
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    simulationRunning = !simulationRunning;
                }
                else if (event.key.code == sf::Keyboard::C)
                {
                    clearBoard(board); // Clear the board when 'C' is pressed
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    randomizeBoard(board); // Randomize the board when 'R' is pressed
                }
            }
        }

        window.clear();

        if (simulationRunning)
        {
            updateBoard(board);
            if (nanosleep(&delay, NULL) == -1)
            {
                perror("nanosleep");
            }
        }

        drawBoard(window, board);
        window.display();
    }

    return 0;
}
