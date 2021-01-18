CXXFLAGS = -Wall -g

PROGS = tests

all: $(PROGS)

tests: tests.o Graphe.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

tests.o: tests.cpp Graphe.hpp
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS)

clean:
	-rm -r $(PROGS) *.o
