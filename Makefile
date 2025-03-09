all:
	gcc -o fishtank fishtank.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 goldfish.c plant.c coral.c dory.c

clean:
	rm -rf fishtank