all: slime

slime: main.o Image.o Slime_Shader.o
	g++ main.o Image.o Slime_Shader.o -o slime

main.o: main.cpp Slime_Shader.h Image.h Makefile
	g++ -std=c++11 -O2 -Wall -Wextra -c main.cpp -o main.o

Image.o: Image.cpp Image.h Makefile
	g++ -std=c++11 -O2 -Wall -Wextra -c Image.cpp -o Image.o

Slime_Shader.o: Slime_Shader.cpp Slime_Shader.h Image.h Makefile
	g++ -std=c++11 -O2 -Wall -Wextra -c Slime_Shader.cpp -o Slime_Shader.o

.PHONY: all clean
clean:
	rm -f main.o Image.o Slime_Shader.o slime
