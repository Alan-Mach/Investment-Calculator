SRC = main.c
OBJ = $(SRC:.c=.o)
EXE = $(SRC:.c=.e)
	
CFLAGS = -g
LINKER = -lm
	
all : $(EXE)
	
$(EXE) : $(OBJ)
	gcc  $(OBJ) -o  $(EXE)  $(LINKER)
	
$(OBJ) :  $(SRC)
	gcc -c  $(CFLAGS)  $(SRC)

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)
