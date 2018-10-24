SRS = homework.c list.h
INPUT = cat input.txt | ./hellomake

all: style test 
 
style:  
	@astyle --style=linux --indent=tab --pad-oper --unpad-paren homework.c
	
hellomake: $(SRS)
	@gcc -o hellomake.o homework.c

test : hellomake
	@$(INPUT) > output.txt

valgrind: 
	@valgrind --leak-check=full $(INPUT)

