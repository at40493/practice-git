#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "list.h"

void freememory(char*, struct list_head*);


struct linked_list_node {
	char *str ;
	struct list_head list;
};

int main(int argc, char *argv[])
{

	LIST_HEAD(head); // Create the list head.
	struct linked_list_node *link_list_new_node, *link_list_match_node;
	struct list_head *list_head_iterator, *list_head_temp;
	char *str = NULL, *str_token_operator, *str_token_match, *str_token_str, *str_token_next;
	size_t len = 0;

	while(getline(&str, &len, stdin) != -1) {	// Scan the intput file
		str_token_operator = strtok_r(str, " \n", &str_token_next); // Split the string.

		if(str_token_operator == NULL) // Check str_token is NULL or not.
			continue ; // Do next line.

		if(strcmp(str_token_operator, "add") == 0) { // Add
			//add <str>:把str加到link list的尾巴
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the string.
			if(str_token_str == NULL) {
				//Incorrect add format
				fprintf(stderr, "Incorrect add format\n");
				continue;
			}
			link_list_new_node = malloc(sizeof(struct linked_list_node));
			if(link_list_new_node == NULL) {
				fprintf(stderr, "Malloc error from link_list_new_node \n");
				freememory(str, &head);
				return 0 ;
			}

			link_list_new_node->str = strdup(str_token_str);
			if(link_list_new_node->str == NULL) { // link list  NULL
				fprintf(stderr, "Malloc error from link_list_new_node->str \n");
				free(link_list_new_node);
				freememory(str, &head);
				return 0 ;
			}


			list_add_tail(&link_list_new_node->list, &head);


		} else if(strcmp(str_token_operator, "del") == 0) {
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str.
			if(str_token_str == NULL) {
				//Incorrect del format
				fprintf(stderr, "Incorrect del format\n");
				continue;
			}
			list_for_each_safe(list_head_iterator, list_head_temp , &head) {
				link_list_match_node = list_entry(list_head_iterator, struct linked_list_node, list);

				// Find the string which wants to delete.
				if(strcmp(link_list_match_node->str, str_token_str) == 0) {
					list_del(&link_list_match_node->list);
					free(link_list_match_node->str); // Free the memory.
					free(link_list_match_node); // Free the memory

					break;
				}
			}

		} else if(strcmp(str_token_operator, "insert") == 0) { //insert <match> <str>: 在找到的match前，加入str
			str_token_match = strtok_r(NULL, " \n", &str_token_next); // Split the str. <match>
			str_token_str = strtok_r(NULL, " \n", &str_token_next); // Split the str. <str>

			if(str_token_match == NULL || str_token_str == NULL) { // Check the insert format
				//Incorrect insert format
				fprintf(stderr, "Incorrect insert format\n");
				continue;
			}
			list_for_each(list_head_iterator, &head) {
				link_list_match_node = list_entry(list_head_iterator, struct linked_list_node, list);

				if(strcmp(str_token_match, link_list_match_node->str) == 0) {
					link_list_new_node = malloc(sizeof(struct linked_list_node));
					if(link_list_new_node == NULL) {
						fprintf(stderr, "Malloc error from link_list_new_node \n");
						freememory(str, &head);
						return 0 ;
					}

					link_list_new_node->str = strdup(str_token_str);
					if(link_list_new_node->str == NULL) {
						fprintf(stderr, "Malloc error from link_list_new_node->str \n");
						free(link_list_new_node);
						freememory(str, &head);
						return 0 ;
					}



					list_add_tail(&link_list_new_node->list, &link_list_match_node->list); // list_add_tail(new,head)
					break;

				}

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

			list_for_each(list_head_iterator, &head) {
				link_list_match_node = list_entry(list_head_iterator, struct linked_list_node, list);

				if(strcmp(str_token_match, link_list_match_node->str) == 0) { // Find the match.

					//fprintf(stderr, "2 str_token = %08x\n", str_token);
					//fprintf(stderr, "2 str_token = %s\n", str_token);

					link_list_new_node = malloc(sizeof(struct linked_list_node));
					if(link_list_new_node == NULL) {
						fprintf(stderr, "Malloc error from link_list_new_node \n");
						freememory(str, &head);
						return 0 ;
					}

					link_list_new_node->str = strdup(str_token_str);

					if(link_list_new_node->str == NULL) {
						fprintf(stderr, "Malloc error from link_list_new_node->str \n");
						free(link_list_new_node);
						freememory(str, &head);
						return 0 ;
					}


					list_add(&link_list_new_node->list, &link_list_match_node->list); // list_add(new,head)
					break;

				}

			}

		}
	}

	free(str); // Free the memory.

	fprintf(stderr, "Output file : output.txt \n");
	list_for_each_safe(list_head_iterator, list_head_temp, &head) {
		link_list_new_node = list_entry(list_head_iterator, struct linked_list_node, list);
		fprintf(stderr, "%s\n", link_list_new_node->str);
		fprintf(stdout, "%s\n", link_list_new_node->str);

		free(link_list_new_node->str);// Free the memory.
		free(link_list_new_node);// Free the memory.

	}



	return 0 ;

}

void freememory(char *str, struct list_head *head)
{
	struct list_head *list_head_iterator, *list_head_temp;
	// Free the memory.
	free(str);

	list_for_each_safe(list_head_iterator, list_head_temp, head) {
		free(list_entry(list_head_iterator, struct linked_list_node, list)->str);
		free(list_entry(list_head_iterator, struct linked_list_node, list));

	}

}
