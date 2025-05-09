CC = gcc
AR = ar
CFLAGS = -Wall -c
TARGET = main
LIB = libmylib.a

all: $(TARGET)

mylib.o: mylib.c
	$(CC) $(CFLAGS) mylib.c -o mylib.o

$(LIB): mylib.o
	$(AR) rcs $(LIB) mylib.o

$(TARGET): main.c $(LIB)
	$(CC) main.c -L. -lmylib -o $(TARGET)

clean:
	rm -f *.o *.a $(TARGET)
