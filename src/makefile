CC = g++
CFLAGS = -Wall -Wextra -g3
INCLUDE = -I ../include
SRC_DIR = .
OUTPUT = output/main.exe

# 自动查找 src 目录下所有 .cpp 文件
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)


all: $(OUTPUT)

$(OUTPUT): $(SRC)
    $(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(OUTPUT)

clean:
    del $(OUTPUT)