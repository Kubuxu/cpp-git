CXX=g++
RM=rm -f
CXXFLAGS=-g -std=c++11 -Wall -pedantic
LDFLAGS=-g 
LDLIBS=-pthread

SRCS=pid.cc test.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: test

test: test.o pid.o
	$(CXX) $(LDFLAGS) -o test test.o pid.o $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)
	$(RM) test

dist-clean: clean
	$(RM) *~ .depend

include .depend
