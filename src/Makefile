PROGRAM = sphiral
PROGSRC = main.c particle.c problem.c output.c tools.c integrator.c
OBJECTS = $(PROGSRC:%.c=%.o)
CC = gcc
CLIBS = -lm

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -f *.o *~ sphiral
