import os
import random
import time

BOARD_ROWS = 45
BOARD_COLS = 200

def print_board(board):
    for row in board:
        for cell in row:
            if cell == 0:
                print(" ", end="")
            else:
                print("#", end="")
        print()

def randomize_board(board):
    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            random_value = random.randint(0, 9)
            if random_value < 1:
                board[i][j] = 1
            else:
                board[i][j] = 0

def update_board(board):
    new_board = [[0] * BOARD_COLS for _ in range(BOARD_ROWS)]

    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            live_neighbors = 0

            for dx in [-1, 0, 1]:
                for dy in [-1, 0, 1]:
                    if dx == 0 and dy == 0:
                        continue
                    x = i + dx
                    y = j + dy
                    if 0 <= x < BOARD_ROWS and 0 <= y < BOARD_COLS and board[x][y] == 1:
                        live_neighbors += 1

            if board[i][j] == 1:
                if live_neighbors < 2 or live_neighbors > 3:
                    new_board[i][j] = 0
                else:
                    new_board[i][j] = 1
            else:
                if live_neighbors == 3:
                    new_board[i][j] = 1

    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            board[i][j] = new_board[i][j]

def clear_board(board):
    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            board[i][j] = 0

def main():
    board = [[0] * BOARD_COLS for _ in range(BOARD_ROWS)]

    while True:
        os.system('clear' if os.name == 'posix' else 'cls')  # Clear the terminal

        print_board(board)

        print("1. Make Alive\n2. Make Dead\n3. Start Simulation\n4. Random\n5. Quit")
        input_choice = input()

        if input_choice == "1":
            x, y = map(int, input("Enter the row and column (0 to {}): ".format(BOARD_ROWS - 1)).split())
            if 0 <= x < BOARD_ROWS and 0 <= y < BOARD_COLS:
                board[x][y] = 1
                print("Cell at ({}, {}) is now alive.".format(x, y))
            else:
                print("Invalid input. Please enter valid coordinates.")

        elif input_choice == "2":
            x, y = map(int, input("Enter the row and column (0 to {}): ".format(BOARD_ROWS - 1)).split())
            if 0 <= x < BOARD_ROWS and 0 <= y < BOARD_COLS:
                board[x][y] = 0
                print("Cell at ({}, {}) is now dead.".format(x, y))
            else:
                print("Invalid input. Please enter valid coordinates.")

        elif input_choice == "3":
            num_generations = int(input("Number of generations: "))
            for _ in range(num_generations):
                os.system('clear' if os.name == 'posix' else 'cls')
                print_board(board)
                update_board(board)
                time.sleep(0.1)  # Pause for 100 milliseconds between generations

        elif input_choice == "4":
            randomize_board(board)
            print("Board randomized.")

        elif input_choice == "5":
            break

        else:
            print("Invalid input. Please enter 1, 2, 3, 4, or 5.")

if __name__ == "__main__":
    main()
