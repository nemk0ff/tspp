.PHONY: all clean run runtest

all: calc test leak_test

calc: main.o calc.o ExpressionParser.o
	g++ main.o calc.o ExpressionParser.o -o calc

main.o: main.cpp
	g++ -c main.cpp

calc.o: calc.cpp
	g++ -c calc.cpp

ExpressionParser.o: ExpressionParser.cpp
	g++ -c ExpressionParser.cpp

test: test.cpp calc.cpp
	g++ test.cpp calc.cpp ExpressionParser.cpp -o test

leak_test: test.cpp calc.cpp
	g++ -g test.cpp calc.cpp ExpressionParser.cpp -o leak_test -fsanitize=address

runtest: test
	./test

run: calc
	./calc

clean:	
	rm -rf *.o *. exe calc leak_test test
