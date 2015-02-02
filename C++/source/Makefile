CC = g++
SRCS = ./main.cpp ./Controller/LifeGameController.cpp ./View/LifeGameViewOnCurses.cpp ./Model/MatrixCell.cpp ./Model/Cell.cpp
LIBS = -lcurses
LDFLAGS = -Wall -O2
OUTFILE = LifeGame

LifeGame:
	$(CC) $(LDFLAGS) -o $(OUTFILE) $(LIBS) $(SRCS) 

clean:
	rm $(OUTFILE)

