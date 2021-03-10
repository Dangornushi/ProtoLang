run:
	g++ -c src/comp.cpp -std=c++14
	g++ -c src/run.cpp -std=c++14
	g++ -c src/define.cpp -std=c++14
	g++ comp.o define.o -o bin/comp
	g++ run.o define.o -o bin/run
	rm *.o

run.cpp:
	g++ -c src/run.cpp -std=c++14
	g++ -c src/define.cpp -std=c++14
	g++ run.o define.o -o bin/run
	rm *o

all:
	g++ -c src/comp.cpp -std=c++14
	g++ -c src/define.cpp -std=c++14
	g++ -c src/run.cpp -std=c++14
	g++ comp.o define.o -o bin/comp
	g++ run.o define.o -o bin/run
	g++ -o bin/proto src/proto.cpp
	rm *.o
