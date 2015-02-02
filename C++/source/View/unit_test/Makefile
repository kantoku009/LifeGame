#LifeGmaeViewのUnitTest
CC = g++
SRCS = ./test_LifeGameViewOnCurses.cpp ../LifeGameViewOnCurses.cpp 
LIBS = -lcurses
LDFLAGS = -Wall -O2
OUTFILE = test_LifeGameView

LifeGameView:
	$(CC) $(LDFLAGS) -o $(OUTFILE) $(LIBS) $(SRCS) 

clean:
	rm $(OUTFILE)

