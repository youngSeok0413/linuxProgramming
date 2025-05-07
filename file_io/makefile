CC = gcc
CFLAGS = -Wall -O2
OBJS = main.o
TARGET = $(OBJS:.o=)

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean : 
	rm -rf main $(OBJS)
