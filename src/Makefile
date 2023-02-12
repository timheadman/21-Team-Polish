## Makefile by phyliscr
GCC = gcc -std=c11 -Wall -Werror -Wextra

.PHONY: clean all uninstall rebuild
all: graph

clean:
	rm *.o

uninstall:
	rm ../build/graph

rebuild: clean uninstall all

graph:
	$(GCC) graph.c stack.c dj.c -o ../build/graph

## Check Block
.PHONY: check_all clang cppcheck leaks 
check_all: clang cppcheck leaks

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -i *.c
	clang-format -n *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	leaks -atExit -- ../build/graph < data
