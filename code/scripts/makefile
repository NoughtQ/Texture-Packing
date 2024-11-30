CXX = g++
CFLAGS = -g -Wall -Werror
DEBUGGER = gdb

test: main.o func.o generate.o
	$(CXX) -o test main.o func.o generate.o

main.o : main.cpp header.h
	$(CXX) -c main.cpp -o main.o

func.o : func.cpp header.h
	$(CXX) -c func.cpp -o func.o

generate.o : generate.cpp header.h
	$(CXX) -c generate.cpp -o generate.o

clean:
	rm -f test main.o func.o generate.o