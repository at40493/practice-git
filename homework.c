#include<stdio.h>
#include<stdlib.h>
#include<list.h>


struct Linked_list{

	int num ; 
	struct list_head list;
};

int main()
{

	LIST_HEAD(name);
	struct Linked_list *tmp ;
	struct list_head *iterator;
	
	for ( int i = -5 ; i < 10 ; i++){
		
		tmp = malloc(sizeof(struct Linked_list));
		tmp -> num = i ;
		list_add(&tmp->list,&name);
	}

	list_for_each(iterator, &name){
		
		printf("%d \n", list_entry(iterator, struct Linked_list, list)->num );
	}
 return 0 ;

}
