CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

OBJECTS = main.o httpserver.o actionhandler.o

#tcpServer3: $(OBJECTS)
#	$(CXX) $(CXXFLAGS) -o $@ $^

main: $(OBJECTS) #main.cpp tcpServer3.c
	$(CXX) $(CXXFLAGS) -o $@ $^

httpclient: httpclient.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
#	$(RM) *.o tcpServer3
	$(RM) *.o main httpclient
