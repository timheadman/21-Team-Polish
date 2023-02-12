.PHONY: clean all
all: graph

clean:
	rm *.o

uninstall:
	rm ../build/graph

rebuild: clean uninstall all

graph:
	gcc graph.c stack.c dj.c -o ../build/graph
