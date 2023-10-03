# Define constants
BOARD_ROWS = 45
BOARD_COLS = 100

# Initialize the board
board = Array.new(BOARD_ROWS) { Array.new(BOARD_COLS, 0) }

# Function to print the current board
def print_board(board)
  board.each do |row|
    row.each do |cell|
      print cell == 1 ? "#" : " "
    end
    puts
  end
end

# Function to randomize the board
def randomize_board(board)
  board.map! { |row| row.map { rand(10) < 2 ? 1 : 0 } }
end

# Function to update the board based on the rules
def update_board(board)
  new_board = Array.new(BOARD_ROWS) { Array.new(BOARD_COLS, 0) }

  (0...BOARD_ROWS).each do |i|
    (0...BOARD_COLS).each do |j|
      live_neighbors = 0

      # Check 8 neighbors
      (-1..1).each do |dx|
        (-1..1).each do |dy|
          next if dx == 0 && dy == 0

          x = i + dx
          y = j + dy

          if x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS
            live_neighbors += 1 if board[x][y] == 1
          end
        end
      end

      # Apply the rules
      if board[i][j] == 1
        if live_neighbors < 2 || live_neighbors > 3
          new_board[i][j] = 0 # Cell dies
        else
          new_board[i][j] = 1 # Cell survives
        end
      else
        new_board[i][j] = 1 if live_neighbors == 3 # Cell reproduces
      end
    end
  end

  board.replace(new_board)
end

# Function to clear the board
def clear_board(board)
  board.map! { |row| row.map { 0 } }
end

# Main loop
loop do
  system("clear")
  print_board(board)

  puts "1. Make Alive\n2. Make Dead\n3. Start Simulation\n4. Randomize\n5. Quit"
  input = gets.chomp.to_i

  case input
  when 1
    puts "Enter the row and column (0 to #{BOARD_ROWS - 1}):"
    x, y = gets.chomp.split.map(&:to_i)
    if x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS
      board[x][y] = 1
      puts "Cell at (#{x}, #{y}) is now alive."
    else
      puts "Invalid input. Please enter valid coordinates."
    end
  when 2
    puts "Enter the row and column (0 to #{BOARD_ROWS - 1}):"
    x, y = gets.chomp.split.map(&:to_i)
    if x >= 0 && x < BOARD_ROWS && y >= 0 && y < BOARD_COLS
      board[x][y] = 0
      puts "Cell at (#{x}, #{y}) is now dead."
    else
      puts "Invalid input. Please enter valid coordinates."
    end
  when 3
    puts "Number of generations:"
    num_generations = gets.chomp.to_i
    num_generations.times do
      system("clear")
      print_board(board)
      update_board(board)
      sleep(0.1)
    end
  when 4
    randomize_board(board)
    puts "Board randomized."
  when 5
    break
  else
    puts "Invalid input. Please enter 1, 2, 3, 4, or 5."
  end
end
