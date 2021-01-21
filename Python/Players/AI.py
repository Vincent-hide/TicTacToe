import random
from .Player import Player

class WeakAI(Player):
  def __int__(self, letter):
    super().__init__(letter)

  def get_move(self, game):
    square = random.choice(game.available_moves())
    return square