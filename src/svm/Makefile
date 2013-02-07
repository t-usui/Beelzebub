CXX = g++
CFLAGS = -Wall -O3
OBJS = main.o svc.o svm.o

classifier: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS)

.cc.o:
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o classifier

