CC = g++
SRC = src
INC = include
OBJ = obj
CFLAGS = -Werror -Wall -I $(INC) -c
OBJS = $(OBJ)/rock.o $(OBJ)/main.o
EXE = tp02

$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean :
	rm $(OBJ)/* $(EXE) *.out