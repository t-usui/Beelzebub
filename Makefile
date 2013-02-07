CXX		= g++
OBJS	= main.o analyze.o
CFLAGS	= -Wall -O3
DEBUG	= -g
VPATH	= src/

Beelzebub: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CFLAGS) $(DEBUG)

.cc.o:
	$(CXX) -c $< $(FLAGS) $(DEBUG)

.PHONY: clean
clean:
	rm -f Beelzebub *.o
