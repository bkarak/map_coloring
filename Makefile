# The 2002 sources built by a current compiler. Nothing in src/ was changed to
# make this work: cc -O2 takes them as they are, and the only warnings are the
# three `#endif _NAME_` include guards, which were legal enough for Dev-C++.

CC      ?= cc
CFLAGS  ?= -O2
LDLIBS  ?= -lm

SRC = src/main.c src/calc.c src/vector.c src/vector_solutions.c
BIN = mapColoring

$(BIN): $(SRC) src/calc.h src/vector.h src/vector_solutions.h
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDLIBS)

# Render every map under maps/ with Graphviz. Needs dot and perl.
graphs:
	$(MAKE) -C maps graphs

# maps/Makefile's own clean target says `rm -f maps/*.gif` from inside maps/,
# so it deletes nothing; it is left as it was written and the sweep is here.
clean:
	rm -f $(BIN) maps/*.dot maps/*.gif

.PHONY: graphs clean
