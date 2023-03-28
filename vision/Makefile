CC = g++
CFLAGS = -g -Wall

EXEC = acquisition

OPENCV = -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -I/usr/include/opencv4
LIBS = $(OPENCV)

$(EXEC): acquisition.o  main.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o acquisition.o $(LIBS)


main.o: acquisition.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp $(LIBS)

acquisition.o: acquisition.h acquisition.cpp
	$(CC) $(CFLAGS) -c acquisition.cpp $(LIBS)


clean:
	rm *.o $(EXEC)
