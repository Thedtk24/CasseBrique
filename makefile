CC = gcc
CFLAGS = -Wall -Wextra -I.
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = main.c palette.c brique.c balle.c
OBJ = $(SRC:.c=.o)
EXEC = breakout

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)