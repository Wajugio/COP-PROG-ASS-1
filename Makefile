CC = gcc
CFLAGS = -Wall -Wextra -g 

TARGET = shell
SRCS = shell.c
OBJS = $(SRCS:.c=.o)
HEADERS = shell.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

debug: CFLAGS += -DDEBUG
debug: clean all

run: all
	./$(TARGET)

.PHONY: all clean debug run
