.PHONY = test clean
CPPFLAGS = -std=c++11 -I include -Werror -Wall -Wextra -pedantic

all: tests/main

tests/main: $(tests/main.cpp)

test: tests/main
	@./tests/main

clean:
	rm tests/main
