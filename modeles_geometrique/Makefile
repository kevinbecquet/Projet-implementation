CPP = g++
LIBS = -g
Exec= mg
CPPFLAGS=-std=c++14


$(Exec) :  main.o
	$(CPP) $(CPPFLAGS) -Wall -o mg main.o $(LIBS)
l -c mgi.cpp  $(LIBS)

main.o: mgi.h mgd.h
	$(CPP) -Wall -c main.cpp
clean :
	rm -f *.o $(Exec)
