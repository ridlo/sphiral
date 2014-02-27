PROGRAM = sphiral
PROGSRC = main.c particle.c problem.c output.c tools.c integrator.c kernel.c force.c 
OBJECTS = $(PROGSRC:%.c=%.o)
CC = gcc
CLIBS = -lm -std=c99

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -f *.o *~ sphiral
