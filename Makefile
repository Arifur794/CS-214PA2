COMPILER = gcc
CCFLAGS  = -Wall
all: sl

sl: main.o libsl.a
	$(COMPILER) $(CCFLAGS) -o sl main.o libsl.a
libsl.a: sorted-list.o
	ar rvs libsl.a sorted-list.o
main.o: main.c sorted-list.h
	$(COMPILER) $(CCFLAGS) -c main.c
sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILER) $(CCFLAGS) -c sorted-list.c

clean:
	rm -f s1
	rm -f *.o