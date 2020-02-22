CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -I/mnt/poco-poco-1.9.4-release/Foundation/include -I/mnt/poco-poco-1.9.4-release/Util/include -I../include
#$(shell root-config --cflags)
# -Wall
LDFLAGS=-g -L/mnt/poco-poco-1.9.4-release/lib/Linux/x86_64 -lPocoFoundation -lPocoUtil -lPocoXML -lPocoJSON
#$(shell root-config --ldflags)
LDLIBS=
#$(shell root-config --libs)

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: updator

updator: $(OBJS)
	$(CXX) $(LDFLAGS) -o updator $(OBJS) $(LDLIBS)

clean: 
	$(RM) $(OBJS) updator updator.log