CC = cmd.exe /c g++
BIN = main

all: $(BIN)

%.o: %.cpp
	$(CC) -c $^

compile:
	$(CC) -c *.cpp

$(BIN): main.o Game.o
	$(CC) $^ -o $@

release:
	$(CC) -O3 -static-libgcc -static-libstdc++ *.o -o $(BIN).exe

zip:
	zip release.zip $(BIN).exe

clean:
	rm *.o $(BIN).exe release.zip *.gch
