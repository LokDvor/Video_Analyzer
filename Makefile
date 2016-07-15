CC              := g++
CFLAGS          := -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS         := 
LIBRARIES       := -lopencv_core -lopencv_imgproc -lopencv_highgui -std=gnu++11

.PHONY: all clean

all: v_frame

v_frame: 
	$(CC) $(CFLAGS) -o v_frame v_frame.cpp $(LIBRARIES)
        
clean:
	rm -f *.o
