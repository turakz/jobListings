#compiler used
CXX = g++
#language version
CV = -std=c++14 
#dependencies
FILES = listings.h listings.cpp main.cpp

#flags
FLAGS = -ggdb -Wall
#external libraries
LIBS = -lncurses -I /usr/lib/boost_1_65_1/
#executable name
OUT_EXE = listings

#target definition
listings: $(FILES)
		$(CXX) $(CV) $(FLAGS) -o $(OUT_EXE) $(FILES) $(LIBS)

clean: 
	rm .*.* | rm .*.*~ | rm *.*~ 
