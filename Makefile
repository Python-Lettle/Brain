CC = gcc
INC = include
SRC = src

CFlags = -Wall -g -O0 -std=c99 -lm
#============================================================================
# 框架需编译的文件
#============================================================================
MLFrame_file = $(SRC)/frame.c $(SRC)/Linear.c $(SRC)/Matrix.c $(SRC)/util.c $(SRC)/Model.c


FILES = test.c $(MLFrame_file)

test_name = test

.PHONY: all wintest test clean

all:
	$(CC) $(CFlags) -I $(INC) -o $(test_name) $(FILES)

	@echo "测试程序编译成功!"

wintest:
	$(CC) -I $(INC) -o $(test_name).exe $(FILES)

test:
	$(CC) -I $(INC) -o $(test_name) $(FILES)

clean:
	rm -f $(test_name) $(test_name).exe
