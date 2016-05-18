#include <stdlib.h>
#include <malloc.h>        
#include "queue.h"   
#include <memory.h>   

struct SListItem
{
    int data;
    SLIST_ENTRY(SListItem) entry;
};
void slist_demo()
{
    struct SListItem* item = NULL;
    SLIST_HEAD(SListHead, SListItem) shead;
    
    SLIST_INIT(&shead);

    item = (struct SListItem*)malloc(sizeof(struct SListItem));
    item->data = 1;

    SLIST_INSERT_HEAD(&shead, item, entry);

    item = (struct SListItem*)malloc(sizeof(struct SListItem));
    item->data = 2;

    SLIST_INSERT_HEAD(&shead, item, entry);

    SLIST_FOREACH(item, &shead, entry){
        printf("%d ", item->data);
    }

    printf("\n");

    while(!SLIST_EMPTY(&shead)){
        item = SLIST_FIRST(&shead);
        printf("remove %d\n", item->data);
        SLIST_REMOVE(&shead, item, SListItem, entry);
        free(item);
    }

}

int main(void)  
{  
    slist_demo();
}

