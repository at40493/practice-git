#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "list.h"

// Word struct.
struct words {
    char *str ;
    struct list_head list;
};

// Create word list.
int words_init(struct words *words);
// Add word function
int words_add(struct words *words, char *word_new);
// Del word function
int words_del(struct words *words, char *word_match);
// Insert word function 找到的match前，加入str
int words_insert(struct words *words, char *word_new, char *word_match);
// Append word function 找到的match後，加入str
int words_append(struct words *words, char *word_new, char *word_match);
// Free the data
int words_deinit(struct words *words);
// Print the result
int words_print(struct words *words);

#endif




