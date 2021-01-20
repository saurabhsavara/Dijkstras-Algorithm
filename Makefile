OBJS    = Dijkstras.o
SOURCE  = Dijkstras.cpp
HEADER  =
OUT     = Dijkstras
CC       = g++
FLAGS    = -g -c -Wall
LFLAGS   =

all: $(OBJS)
        $(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Dijkstras.o: Dijkstras.cpp
        $(CC) $(FLAGS) Dijkstras.cpp


clean:
        rm -f $(OBJS) $(OUT)
