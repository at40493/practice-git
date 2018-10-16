
// (linux/list.h) v4.18.14  functions ---------------------

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \ 
        struct list_head name = LIST_HEAD_INIT(name)
#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_entry - get the struct for this entry
 * @ptr:        the &struct list_head pointer.
 * @type:       the type of the struct this is embedded in.
 * @member:     the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)
#define offsetof(TYPE, MEMBER) ((unsigned int) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
               (type *)( (char *)__mptr - offsetof(type,member) );})


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
        prev->next = new;
}

// Add function
/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */

static inline void list_add(struct list_head *new, struct list_head *head )
{
        __list_add(new, head, head->next);
}

// Delete function
static inline void __list_del (struct list_head * prev, struct list_head * next)
{
        next->prev = prev ;
        prev->next = next ;
}

// Check empty
static inline int list_empty(const struct list_head *head)
{
        return READ_ONCE(head->next) == head;
}

