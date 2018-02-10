# reversi-game with AI player
# by Arbai Fayçal & Benabdesselam Nadir

A reversi game with 3 mode :
  - Human vs Human
  - Human vs File
  - Human vs AI (alias Skynet)
  
 The AI is an implementation of the Monte Carlo algorithm. Put simply : it generates 500 
 virtual games with the current state of the game and randomly chooses legal moves for 
 each player. Among the legal moves of the current player at the current state of the game, 
 the selected one is the one with the most success in the virtual games.
 Several ways to optimize the process are used and can be found in the code.
