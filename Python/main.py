from TicTacToe import TicTacToe
from Players.Human import Human
from Players.AI import WeakAI, SmartAI
from utils import play

if __name__ == '__main__':
  x_player = Human('X')
  o_player = SmartAI('O')
  t = TicTacToe()
  play(t, x_player, o_player, print_game=True)