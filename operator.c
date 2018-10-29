#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "operator.h"

//add <str>:把str加到link list的尾巴
bool add_word(char *str_token_str, struct list_head *head)
{
	struct list_node_word *list_node_new;

	list_node_new = malloc(sizeof(struct list_node_word));
	if(list_node_new == NULL) {
		fprintf(stderr, "Malloc error from list_node_new \n");
		return false;
	}

	list_node_new->str = strdup(str_token_str);
	if(list_node_new->str == NULL) { // link list  NULL
		fprintf(stderr, "Malloc error from list_node_new->str \n");
		free(list_node_new);
		return false;
	}

	list_add_tail(&list_node_new->list, head);

	return true;
}
// del <str>在link list中，找到str，並刪除
void del_word(char *str_token_str, struct list_head *head)
{
	struct list_node_word *list_node_match;
	struct list_head *list_head_iterator, *list_head_temp;

	list_for_each_safe(list_head_iterator, list_head_temp, head) {
		list_node_match = list_entry(list_head_iterator, struct list_node_word, list);

		// Find the string which wants to delete.
		if(strcmp(list_node_match->str, str_token_str) == 0) {
			list_del(&list_node_match->list);
			free(list_node_match->str); // Free the memory.
			free(list_node_match); // Free the memory
			break;
		}
	}
}
//insert <match> <str>: 找到的match前，加入str
bool insert_word(char *str_token_match, char *str_token_str, struct list_head *head)
{
	struct list_node_word *list_node_new, *list_node_match;
	struct list_head *list_head_iterator;

	list_for_each(list_head_iterator, head) {
		list_node_match = list_entry(list_head_iterator, struct list_node_word, list);

		if(strcmp(str_token_match, list_node_match->str) == 0) {
			list_node_new = malloc(sizeof(struct list_node_word));
			if(list_node_new == NULL) {
				fprintf(stderr, "Malloc error from list_node_new \n");
				return false;
			}

			list_node_new->str = strdup(str_token_str);
			if(list_node_new->str == NULL) {
				fprintf(stderr, "Malloc error from list_node_new->str \n");
				free(list_node_new);
				return false;
			}

			list_add_tail(&list_node_new->list, &list_node_match->list); // list_add_tail(new,head)
			break;

		}

	}

	return true;
}
//append <match> <str>: 找到的match後，加入str
bool append_word(char *str_token_match, char *str_token_str, struct list_head *head)
{
	struct list_node_word *list_node_new, *list_node_match;
	struct list_head *list_head_iterator;

	list_for_each(list_head_iterator, head) {
		list_node_match = list_entry(list_head_iterator, struct list_node_word, list);

		if(strcmp(str_token_match, list_node_match->str) == 0) { // Find the match.

			list_node_new = malloc(sizeof(struct list_node_word));
			if(list_node_new == NULL) {
				fprintf(stderr, "Malloc error from list_node_new \n");
				return false;
			}

			list_node_new->str = strdup(str_token_str);
			if(list_node_new->str == NULL) {
				fprintf(stderr, "Malloc error from list_node_new->str \n");
				free(list_node_new);
				return false;
			}

			list_add(&list_node_new->list, &list_node_match->list); // list_add(new,head)
			break;

		}

	}

	return true;
}
// Free the data
void free_data(char *str, struct list_head *head)
{
	struct list_head *list_head_iterator, *list_head_temp;
	// Free the memory.
	free(str);

	list_for_each_safe(list_head_iterator, list_head_temp, head) {
		free(list_entry(list_head_iterator, struct list_node_word, list)->str);
		free(list_entry(list_head_iterator, struct list_node_word, list));
	}
}
// Print the result
void list_print(struct list_head *head)
{
	struct list_head *list_head_iterator, *list_head_temp;

	list_for_each_safe(list_head_iterator, list_head_temp, head) {
		fprintf(stderr, "%s\n", list_entry(list_head_iterator, struct list_node_word, list)->str);
		fprintf(stdout, "%s\n", list_entry(list_head_iterator, struct list_node_word, list)->str);
	}
}
