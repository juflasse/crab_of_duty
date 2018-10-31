CC=gcc #Déclaration de variables
SRC=$(wildcard *.c)
H=$(wildcard *.h)
OBJ=$(SRC:.c=.o)
DEBUG=no
EXE="main"

ifeq ($(DEBUG), yes) #Condtions
$(info "Debug activé")
CFLAGS=-O2 -g -W -Wall
else
CFLAGS=-Wall -Wextra -g
endif

LIB=-lm -lSDL2 -lSDL2_ttf -lSDL2_image -lSANDAL2

all:$(OBJ)
	$(CC) -o $(EXE) $^ $(LIB)



%.o:%.c $(H)
	@$(CC) -c $< $(CFLAGS)
