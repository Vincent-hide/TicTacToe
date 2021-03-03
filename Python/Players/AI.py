import math
import random
from .Player import Player


class WeakAI(Player):
  def __int__(self, letter):
    super().__init__(letter)

  def get_move(self, game):
    square = random.choice(game.available_moves())
    return square


class SmartAI(Player):
  def __init__(self, letter):
    super().__init__(letter)

  def get_move(self, tictactoe):
    if len(tictactoe.available_moves()) == 9:
      # if SmartAI gets the first move, it puts in random square
      square = random.choice(tictactoe.available_moves)

      # or put in the middle which is the best option as the first move of the game
      # square = 5

    else:
      square = self.minimax(tictactoe, self.letter)['position']
    return square

  def minimax(self, tictactoe, player):
    # print("   MINIMAX tic  ", tictactoe)
    # print("   MINIMAX player  ", player)
    max_player = self.letter
    opponent = 'O' if player == 'X' else 'X'

    if tictactoe.current_winner == opponent:
      spaces = tictactoe.num_empty() + 1  # number of empty spaces + 1
      # if game is over and opponent win => 1 * number of spaces + 1, otherwise => -1 * number of spaces + 1
      return {
        'position': None,
        'score': 1 * spaces if opponent == max_player else -1 * spaces
      }

    elif not tictactoe.empty_squares():
      # the game is over and it is draw
      return {
        'position': None,
        'score': 0
      }

    else:
      if player == max_player:
        best = {
          'position': None,
          'score': -math.inf
        }

      else:
        best = {
          'position': None,
          'score': math.inf
        }

      for possible_move in tictactoe.available_moves():
        tictactoe.make_move(possible_move, player)
        future_scores = self.minimax(tictactoe, opponent)

        # remove the letter from the board. similar to back-tracking
        tictactoe.board[possible_move] = ' '
        tictactoe.current_winner = None
        future_scores['position'] = possible_move

        # 0 == 0
        if player == max_player:
          if future_scores['score'] > best['score']:
            best = future_scores

        else:
          if future_scores['score'] < best['score']:
            best = future_scores
    return best
