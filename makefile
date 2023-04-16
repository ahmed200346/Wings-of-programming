prog:enigme.o main.o
	gcc enigme.c main.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -o prog
enigme.o:enigme.c
	gcc -c enigme.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	gcc -c main.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g	
