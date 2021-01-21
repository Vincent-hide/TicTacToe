import time

def play(tictactoe, x_player, o_player, print_game=True):
  if print_game:
    tictactoe.print_board_num()

  letter = "X"
  while tictactoe.empty_squares():
    if letter == "O":
      square = o_player.get_move(tictactoe)
    else:
      square = x_player.get_move(tictactoe)

    if tictactoe.make_move(square, letter):
      if print_game:
        print(letter + ' makes a move to square {}'.format(square))
        tictactoe.print_board()
        print('')

      if tictactoe.current_winner:
        if print_game:
          print(letter + ' wins!')
        return letter

      # swap a player
      letter = 'O' if letter == 'X' else 'X'

    # to simulate that AI is thinking
    time.sleep(.5)

  if print_game:
    print('draw')