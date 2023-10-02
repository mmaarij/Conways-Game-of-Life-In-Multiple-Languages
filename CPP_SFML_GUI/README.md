# Conway's Game of Life Implemented as a C++ Graphical Application using SFML

## Getting Started

### Install SMFL (https://www.sfml-dev.org/tutorials/2.6/start-linux.php)

```console
$ sudo apt-get install libsfml-dev
```

### Compile the program

```console
$ g++ main.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system
```

### Run the program

```console
$ ./main.out
```

## Usage

| Key               | Action                                   |
|-------------------|------------------------------------------|
| Right Mouse Click | Toggle cell state between alive and dead |
| Space             | Start/Stop the simulation                |
| C                 | Clear the board                          |
| R                 | Randomize the board                      |