CFLAGS += -std=gnu11 -g
EXES   =  stack_main
OBJS   =  stack_main.o stack.o refcount.o

all: $(EXES)

stack_main: $(OBJS)

clean:
	rm -f $(EXES) $(OBJS)
tidy:
	rm -f $(OBJS)