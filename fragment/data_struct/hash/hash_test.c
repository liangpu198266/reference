#include <stdlib.h>
#include <malloc.h>        
#include "comm_hash.h"    
#include <memory.h>     
#include <string.h>

struct q_coef
{
    unsigned char coef;
    unsigned char index;
    struct hlist_node hash;
};

#define HASH_NUMBER 15
unsigned char coef[HASH_NUMBER] = {
    0x01, 0x02, 0x04, 0x08,0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13,
};
struct q_coef q_coef_list[HASH_NUMBER];

struct hlist_head hashtbl[HASH_NUMBER];

static inline int hash_func(unsigned char k)
{
    int a, b, p, m;
    a = 104;
    b = 52;
    p = 233;
    m = HASH_NUMBER;
    return ((a * k + b) % p) % m;
}

static void hash_init(void)
{
    int i, j;
    for (i = 0 ; i < HASH_NUMBER ; i++) {
        INIT_HLIST_HEAD(&hashtbl[i]);
        INIT_HLIST_NODE(&q_coef_list[i].hash);
        q_coef_list[i].coef = coef[i];
        q_coef_list[i].index = i + 1;
    }
    for (i = 0 ; i < HASH_NUMBER ; i++) {
        j = hash_func(q_coef_list[i].coef);
        hlist_add_head(&q_coef_list[i].hash, &hashtbl[j]);
    }
}

static void hash_test(void)
{
    int i, j;
    struct q_coef *q;
    struct hlist_node *hn;
    for (i = 0 ; i < HASH_NUMBER ; i++) {
        j = hash_func(coef[i]);
        hlist_for_each_entry(q, hn, &hashtbl[j], hash)
            if (q->coef == coef[i])
                printf("found: coef=0x%02x index=%d\n", q->coef, q->index);
    }
}
int main(void)  
{
    hash_init();
    hash_test();
    return -1;
}


