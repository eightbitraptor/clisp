cc=clang

src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -std=c99 -Wall
DEBUGFLAGS = -ggdb3
OPTFLAGS = -O0
LDFLAGS = -lreadline

clisp: $(obj)
	$(cc) $(CFLAGS) $(DEBUGFLAGS) $(OPTFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) clisp
