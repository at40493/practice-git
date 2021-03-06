#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"


int main(int argc, char *argv[])
{
	struct words words;
	int ret = 0;
	char *str = NULL, *str_token_operator, *str_token_match, *str_token_str, *str_token_next;
	size_t len = 0;

	if(words_init(&words) != 0) {// Create head.
		fprintf(stderr, "Initial failed\n");
		ret = -1;
		goto exit;
	}

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
			if(words_add(&words, str_token_str) != 0) { // Add failed
				fprintf(stderr, "Add failed\n");
				ret = -1;
				goto exit;
			}

		} else if(strcmp(str_token_operator, "del") == 0) {
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str.
			if(str_token_str == NULL) {
				//Incorrect del format
				fprintf(stderr, "Incorrect del format\n");
				continue;
			}

			if(words_del(&words, str_token_str) != 0) { // Del failed
				fprintf(stderr, "Del failed\n");
				ret = -1;
				goto exit;
			}

		} else if(strcmp(str_token_operator, "insert") == 0) { //insert <match> <str>: 在找到的match前，加入str
			str_token_match = strtok_r(NULL, " \n", &str_token_next); // Split the str. <match>
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str. <str>

			if(str_token_match == NULL || str_token_str == NULL) { // Check the insert format
				//Incorrect insert format
				fprintf(stderr, "Incorrect insert format\n");
				continue;
			}

			if(words_insert(&words, str_token_str, str_token_match) != 0) { // Insert failed.
				fprintf(stderr, "Insert failed\n");
				ret = -1; //
				goto exit;
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

			if(words_append(&words, str_token_str, str_token_match) != 0) { // Append failed.
				fprintf(stderr, "Append failed\n");
				ret = -1;
				goto exit;
			}
		}
	}

	//fprintf(stderr, "Output file : output.txt \n");
	if(words_print(&words) != 0) { // Print the result.
		ret = -1;
		goto exit;
	}
exit:
	//CLEANUP
	if(words_deinit(&words) != 0) {// Words clean up
		fprintf(stderr, "Clean up failed\n");
		ret = -1;
	}
	if(str != NULL) // Str not NULL
		free(str);
	return ret;
}


