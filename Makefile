SRS = homework.c operator.c list.h operator.h
INPUT = cat input.txt | ./hellomake

all: style test valgrind
 
style:  
	astyle --style=linux --indent=tab --pad-oper --unpad-paren homework.c operator.c
	
hellomake: $(SRS)
	gcc -o hellomake homework.c operator.c

test : hellomake
	$(INPUT) > output.txt

valgrind: 
	valgrind --leak-check=full $(INPUT) > output.txt

