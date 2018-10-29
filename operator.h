

// Linked-list node for word.
struct list_node_word {
	char *str ;
	struct list_head list;
};

// Add word function
bool add_word(char *str_token_str, struct list_head *head);
// Del word function
void del_word(char *str_token_str, struct list_head *head);
// Insert word function 找到的match前，加入str
bool insert_word(char *str_token_match, char *str_token_str, struct list_head *head);
// Append word function 找到的match後，加入str
bool append_word(char *str_token_match, char *str_token_str, struct list_head *head);
// Free the data
void free_data(char *str, struct list_head *head);
// Print the result
void list_print(struct list_head *head);
