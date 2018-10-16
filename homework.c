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
	struct list_head *iterator, *temp;
	int number = 0 ;
	
	for ( int i = -5 ; i < 10 ; i++){
		
		tmp = malloc(sizeof(struct Linked_list));
		tmp -> num = i ;
		list_add(&tmp->list,&name);
		
	}
	

	list_for_each_safe(iterator, temp ,&name){

                number = list_entry(iterator, struct Linked_list, list)->num;

                if(number == 2)
		{
			list_del(&list_entry(iterator, struct Linked_list, list)->list);
			free(list_entry(iterator, struct Linked_list, list));			
		}
        }

	list_for_each(iterator, &name){
		
		
		printf("%d \n", list_entry(iterator, struct Linked_list, list)->num );
	}

	 return 0 ;

}
