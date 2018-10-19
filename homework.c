#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<limits.h>
#include<assert.h>
#include"list.h"


struct Linked_list {

	char str[500] ;
	struct list_head list;
};

int main()
{

	LIST_HEAD(head); // Create the list head.
	struct Linked_list *link_list ;
	struct list_head *list_head_iterator, *list_head_temp;
	char str[128], *str_token, emptyStr = '\0';
	char *saveptr1, *endptr;
	FILE *fptr ;

	// Check file exist.
	if((fptr = fopen("input.txt", "r")) == NULL){
		printf("open_file_error");
		exit(1);
	}

	errno = 0 ; /* To distinguish success/failure after call */
	while(fgets(str, 128, fptr) != NULL) {	// Scan the intput file

		str_token = strtok_r(str, " \n", &saveptr1); // Split the string.

		if(str_token == NULL) // Check pch is NULL or not.
			str_token = &emptyStr ; // emptyStr = '\0'

		if(!strcmp(str_token, "add")) { // Add
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the string.
			link_list = malloc(sizeof(struct Linked_list));
			if(link_list) { // tmp value not NULL
				strncpy(link_list->str, str_token, strlen(str_token) + 1); // Convert char *pch to char str[]

				//tmp -> str = pch ;
				list_add_tail(&link_list->list, &head);
			} else { // tmp value is NULL.
				printf("malloc error \n");
				exit(1);

			}
		} else if(!strcmp(str_token, "del")) {
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str.

			list_for_each_safe(list_head_iterator, list_head_temp , &head) {

				//number = strtol(pch, &endptr, 10);

				/* Check for various possible errors */
				/*
				if ((errno == ERANGE && (number == LONG_MAX || number == LONG_MIN))
				  || (errno != 0 && number == 0)) {
				perror("strtol");
				exit(EXIT_FAILURE);
				}

				if (endptr == pch) {
				fprintf(stderr, "No digits were found\n");
				exit(EXIT_FAILURE);
				}
				*/
				link_list = list_entry(list_head_iterator, struct Linked_list, list);

				// Find the string which wants to delete.
				if(!strcmp(link_list->str, str_token)) {
					list_del(&link_list->list);
					free(link_list); // Free the memory
				}
			}
		} else {
			//printf("------ \n");
			//printf("%s \n",pch);
		}
	}


	fclose(fptr); // Close file.

	printf("Print result : \n");
	list_for_each(list_head_iterator, &head) {

		link_list = list_entry(list_head_iterator, struct Linked_list, list);
		printf("%s \n", link_list->str);
		free(link_list); // Free the memory.
	}



	return 0 ;

}
