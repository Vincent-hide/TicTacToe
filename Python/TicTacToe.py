class TicTacToe:
  def __init__(self):
    self.board = self.make_board()
    self.current_winner = None

  @staticmethod
  def make_board():
    return [' ' for _ in range(9)]

  def print_board(self):
    print('-------------')
    for i in range(3):
      #  i=0 => 0:3
      #  i=1 => 3:6 ...
      for row in [self.board[i * 3: (i + 1) * 3]]:
        print('| ' + ' | '.join(row) + ' |')
        print('-------------')

  @staticmethod
  def print_board_num():
    box = []
    for i in range(3):
      list = []
      for s in range(i * 3, (i + 1) * 3):
        list.append(str(s))
      box.append(list)

    for row in box:
      print('| ' + ' | '.join(row) + ' |')

  def empty_squares(self):
    return ' ' in self.board

  def num_empty(self):
    return self.board.count(' ')

  def available_moves(self):
    list = []
    for i, x in enumerate(self.board):
      if (x == " "):
        list.append(i)
    return list

  # square: cell that represents player's input
  # letter: X or O
  def make_move(self, square, letter):
    if self.board[square] == ' ':
      self.board[square] = letter
      if self.isGameOver(square, letter):
        self.current_winner = letter
      return True
    return False

  def isGameOver(self, square, letter):
    # finds which row the square/input belongs to
    nth_rows = square // 3
    # take out the row as a list to be checked
    row = self.board[nth_rows * 3: (nth_rows + 1) * 3]

    if all([s == letter for s in row]):
      return True

    nth_col = square % 3
    col = [self.board[nth_col + i * 3] for i in range(3)]

    if all([s == letter for s in col]):
      return True

    if square % 2 == 0:
      diagnalLR = [self.board[i] for i in [0, 4, 8]]
      if all([s == letter for s in diagnalLR]):
        return True

      diagnalRL = [self.board[i] for i in [2, 4, 6]]
      if all([s == letter for s in diagnalRL]):
        return True
    return False
