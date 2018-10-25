SRS = homework.c list.h
INPUT = cat input.txt | ./hellomake

all: style test valgrind
 
style:  
	astyle --style=linux --indent=tab --pad-oper --unpad-paren homework.c
	
hellomake: $(SRS)
	gcc -o hellomake homework.c

test : hellomake
	$(INPUT) > output.txt

valgrind: 
	valgrind --leak-check=full $(INPUT) > output.txt

