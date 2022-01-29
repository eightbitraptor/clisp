cc=clang

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lreadline

clisp: $(obj)
	$(cc) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) clisp
