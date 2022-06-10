CC=gcc
OBJS=find.o

find: test_project.sh ${OBJS}
	${CC} ${OBJS} -o $@
	bash $< >> output.txt

%.o: %.c
	${CC} -c $^

clean:
	rm -rf *.o find output.txt
