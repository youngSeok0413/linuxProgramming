CC = gcc
CFLAGS = -Wall -O2

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
BINS = $(OBJS:.o=)

# 파일별 개별 CFLAGS 설정
CFLAGS_mutex.o = -pthread
CFLAGS_thread.o = -pthread

all: $(BINS)

%: %.o
	$(CC) $(CFLAGS) $(CFLAGS_$<) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_$@) -c $< -o $@

clean:
	rm -f $(OBJS) $(BINS)

.PHONY: clean
