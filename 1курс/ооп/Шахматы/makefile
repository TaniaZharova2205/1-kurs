chess: chessman.o chesslib.o chess.cc
	g++ -o chess chess.cc chessman.o chesslib.o
chessman.o: chessman.h chessman.cc
	g++ -c chessman.cc -o chessman.o 
chesslib.o: chesslib.h chesslib.cc chessman.h
	g++ -c chesslib.cc -o chesslib.o
