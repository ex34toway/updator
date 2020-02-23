CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 -I/mnt/poco-poco-1.9.4-release/Foundation/include -I/mnt/poco-poco-1.9.4-release/Util/include -I../include
LDFLAGS=-g -L/mnt/poco-poco-1.9.4-release/lib/Linux/x86_64
LDLIBS=-lPocoFoundation -lPocoUtil -lPocoXML -lPocoJSON

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: updator

updator: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o updator

clean: 
	$(RM) $(OBJS) updator updator.log