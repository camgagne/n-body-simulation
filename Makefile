CC = g++
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
OBJS = Universe.o CelestialBody.o
CFLAGS = -Wall -Werror -pedantic -g --std=c++20

all: NBody.a NBody test

NBody: $(OBJS) main.o
	$(CC) $(CFLAGS) -o NBody $(OBJS) main.o $(LIB)

NBody.a: $(OBJS)
	ar rcs NBody.a $(OBJS)

main.o: main.cpp CelestialBody.hpp Universe.hpp
	$(CC) $(CFLAGS) -c main.cpp

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c Universe.cpp -o Universe.o

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp -o CelestialBody.o

test.o: test.cpp CelestialBody.hpp Universe.hpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o

test: test.o Universe.o CelestialBody.o
	$(CC) $(CFLAGS) -o test test.o Universe.o CelestialBody.o $(LIB)

clean:
	rm -f *.o NBody test NBody.a

lint:
	cpplint *.cpp *.hpp
