INCLUDE= -I../inc

SRC= ../src/

BASIC_ALL_OBJS := FileHandler.o Encrypter.o HiScoreTable.o
BASIC_ALL_SRCS := $(BASIC_ALL_OBJS:%.o=$(SRC)%.cpp)

BASIC_ALL_TST_HPP  := $(BASIC_ALL_OBJS:%.o=test%.hpp)
BASIC_ALL_TST_CPP  := $(BASIC_ALL_TST_HPP:%.hpp=%.cpp)

BASIC_RUNNER_EXEC := run_tests.exe
BASIC_RUNNER_SRC  := $(BASIC_RUNNER_EXEC:.exe=.cpp)


CC=g++

CXXGEN=python c:\mingw\cxxtest\bin\cxxtestgen --error-printer

##########

$(BASIC_RUNNER_EXEC): $(BASIC_RUNNER_SRC) $(BASIC_ALL_OBJS)
	$(CC) $(INCLUDE) $(BASIC_RUNNER_SRC) $(BASIC_ALL_OBJS) -std=c++0x -o $@

$(BASIC_RUNNER_SRC) : $(BASIC_ALL_TST_HPP)
	$(CXXGEN) -o $@ $(BASIC_ALL_TST_HPP)

##########

$(BASIC_ALL_OBJS): $(BASIC_ALL_SRCS)
	$(CC) $(INCLUDE) -c $(SRC)$(@:.o=.cpp) -std=c++0x -o $@

##########

basic: $(BASIC_RUNNER_EXEC)
	$(BASIC_RUNNER_EXEC)

.PHONY: clean

clean:
	del *.exe *.cpp *.o