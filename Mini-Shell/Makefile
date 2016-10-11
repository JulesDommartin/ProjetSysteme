compilo = gcc -g -Wall -W -Werror -Os -std=gnu11

executables = mon_shell

objets = $(patsubst %.c,%.o, $(wildcard *.c))

default: $(executables)

$(executables): %: $(objets)
	$(compilo) $^ -o $@

%.o: %.c $(wildcard *.h) Makefile
	$(compilo) -c $<

menage:
	rm -f *~ $(executables) *.o a.out core
