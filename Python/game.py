import math

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


