DIR_INC = ./code/inc
DIR_SRC = ./code/src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard $(DIR_SRC)/*.c)  
OBJ = $(patsubst %.c,$(DIR_OBJ)/%.o,$(notdir $(SRC))) 
TARGET = $(DIR_BIN)/lcd

CC = gcc
CFLAGS = -g -Wall -I$(DIR_INC) -lwiringPi

$(TARGET):$(OBJ)
	    $(CC) -o $@ $^ $(CFLAGS)
	        
$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	    $(CC) -o $@ -c $< $(CFLAGS)


.PHONY:clean
clean:
	rm -rf $(DIR_OBJ)/*.o $(TARGET)
