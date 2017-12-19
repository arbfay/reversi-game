all:
	g++ -std=c++11 -pthread game.cpp board.cpp player.cpp main.cpp skynet.cpp -o main
