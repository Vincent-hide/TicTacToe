from .Player import Player

class Human(Player):
  def __init__(self, letter):
    super().__init__(letter)

  # returns the square/input if that is not taken yet
  def get_move(self, tictactoe):
    valid_square = False
    val = None
    while not valid_square:
      square = input(self.letter + "\'s turn. Make a move [0-9]: ")
      try:
        val = int(square)
        if val not in tictactoe.available_moves():
          raise ValueError
        else:
          valid_square = True
      except ValueError:
        print("Invalid square. Try again.")
    return val
