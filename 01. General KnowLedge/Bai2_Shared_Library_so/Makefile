CC = gcc
CFLAGS = -Wall -fPIC
TARGET = main
LIB = libmylib.so

all: $(TARGET)

mylib.o: mylib.c
	$(CC) $(CFLAGS) -c mylib.c -o mylib.o

$(LIB): mylib.o
	$(CC) -shared -o $(LIB) mylib.o

$(TARGET): main.c $(LIB)
	$(CC) main.c -L. -lmylib -o $(TARGET) -Wl,-rpath=.

clean:
	rm -f *.o *.so $(TARGET)
