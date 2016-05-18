#include <stdlib.h>
#include <malloc.h>        
#include "queue.h"   
#include <memory.h>       

struct ListItem
{
    int data;
    SLIST_ENTRY(ListItem) entry;
};

void list_demo(void)
{
    struct ListItem* item = NULL;
    
    SLIST_HEAD(SListHead, ListItem) lhead;

    SLIST_INIT(&lhead);

    item = (struct ListItem*)malloc(sizeof(struct ListItem));
    item->data = 1;

    SLIST_INSERT_HEAD(&lhead, item, entry);
    
    item = (struct ListItem*)malloc(sizeof(struct ListItem));
    item->data = 2;
    
    SLIST_INSERT_HEAD(&lhead, item, entry);

    SLIST_FOREACH(item, &lhead, entry){
        printf("%d ", item->data);
    }

    printf("\n");

    while(!SLIST_EMPTY(&lhead)){
        item = SLIST_FIRST(&lhead);
        printf("remove %d\n", item->data);
        SLIST_REMOVE_HEAD(&lhead, entry);
        free(item);
    }

}

int main(void)  
{  
    list_demo();
}

