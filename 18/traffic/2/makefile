main:main.o Graph.o view.o 
	g++ -o main main.o Graph.o view.o 
main.o:main.cpp view.h Graph.h
	g++ -c main.cpp
Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp
view.o:view.cpp view.h
	g++ -c view.cpp
clean:
	rm main *.o
