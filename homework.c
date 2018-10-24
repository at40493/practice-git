#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<limits.h>
#include<assert.h>
#include"list.h"


struct Linked_list {

	char *str ;
	struct list_head list;
};

int main(int argc, char *argv[])
{

	LIST_HEAD(head); // Create the list head.
	struct Linked_list *link_list, *link_list_match ;
	struct list_head *list_head_iterator, *list_head_temp;
	char *str = NULL, *str_token = NULL, *str_token_next = NULL, emptyStr = '\0';
	char *saveptr1, *endptr;
	size_t len = 0;
	ssize_t read;
	FILE *fptr;
	/*
	if(argc == 2) {
		fprintf(stderr, "Usage: ./hellomake  [Input file name]\n");
		exit(1);
	}
	//fprintf(stderr,"Input file : %d\n",argc);
	fprintf(stderr, "Input file : %s\n", argv[1]);
	// Check file exist.
	if((fptr = fopen(argv[1], "r")) == NULL) {
		printf("Open_file_error\n");
		exit(1);
	}
	*/
	errno = 0 ; /* To distinguish success/failure after call */
	while((read = getline(&str, &len, stdin)) != -1) {	// Scan the intput file
		//fprintf(stderr, "Retrieved line of length %zu :\n", read);
		str_token = strtok_r(str, " \n", &saveptr1); // Split the string.

		if(str_token == NULL) // Check str_token is NULL or not.
			str_token = &emptyStr ; // emptyStr = '\0'

		if(!strcmp(str_token, "add")) { // Add
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the string.
			if(str_token != NULL) {
				link_list = malloc(sizeof(struct Linked_list));
				link_list->str = malloc((strlen(str_token) + 1) * sizeof(char *));
				if(link_list && link_list->str) { // link list not NULL
					strcpy(link_list->str, str_token); // Convert char *str_token to char str[]

					//tmp -> str = pch ;
					list_add_tail(&link_list->list, &head);
				} else { // link list is NULL.
					printf("malloc error \n");
					exit(1);

				}
			}
		} else if(!strcmp(str_token, "del")) {
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str.
			if(str_token != NULL) {
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
						free(link_list->str); // Free the memory.
						free(link_list); // Free the memory

						break;
					}
				}
			}
		} else if(!strcmp(str_token, "insert")) { //insert <match> <str>: 在找到的match前，加入str
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str. <match>
			str_token_next = strtok_r(NULL, " \n", &saveptr1); // Split the str. <str>

			if(str_token != NULL && str_token_next != NULL) { // Check the insert format
				list_for_each(list_head_iterator, &head) {

					link_list_match = list_entry(list_head_iterator, struct Linked_list, list);

					if(!strcmp(str_token, link_list_match->str)) {
						//str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str.

						link_list = malloc(sizeof(struct Linked_list));
						link_list->str = malloc((strlen(str_token_next) + 1) * sizeof(char *));
						if(link_list && link_list->str) { // link_list not NULL
							strcpy(link_list->str, str_token_next); // Convert char *str_token to char str[]

							list_add_tail(&link_list->list, &link_list_match->list); // list_add_tail(new,head)
							break;
						} else { // link_list is NULL.
							printf("malloc error \n");
							exit(1);

						}
					}

				}
			}
		} else if(!strcmp(str_token, "append")) {  //append <match> <str>: 找到的match後，加入str
			str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str <match>
			str_token_next = strtok_r(NULL, " \n", &saveptr1); // Split the str <str>

			if(str_token != NULL && str_token_next != NULL) { // Check the append format

				//fprintf(stderr, "1 str_token = %d\n", sizeof(str));
				//fprintf(stderr, "1 str_token = %s\n", str_token_next);

				list_for_each(list_head_iterator, &head) {

					link_list_match = list_entry(list_head_iterator, struct Linked_list, list);

					if(!strcmp(str_token, link_list_match->str)) { // Find the match.
						//str_token = strtok_r(NULL, " \n", &saveptr1); // Split the str.
						//fprintf(stderr, "2 str_token = %08x\n", str_token);
						//fprintf(stderr, "2 str_token = %s\n", str_token);

						link_list = malloc(sizeof(struct Linked_list));
						link_list->str = malloc((strlen(str_token_next) + 1) * sizeof(char *));

						if(link_list && link_list->str) { // link_list not NULL
							//printf("%s \n",str_token);
							//printf("%d \n",strlen(str_token)+1);
							// 重設所有字元為空字元
							//memset(link_list->str, '\0', sizeof(link_list->str));
							strcpy(link_list->str, str_token_next); // Convert char *str_token to char str[]
							//strncat(emptyStr, link_list->str, strlen((link_list->str)-1));
							//link_list_match = list_next_entry(link_list_match, list);
							list_add(&link_list->list, &link_list_match->list); // list_add(new,head)
							break;
						} else { // link_list is NULL.
							printf("malloc error \n");
							exit(1);

						}
					}

				}
			}
		}
	}



	//fclose(fptr); // Close file.
	free(str); // Free the memory.

	// Check file exist.
	//if((fptr = fopen("output.txt", "w")) == NULL) {
	//	fprintf(stderr, "open_file_error\n");
	//	exit(1);
	//}

	fprintf(stderr, "Output file : output.txt \n");
	list_for_each(list_head_iterator, &head) {

		link_list = list_entry(list_head_iterator, struct Linked_list, list);
		fprintf(stdout, "%s\n", link_list->str);
		//fwrite(link_list->str,sizeof(link_list->str),1,fptr);
		free(link_list->str); // Free the memory.
		free(link_list); // Free the memory.

	}

	//fclose(fptr);

	return 0 ;

}
