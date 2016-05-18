#include <stdlib.h>
#include <malloc.h>        
#include "queue.h"   
#include <memory.h>       

struct ListItem
{
    int data;
    LIST_ENTRY(ListItem) entry;
};

void list_demo(void)
{
    struct ListItem* item = NULL;
    
    LIST_HEAD(ListHead, ListItem) lhead;

    LIST_INIT(&lhead);

    item = (struct ListItem*)malloc(sizeof(struct ListItem));
    item->data = 1;

    LIST_INSERT_HEAD(&lhead, item, entry);
    
    item = (struct ListItem*)malloc(sizeof(struct ListItem));
    item->data = 2;
    
    LIST_INSERT_HEAD(&lhead, item, entry);

    LIST_FOREACH(item, &lhead, entry){
        printf("%d ", item->data);
    }

    printf("\n");

    while(!LIST_EMPTY(&lhead)){
        item = LIST_FIRST(&lhead);
        printf("remove %d\n", item->data);
        LIST_REMOVE(item, entry);
        free(item);
    }

}

int main(void)  
{  
    list_demo();
}

