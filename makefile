#Makefile

BOOST_PATH = /usr/local/boost_1_67_0

main: Tarjan.o Nuutila.o pearce.o testing.o main.o
	g++ -I BOOST_PATH -o main Tarjan.o Nuutila.o pearce.o testing.o main.o

Tarjan.o: Tarjan.cpp tarjan.h
	g++ -I BOOST_PATH -c Tarjan.cpp

Nuutila.o: Nuutila.cpp nuutila.h
	g++ -I BOOST_PATH -c Nuutila.cpp

pearce.o: pearce.cpp pearce.h
	g++ -I BOOST_PATH -c pearce.cpp

testing.o: testing.cpp testing.h
	g++ -I BOOST_PATH -c testing.cpp

main.o: main.cpp
	g++ -I BOOST_PATH -c main.cpp
