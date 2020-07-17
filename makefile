all:
	g++ *.cpp -static -Wall -pedantic -O3

debug:
	g++ *.cpp -g

teste:
	./a.out < 2.meio