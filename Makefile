.PHONY = debug test bench clean
CPPFLAGS = -std=c++17 -I include -Werror -Wall -Wextra -pedantic -O

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
