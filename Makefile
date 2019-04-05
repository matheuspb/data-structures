.PHONY = debug test bench clean
SIZE = 10000
CPPFLAGS = -std=c++17 -O
CPPFLAGS += -Werror -Wall -Wextra -pedantic
CPPFLAGS += -I include -D SIZE=$(SIZE)

all: tests/main

tests/main: tests/main.cpp

debug: CPPFLAGS += -g
debug: tests/main

test: debug
	valgrind ./tests/main

bench: tests/main
	sh -c "time ./tests/main"

docs: Doxyfile $(wildcard include/*.h tests/*.cpp tests/*.h)
	doxygen Doxyfile

floyd.pdf: floyd.tex
	pdflatex floyd.tex -o floyd.pdf

clean:
	@rm -f tests/main floyd.aux floyd.log floyd.pdf
	@rm -rf docs/
