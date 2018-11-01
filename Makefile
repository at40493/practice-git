INPUT = cat input.txt | ./homework
SRS = homework.c operator.c
OBJS = $(SRS:.c=.o)

all: style test valgrind 
 
style:  
	astyle --style=linux --indent=tab --pad-oper --unpad-paren homework.c operator.c

homework: $(OBJS)
	gcc -o $@ $^

%.o:%.c operator.h list.h list_private.h
	gcc -c $<

test : homework
	$(INPUT) | tee output.txt

valgrind: 
	valgrind --leak-check=full $(INPUT) | tee output.txt

