.PHONY = test clean debug
CXXFLAGS = -std=c++11 -I include -Werror -Wall -Wextra -pedantic

all: tests/main

tests/main: $(wildcard tests/*.cpp)

debug: CXXFLAGS += -g
debug: all

test: tests/main
	@./tests/main

clean:
	rm tests/main
