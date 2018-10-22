CC=gcc
CFLAGS=-std=c99 -pedantic -D _POSIX_C_SOURCE=200809L
DEPS=types.h
OBJ = benchmark.o types.o
LIBS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

benchmark: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm $(OBJ)
	-rm benchmark
