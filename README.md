# Conway's Game of Life

Conway's Game of Life is a cellular automaton devised by mathematician John Conway in 1970. It is a zero-player game, meaning that its progression is determined by its initial state, with no further input required. The game is a classic example of emergent complexity and is known for its ability to create diverse patterns and behaviors from simple rules.

## Rules

The game is played on a grid of cells, where each cell can be in one of two states: alive or dead.

- **Birth**: A dead cell with exactly three live neighbors becomes alive (reproduction).
- **Survival**: A live cell with two or three live neighbors remains alive.
- **Death**: In all other cases, a cell dies or remains dead.

These simple rules give rise to complex and fascinating patterns and can be used to simulate various biological and natural phenomena.

![Conway's Game of Life](https://upload.wikimedia.org/wikipedia/commons/e/e5/Gospers_glider_gun.gif)

## Project Overview

This repository contains implementations of Conway's Game of Life in multiple programming languages. Each implementation offers different features and user interfaces.

### Implemented Versions

- **C++ Terminal Application**: A command-line version of the game with text-based input and output.
- **C++ SFML GUI Application**: A graphical version of the game using the Simple and Fast Multimedia Library (SFML).

### How to Run

For detailed instructions on running each version of the game, refer to their respective README files or directories.

### Contributing

If you'd like to contribute to this project by adding implementations in other programming languages or improving existing ones, please feel free to fork this repository and submit a pull request.

### License

This project is licensed under the [MIT License](LICENSE).

## Get Started

Choose an implementation from the list below to get started:

- [C++ Terminal Application](C++ Terminal)
- [C++ SFML GUI Application](cpp-sfml)