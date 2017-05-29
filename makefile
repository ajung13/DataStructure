CC = gcc
CFAGS = -W -Wall
TARGET = testlib
OBJECTS = list.o bitmap.o hash.o main.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAS) -o $@ $^

clean :
	rm *.o testlib
