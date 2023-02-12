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
.PHONY: check clang cppcheck leaks 
check: clang cppcheck leaks

clang:
	@echo "************************************************************"
	@echo "******************** CLANG-FORMAT **************************"
	@echo "************************************************************"
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -i *.c
	clang-format -n *.c

cppcheck:
	@echo "************************************************************"
	@echo "********************** CPPCHECK ****************************"
	@echo "************************************************************"
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	@echo "************************************************************"
	@echo "************************ LEAKS *****************************"
	@echo "************************************************************"
	leaks -atExit -- ../build/graph < data
