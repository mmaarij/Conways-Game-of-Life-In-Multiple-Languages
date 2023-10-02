const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

const BOARD_ROWS = 150;
const BOARD_COLS = 200;
const CELL_SIZE = 5; // Adjust this to change cell size

canvas.width = BOARD_COLS * CELL_SIZE;
canvas.height = BOARD_ROWS * CELL_SIZE;

let board = new Array(BOARD_ROWS).fill(null).map(() => new Array(BOARD_COLS).fill(0));
let simulationRunning = false;
let requestId = null;

// Function to draw the board
function drawBoard() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for (let i = 0; i < BOARD_ROWS; i++) {
        for (let j = 0; j < BOARD_COLS; j++) {
            ctx.fillStyle = board[i][j] === 1 ? 'black' : 'white';
            ctx.fillRect(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
}

// Function to update the board
function updateBoard() {
    const newBoard = new Array(BOARD_ROWS).fill(null).map(() => new Array(BOARD_COLS).fill(0));

    for (let i = 0; i < BOARD_ROWS; i++) {
        for (let j = 0; j < BOARD_COLS; j++) {
            const liveNeighbors = countLiveNeighbors(i, j);

            if (board[i][j] === 1) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newBoard[i][j] = 0; // Cell dies
                } else {
                    newBoard[i][j] = 1; // Cell survives
                }
            } else {
                if (liveNeighbors === 3) {
                    newBoard[i][j] = 1; // Cell reproduces
                } else {
                    newBoard[i][j] = 0; // Cell remains dead
                }
            }
        }
    }

    board = newBoard;
}

// Function to count live neighbors
function countLiveNeighbors(row, col) {
    let liveNeighbors = 0;
    const neighbors = [-1, 0, 1];

    for (const dx of neighbors) {
        for (const dy of neighbors) {
            if (dx === 0 && dy === 0) continue; // Skip the current cell
            const x = row + dx;
            const y = col + dy;

            if (x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS) {
                liveNeighbors += board[x][y];
            }
        }
    }

    return liveNeighbors;
}

// Function to start or stop the simulation
function startStopSimulation() {
    simulationRunning = !simulationRunning;
    if (simulationRunning) {
        document.getElementById('startStopButton').textContent = 'Stop';
        requestAnimationFrame(animate);
    } else {
        document.getElementById('startStopButton').textContent = 'Start';
        cancelAnimationFrame(requestId);
    }
}

// Function to clear the board
function clearBoard() {
    board = new Array(BOARD_ROWS).fill(null).map(() => new Array(BOARD_COLS).fill(0));
    drawBoard();
}

// Function to randomize the board
function randomizeBoard() {
    for (let i = 0; i < BOARD_ROWS; i++) {
        for (let j = 0; j < BOARD_COLS; j++) {
            const randomValue = Math.random();
            board[i][j] = randomValue < 0.1 ? 1 : 0; // Adjust the threshold for density
        }
    }
    drawBoard();
}

// Function to animate the simulation
function animate() {
    if (!simulationRunning) {
        return;
    }
    updateBoard();
    drawBoard();

    // Add a delay (in milliseconds) between generations
    const delay = 100;
    setTimeout(() => {
        requestId = requestAnimationFrame(animate);
    }, delay);
}

// Event listeners
canvas.addEventListener('click', (event) => {
    const rect = canvas.getBoundingClientRect();
    const mouseX = event.clientX - rect.left;
    const mouseY = event.clientY - rect.top;
    const col = Math.floor(mouseX / CELL_SIZE);
    const row = Math.floor(mouseY / CELL_SIZE);

    if (row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS) {
        board[row][col] = 1 - board[row][col];
        drawBoard();
    }
});

document.getElementById('startStopButton').addEventListener('click', startStopSimulation);
document.getElementById('clearButton').addEventListener('click', clearBoard);
document.getElementById('randomizeButton').addEventListener('click', randomizeBoard);

// Initial drawing of the board
drawBoard();
