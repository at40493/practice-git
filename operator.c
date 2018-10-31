#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"

void words_init(struct words *words)
{
	// Create list head.
	LIST_HEAD(name);
	list_replace(&name, &words->list);
}
//add <str>:把str加到link list的尾巴
int words_add(struct words *words, char *word_new)
{
	struct words *list_node_new;

	list_node_new = malloc(sizeof(struct words));
	if(list_node_new == NULL) {
		fprintf(stderr, "Malloc error from list_node_new \n");
		return -1;
	}
	list_node_new->str = strdup(word_new);
	if(list_node_new->str == NULL) { // link list  NULL
		fprintf(stderr, "Malloc error fmrom list_node_new->str \n");
		free(list_node_new);
		return -1;
	}

	list_add_tail(&list_node_new->list, &words->list);

	return 0; // Success add
}
// del <str>在link list中，找到str，並刪除
int words_del(struct words *words, char *word_match)
{
	struct words *list_node_match;
	struct list_head *list_words_iterator, *list_words_temp;

	list_for_each_safe(list_words_iterator, list_words_temp, &words->list) {
		list_node_match = list_entry(list_words_iterator, struct words, list);

		// Find the string which wants to delete.
		if(strcmp(list_node_match->str, word_match) == 0) {
			list_del(&list_node_match->list);
			free(list_node_match->str); // Free the memory.
			free(list_node_match); // Free the memory
			return 0; // Success del
		}
	}
	fprintf(stderr, "Can't find the word : %s\n", word_match);
	return -1;
}
//insert <match> <str>: 找到的match前，加入str
int words_insert(struct words *words, char *word_new, char *word_match)
{
	struct words *list_node_new, *list_node_match;
	struct list_head *list_words_iterator;

	list_for_each(list_words_iterator, &words->list) {
		list_node_match = list_entry(list_words_iterator, struct words, list);

		if(strcmp(word_match, list_node_match->str) == 0) {
			list_node_new = malloc(sizeof(struct words));
			if(list_node_new == NULL) {
				fprintf(stderr, "Malloc error from list_node_new \n");
				return -1;
			}

			list_node_new->str = strdup(word_new);
			if(list_node_new->str == NULL) {
				fprintf(stderr, "Malloc error from list_node_new->str \n");
				free(list_node_new);
				return -1;
			}

			list_add_tail(&list_node_new->list, &list_node_match->list); // list_add_tail(new,words)
			return 0; // Success insert

		}

	}
	fprintf(stderr, "Can't find the word : %s\n", word_match);
	return -1;
}
//append <match> <str>: 找到的match後，加入str
int words_append(struct words *words, char *word_new, char *word_match)
{
	struct words *list_node_new, *list_node_match;
	struct list_head *list_words_iterator;

	list_for_each(list_words_iterator, &words->list) {
		list_node_match = list_entry(list_words_iterator, struct words, list);

		if(strcmp(word_match, list_node_match->str) == 0) { // Find the match.

			list_node_new = malloc(sizeof(struct words));
			if(list_node_new == NULL) {
				fprintf(stderr, "Malloc error from list_node_new \n");
				return -1;
			}

			list_node_new->str = strdup(word_new);
			if(list_node_new->str == NULL) {
				fprintf(stderr, "Malloc error from list_node_new->str \n");
				free(list_node_new);
				return -1;
			}

			list_add(&list_node_new->list, &list_node_match->list); // list_add(new,words)
			return 0; // Success append

		}

	}
	fprintf(stderr, "Can't find the word : %s\n", word_match);
	return -1;
}
// Free the data
void words_cleanup(struct words *words)
{
	struct list_head *list_words_iterator, *list_words_temp;
	// Free the memory.

	list_for_each_safe(list_words_iterator, list_words_temp, &words->list) {
		free(list_entry(list_words_iterator, struct words, list)->str);
		free(list_entry(list_words_iterator, struct words, list));
	}
}
// Print the result
void words_print(struct words *words)
{
	struct list_head *list_words_iterator, *list_words_temp;

	list_for_each_safe(list_words_iterator, list_words_temp, &words->list) {
		fprintf(stderr, "%s\n", list_entry(list_words_iterator, struct words, list)->str);
		fprintf(stdout, "%s\n", list_entry(list_words_iterator, struct words, list)->str);
	}
}

int words_empty(struct words *words)
{
	return list_empty(&words->list);
}




