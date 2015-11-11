OBJ=addqueue showqueue rmqueue
CXX=clang++
STDFLAG=-std=c++11
CXXFLAGS=$(STDFLAG) -lboost_system -lboost_filesystem

build: queue_commands 

queue_commands: $(OBJ)

addqueue: addqueue.o spool_helper.o 
	$(CXX) $(CXXFLAGS) -o $@ addqueue.o spool_helper.o

showqueue: showqueue.o spool_helper.o 
	$(CXX) $(CXXFLAGS) -o $@ showqueue.cpp spool_helper.o

rmqueue: rmqueue.o spool_helper.o
	$(CXX) $(CXXFLAGS) -o $@ rmqueue.cpp spool_helper.o

addqueue.o: addqueue.cpp spool_helper.h
	$(CXX) $(STDFLAG) -c addqueue.cpp

showqueue.o: showqueue.cpp spool_helper.h
	$(CXX) $(STDFLAG) -c showqueue.cpp

rmqueue.o: rmqueue.cpp spool_helper.h
	$(CXX) $(STDFLAG) -c rmqueue.cpp

spool_helper.o: spool_helper.cpp spool_helper.h
	$(CXX) $(STDFLAG) -c spool_helper.cpp

test: build
	./acl_main < first_test.txt

exec: build
	./acl_main $(ARG)

clean:
	rm -f acl_main *.o *.h~ *.cpp~
