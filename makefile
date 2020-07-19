all:
	g++ *.cpp -static -Wall -pedantic -O3

debug:
	g++ *.cpp -g

teste:
	./a.out < 2.meio

t1:
	./a.out < teste.txt
t2:
	./a.out < teste2.txt
t3:
	./a.out < teste3.txt