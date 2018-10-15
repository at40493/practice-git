#include<stdio.h>

// linux/list.h v4.18.14  functions ---------------------

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \ 
        struct list_haed name = LIST_HEAD_INIT(name)
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)


// The list head
struct list_head{
     
	struct list_head *next, *prev;
};

// Add function
static inline void __list_add (struct list_head *new,
			     struct list_head *prev,
                             struct list_head *next)
{
         
	next->prev = new ;
	new ->next = next;
        new ->prev = prev;
        WRITE_ONCE(prev -> next, new);
}

// Add function
static inline void list_add(struct list_head *new, struct list_head *head )
{
	__list_add(new, head, head->next);
}

// Delete function
static inline void __list_del (struct list_head * prev, struct list_head * next)
{
	next->prev = prev ;
	WRITE_ONCE(prev->next, next);
}

// Check empty
static inline int list_empty(const struct list_head *head)
{
	return READ_ONCE(head->next) == head;
}

// ---------------------------------------------------



struct Linked_list{

	int num ; 
	struct list_head list;
};

int main()
{




 return 0 ;

}
