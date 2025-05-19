.PHONY: all clean run runtest

GTEST_INCLUDE = googletest/googletest/include
GTEST_LIB_PATH = googletest/build/lib
GTEST_LFLAGS = -lgtest -lpthread -lgtest_main

all: calc test leak_test

calc: main.o math.o ExpressionParser.o
	g++ main.o math.o ExpressionParser.o -o calc

main.o: main.cpp
	g++ -c main.cpp

math.o: math.cpp
	g++ -c math.cpp

ExpressionParser.o: ExpressionParser.cpp
	g++ -c ExpressionParser.cpp

test: test.cpp math.o ExpressionParser.o
	g++ test.cpp math.o ExpressionParser.o -o test -I$(GTEST_INCLUDE) -L$(GTEST_LIB_PATH) $(GTEST_LFLAGS)

leak_test: test.cpp math.o ExpressionParser.o
	g++ -g test.cpp math.o ExpressionParser.o -o leak_test -fsanitize=address -I$(GTEST_INCLUDE) -L$(GTEST_LIB_PATH) $(GTEST_LFLAGS)

runtest: test
	./test

run: calc
	./calc

clean:
	rm -rf *.o *. exe calc leak_test test
