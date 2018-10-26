#include<stdbool.h>
#include<stddef.h> // offsetof

#ifdef CONFIG_ILLEGAL_POINTER_VALUE
# define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL)
#else
# define POISON_POINTER_DELTA 0
#endif

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */

#define LIST_POISON1  ((void *) 0x00100100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x00200200 + POISON_POINTER_DELTA)


#define WRITE_ONCE(traget,source) \
		traget = source 

#define READ_ONCE(target) \
		target 


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	((type *)(__mptr - offsetof(type, member))); })

// The hlist_head
struct hlist_head {
	struct hlist_node *first;
};

// The hlist_node
struct hlist_node {
	struct hlist_node *next, **pprev;
};
// The list head
struct list_head {
	struct list_head *next, *prev;
};


