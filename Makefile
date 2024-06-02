CC = gcc
INC = include
SRC = src
#============================================================================
# 框架需编译的文件
#============================================================================
MLFrame_file = $(SRC)/frame.c $(SRC)/Linear.c $(SRC)/Matrix.c


FILES = test.c $(MLFrame_file)

test_name = test

.PHONY: all wintest test clean

all:
	$(CC) -I $(INC) -o $(test_name) $(FILES)

wintest:
	$(CC) -I $(INC) -o $(test_name).exe $(FILES)

test:
	$(CC) -I $(INC) -o $(test_name) $(FILES)

clean:
	rm -f $(test_name) $(test_name).exe
