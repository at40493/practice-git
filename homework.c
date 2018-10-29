#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "operator.h"


int main(int argc, char *argv[])
{

	LIST_HEAD(head); // Create the list head.
	char *str = NULL, *str_token_operator, *str_token_match, *str_token_str, *str_token_next;
	size_t len = 0;

	while(getline(&str, &len, stdin) != -1) {	// Scan the intput file
		str_token_operator = strtok_r(str, " \n", &str_token_next); // Split the string.

		if(str_token_operator == NULL) // Check str_token is NULL or not.
			continue; // Do next line.

		if(strcmp(str_token_operator, "add") == 0) { // Add
			//add <str>:把str加到link list的尾巴
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the string.
			if(str_token_str == NULL) {
				//Incorrect add format
				fprintf(stderr, "Incorrect add format\n");
				continue;
			}
			if(!add_word(str_token_str, &head)) { // Add failed
				free_data(str, &head);
				return 1;
			}

		} else if(strcmp(str_token_operator, "del") == 0) {
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str.
			if(str_token_str == NULL) {
				//Incorrect del format
				fprintf(stderr, "Incorrect del format\n");
				continue;
			}

			del_word(str_token_str, &head);

		} else if(strcmp(str_token_operator, "insert") == 0) { //insert <match> <str>: 在找到的match前，加入str
			str_token_match = strtok_r(NULL, " \n", &str_token_next); // Split the str. <match>
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str. <str>

			if(str_token_match == NULL || str_token_str == NULL) { // Check the insert format
				//Incorrect insert format
				fprintf(stderr, "Incorrect insert format\n");
				continue;
			}

			if(!insert_word(str_token_match, str_token_str, &head)) { // Insert failed.
				free_data(str, &head);
				return 1;
			}

		} else if(strcmp(str_token_operator, "append") == 0) {
			//append <match> <str>: 找到的match後，加入str
			str_token_match = strtok_r(NULL, " \n", &str_token_next); // Split the str <match>
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str <str>

			if(str_token_match == NULL || str_token_str == NULL) { // Check the append format
				//Incorrect append format
				fprintf(stderr, "Incorrect append format\n");
				continue;
			}
			//fprintf(stderr, "1 str_token = %d\n", sizeof(str));
			//fprintf(stderr, "1 str_token = %s\n", str_token_next);

			if(!append_word(str_token_match, str_token_str, &head)) { // Append failed.
				free_data(str, &head);
				return 1;
			}
		}
	}

	fprintf(stderr, "Output file : output.txt \n");
	list_print(&head); // Print the result.
	free_data(str, &head);

	return 0 ;

}

