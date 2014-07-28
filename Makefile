CXX	= g++
OBJS	= main.o analyze.o disasm.o
CFLAGS	= -Wall -O2 -ludis86
DEBUG	= -O0 -g
VPATH	= src/

INSTALL	= install -c
prefix	= /usr/local
bindir	= $(prefix)/bin

beelzebub: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CFLAGS) $(DEBUG)

.cc.o:
	$(CXX) -c $< $(CFLAGS) $(DEBUG)

.PHONY: install clean
install: beelzebub
	$(INSTALL) beelzebub $(bindir)/beelzebub

clean:
	rm -f beelzebub *.o
