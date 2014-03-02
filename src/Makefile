PROGRAM = sphiral
PROGSRC = main.c particle.c problem.c output.c tools.c integrator.c boundaries.c kernel.c gravityinteract.c eos.c force.c 
OBJECTS = $(PROGSRC:%.c=%.o)
CC = gcc -std=c99 -O3 -Wpointer-arith -Wall -g -lm

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -f *.o *~ sphiral
