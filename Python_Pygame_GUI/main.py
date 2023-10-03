import pygame
import random
import time

# Define constants
BOARD_ROWS = 150
BOARD_COLS = 250
CELL_SIZE = 5
WINDOW_WIDTH = BOARD_COLS * CELL_SIZE
WINDOW_HEIGHT = BOARD_ROWS * CELL_SIZE
FPS = 30

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

def initialize_board():
    return [[0 for _ in range(BOARD_COLS)] for _ in range(BOARD_ROWS)]

def randomize_board(board):
    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            random_value = random.randint(0, 9)
            if random_value < 2:
                board[i][j] = 1
            else:
                board[i][j] = 0

def draw_board(screen, board):
    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLS):
            color = BLACK if board[i][j] == 1 else WHITE
            pygame.draw.rect(screen, color, (j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE))

def update_board(board):
    new_board = [[0 for _ in range(BOARD_COLS)] for _ in range(BOARD_ROWS)]

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

def main():
    pygame.init()
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("Conway's Game of Life")

    clock = pygame.time.Clock()
    board = initialize_board()
    randomize_board(board)

    running = False
    num_generations = 1

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                row = y // CELL_SIZE
                col = x // CELL_SIZE
                board[row][col] = 1 - board[row][col]
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    running = not running
                elif event.key == pygame.K_c:
                    board = initialize_board()
                elif event.key == pygame.K_r:
                    randomize_board(board)

        screen.fill(WHITE)

        if running:
            update_board(board)
            time.sleep(0.1)

        draw_board(screen, board)
        pygame.display.flip()
        clock.tick(FPS)

if __name__ == "__main__":
    main()
