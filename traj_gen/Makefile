CPP = g++
LIBS = -g
Exec= traj
CPPFLAGS=-std=c++14


$(Exec) :  main.o
	$(CPP) $(CPPFLAGS) -Wall -o traj main.o $(LIBS)


main.o: traj_gen.h
	$(CPP) -Wall -c main.cpp
clean :
	rm -f *.o $(Exec)
