#以下クラスのユニットテスト
#　・Cell.cpp
#　・MatrixCell.cpp
CC = g++
SRCS_CELL = test_Cell.cpp ../Cell.cpp 
SRCS_MATRIX = test_MatrixCell.cpp ../MatrixCell.cpp ../Cell.cpp
OUTFILE_CELL = test_Cell
OUTFILE_MATRIX = test_Matrix_Cell
LDFLAGS = -Wall -O2

cell_test:
	$(CC) $(LDFLAGS) $(SRCS_CELL) -o $(OUTFILE_CELL)
	$(CC) $(LDFLAGS) $(SRCS_MATRIX) -o $(OUTFILE_MATRIX)

clean:
	rm $(OUTFILE_CELL) $(OUTFILE_MATRIX)

