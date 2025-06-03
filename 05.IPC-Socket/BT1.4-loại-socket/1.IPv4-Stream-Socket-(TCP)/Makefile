CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TCP_SERVER = server
TCP_CLIENT = client

TCP_SERVER_SRC = Server.c
TCP_CLIENT_SRC = Client.c

.PHONY: all clean

all: $(TCP_SERVER) $(TCP_CLIENT)

$(TCP_SERVER): $(TCP_SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(TCP_CLIENT): $(TCP_CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TCP_SERVER) $(TCP_CLIENT)
