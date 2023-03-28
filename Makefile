CPP=g++

CPPFLAGS=-Wall
LIBS= -lwiringPi
EXES=main
all:$(EXES)

#cm: control_m.o Controle/control_m.hpp config/config.hpp
#	$(CPP) $(CPPFLAGS) control_m.o -o cm $(LIBS)
#control_m.o: Controle/control_m.cpp Controle/control_m.hpp config/config.hpp
#	$(CPP) $(CPPFLAGS) -c Controle/control_m.cpp $(LIBS)

main: main.o codeur.o control_m.o Controle/control_m.cpp Controle/control_m.hpp Codeur/codeur.hpp config/config.hpp pid/pid.h
	$(CPP) $(CPPFLAGS) main.o codeur.o control_m.o -o main $(LIBS)
main.o: main.cpp config/config.hpp Codeur/codeur.hpp Controle/control_m.hpp pid/pid.h
	$(CPP) $(CPPFLAGS) -c main.cpp $(LIBS)
codeur.o: Codeur/codeur.cpp config/config.hpp Codeur/codeur.hpp Controle/control_m.hpp pid/pid.h
	$(CPP) $(CPPFLAGS) -c Codeur/codeur.cpp $(LIBS)
control_m.o: Controle/control_m.cpp Controle/control_m.hpp config/config.hpp pid/pid.h
	$(CPP) $(CPPFLAGS) -c Controle/control_m.cpp $(LIBS)
clean:
	rm -f *.o $(EXES)
