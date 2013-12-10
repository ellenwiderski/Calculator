CXX	= g++
DEBUG    = -g
CXXFLAGS = $(shell fltk-config --cxxflags ) -std=c++11 -I.
LDFLAGS  = $(shell fltk-config --ldflags )
LDSTATIC = $(shell fltk-config --ldstaticflags )
LINK     = g++-4.8


.SUFFIXES: .o .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

calculator: gui.cpp operandButton.o operatorButton.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) gui.cpp operandButton.o operatorButton.o -o calculator