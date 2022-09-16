CC = gcc
CFLAGS   = -Wall -g -O1 `sdl2-config --cflags` # Compilation flags and include paths
LIBS     = -lSDL2_ttf -lm         			   # Additional Libraries
LFLAGS   = `sdl2-config --libs`                # Library flags
SRCS = game.c database.c events.c fonctions_SDL.c graphique.c init_and_clean.c update.c player.c enemy.c map.c fonctions_fichiers.c boss.c
OBJS = $(SRCS:.c=.o)
BIN = main
EXEC = $(BIN)

all: $(EXEC)

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $^ $(LIBS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(LFLAGS)

clean:
	$(RM) *.o *~ $(BIN)	

mrproper: clean
	$(RM) $(EXEC)
