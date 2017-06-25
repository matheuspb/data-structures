.PHONY = test clean debug
CPPFLAGS = -std=c++11 -I include -Werror -Wall -Wextra -pedantic

all: tests/main

tests/main: $(wildcard tests/*.cpp)

debug: CPPFLAGS += -g
debug: all

test: debug
	valgrind ./tests/main

clean:
	rm tests/main
