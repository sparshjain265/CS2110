CC = gcc -Wall -g
OBJS = main.o graph.o queue.o

dijkstra.out : ${OBJS}
	${CC} ${OBJS} -o dijkstra.out

main.o: main.c
	${CC} -c main.c

graph.o : graph.c
	${CC} -c graph.c

queue.o : queue.c
	${CC} -c queue.c

clean:
	\rm diskstra.out *.o *.dot
