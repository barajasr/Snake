CC=g++
IDIR=include
ODIR=obj
SDIR=source
CFLAGS=-I $(IDIR) -Wall -Wextra -pedantic -O2
APP=snake

all: $(APP)

$(APP): $(ODIR)/*.o
	$(CC) -o $(APP) $(ODIR)/*.o  -lsfml-graphics -lsfml-system -lsfml-window

$(ODIR)/*.o: $(SDIR)/*.cpp $(IDIR)/*.hpp
	$(CC) $(CFLAGS) -c $(SDIR)/*.cpp
	mv *.o $(ODIR)

clean:
	rm $(ODIR)/*.o $(APP)

