CC=g++
IDIR=include
ODIR=obj
SDIR=source
CFLAGS= -g -std=c++0x -I $(IDIR) -Wall -Wextra -pedantic -O2
LSFML=-lsfml-graphics -lsfml-system -lsfml-window
APP=game

all: $(APP)

$(APP): $(ODIR)/Snake.o $(ODIR)/Tiles.o $(ODIR)/Main.o
	$(CC) -o $(APP) $(ODIR)/*.o $(LSFML)

$(ODIR)/Main.o: $(SDIR)/Main.cpp
	$(CC) $(CFLAGS) -c $(SDIR)/Main.cpp
	mv Main.o $(ODIR)

$(ODIR)/Tiles.o: $(SDIR)/Tiles.cpp $(IDIR)/Tiles.hpp $(IDIR)/Definitions.hpp
	$(CC) $(CFLAGS) -c $(SDIR)/Tiles.cpp
	mv Tiles.o $(ODIR)

$(ODIR)/Snake.o: $(SDIR)/Snake.cpp $(IDIR)/Snake.hpp $(IDIR)/Definitions.hpp
	$(CC) $(CFLAGS) -c $(SDIR)/Snake.cpp
	mv Snake.o $(ODIR)

clean:
	rm $(ODIR)/*.o $(APP)

