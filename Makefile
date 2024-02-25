#!/usr/bin/make

CXX		= g++
CXXFLAGS	= -Wall -Wextra -std=c++2a
LDFLAGS		= -shared

SRCDIR	= src
OBJDIR	= obj

LIBRARY	= libDetectorMapping.so
LIBDIR	= lib

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard include/*.h)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(LIBDIR)/$(LIBRARY): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

clean:
	@rm -rf $(OBJDIR) $(LIBDIR)

test: $(LIBDIR)/$(LIBRARY) test.cpp
	$(CXX) $(CXXFLAGS) -o $@ test.cpp -L$(LIBDIR) -lDetectorMapping

.PHONY: clean test
