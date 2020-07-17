all:
	g++ *.cpp -static -Wall -Pedantic -O3

debug:
	g++ *.cpp -g

teste:
	./a.out < 2.meio