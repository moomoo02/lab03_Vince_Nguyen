# CXXFLAGS=-g -std=c++11 -Wall -Werror -Wconversion -Wshadow -pedantic -I .
CXXFLAGS=-g -std=c++11 -Wall -Wconversion -Wshadow -pedantic -I .

test: test.cpp list.o
	${CXX} ${CXXFLAGS} -o $@ $^ -lgtest -lgtest_main -lpthread

list.o: list.cpp list.hpp

clean:
	rm -f test list.o
