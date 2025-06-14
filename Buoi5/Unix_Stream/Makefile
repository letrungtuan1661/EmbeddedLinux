SRCS = $(wildcard *.c)
EXES = $(SRCS:%.c=%)

.PHONY: all clean

all: $(EXES)

%: %.c
	gcc $^ -o $@ 

clean:
	rm -f $(EXES) sock_stream