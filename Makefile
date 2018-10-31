INPUT = cat input.txt | ./hellomake

all: style test valgrind 
 
style:  
	astyle --style=linux --indent=tab --pad-oper --unpad-paren homework.c operator.c

hellomake: homework.o operator.o
	gcc -o hellomake homework.o operator.o

homework.o: homework.c operator.h 
	gcc -c homework.c

operator.o: operator.c operator.h list.h list_private.h
	gcc -c operator.c 

test : hellomake
	$(INPUT) > output.txt

valgrind: 
	valgrind --leak-check=full $(INPUT) > output.txt

