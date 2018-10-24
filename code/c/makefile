run: main
	./main

main: main.o
	g++ -o main main.o -l fftw3

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f main *.o
