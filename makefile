SRC = main.c
OBJ = $(SRC:.c=.o)
EXE = $(SRC:.c=.e)
	
CFLAGS = -g -lm
	
all : $(EXE)
	
$(EXE) : $(OBJ)
	gcc  $(OBJ) -o  $(EXE)
	
 $(OBJ) :  $(SRC)
	gcc -c  $(CFLAGS)  $(SRC)
