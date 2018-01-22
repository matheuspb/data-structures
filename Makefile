.PHONY = debug test bench clean
CPPFLAGS = -std=c++11 -I include -Werror -Wall -Wextra -pedantic -O

all: tests/main

tests/main: $(wildcard tests/*.cpp)

debug: CPPFLAGS += -g
debug: all

test: debug
	valgrind ./tests/main

bench: all
	sh -c "time ./tests/main"

docs: Doxyfile $(wildcard include/*.h tests/*.cpp tests/*.h)
	doxygen Doxyfile

floyd.pdf: floyd.tex
	pdflatex floyd.tex -o floyd.pdf
	rm floyd.aux floyd.log

clean:
	@rm -f tests/main floyd.pdf
	@rm -rf docs/
