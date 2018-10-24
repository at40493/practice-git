# practice-git


Makefile - Use make command to makefile.(Input: input.txt, Output: output.txt)
homework.c - Main program, use stdin to input data, and it have add, 
			 insert, append and del option, print the output result to stdout.
list.h - The <linux/list.h> header v4.18.14.

Usage:
	
	cat <input file> | ./<program name> > <output file>

Input file command:

    add <str>:把str加到link list的尾巴
    insert <match> <str>: 在找到的match前，加入str
    append <match> <str>: 找到的match後，加入str
	del <str>: 在link list中，找到str，並刪除
