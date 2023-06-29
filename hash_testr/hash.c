
#include <stdlib.h>
#include <stdio.h>

#include "hash.h"
#include "forward_list.h"

struct HashTableIterator {
    HashTable *hash_tbl;
    int current_bucket_idx;
    Node *current_node;
};

struct HashTable {
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

HashTableItem *_hash_pair_construct(void *key, void *val) {
    HashTableItem *p = calloc(1, sizeof(HashTableItem));
    p->key = key;
    p->val = val;
    return p;
}

void _hash_pair_destroy(HashTableItem *p) {
    free(p);
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) {
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

void* hash_table_set(HashTable *h, void *key, void *val) {
    int idx = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[idx];

    if (bucket == NULL) {
        bucket = forward_list_construct();
        h->buckets[idx] = bucket;
    }

    Node *n = bucket->head;
    while (n != NULL) {
        HashTableItem *pair = n->value;
        if (h->cmp_fn(pair->key, key) == 0) {
            void *old_val = pair->val;
            pair->val = val;
            return old_val;
        }
        n = n->next;
    }

    HashTableItem *pair = _hash_pair_construct(key, val);
    forward_list_push_front(bucket, pair);
    h->n_elements++;

    return NULL;
}

void *hash_table_get(HashTable *h, void *key) {
    void *val = NULL;

    int idx = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[idx];

    if (bucket != NULL) {
        Node *n = bucket->head;
        while (n != NULL) {
            HashTableItem *pair = n->value;
            if (h->cmp_fn(pair->key, key) == 0) {
                val = pair->val;
                break;
            }
            n = n->next;
        }
    }

    return val;
}

void *hash_table_pop(HashTable *h, void *key) {
    void* val = NULL;

    int idx = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[idx];

    if (bucket != NULL) {
        Node *n = bucket->head;
        Node *prev = NULL;
        while (n != NULL) {
            HashTableItem *pair = n->value;
            if (h->cmp_fn(pair->key, key) == 0) {
                val = pair->val;
                if (prev == NULL) {
                    bucket->head = n->next;
                }
                else {
                    prev->next = n->next;
                }
                _hash_pair_destroy(pair);
                free(n);
                h->n_elements--;
                break;
            }
            prev = n;
            n = n->next;
        }
    }

    return val;
}

int hash_table_size(HashTable *h) {
    return h->table_size;
}

int hash_table_num_elems(HashTable *h) {
    return h->n_elements;
}

void hash_table_destroy(HashTable *h) {
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                _hash_pair_destroy(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

void hash_table_print(HashTable* h, void (*print_key_fn)(void*), void (*print_val_fn)(void*)) {
    HashTableIterator *it = hash_table_iterator_construct(h);
    
    printf("{\n");
    while(!hash_table_iterator_is_over(it)) {
        HashTableItem *item = hash_table_iterator_next(it);
        if(item != NULL && item->key != NULL && item->val != NULL) {
            printf("\t");
            print_key_fn(item->key);
            printf(": ");
            print_val_fn(item->val);
            printf("\n");
        }
    }

    printf("}\n");

    hash_table_iterator_destroy(it);
}


HashTableIterator* hash_table_iterator_construct(HashTable *h) {
    HashTableIterator* it = malloc(sizeof(HashTableIterator));
    it->hash_tbl = h;
    it->current_bucket_idx = 0;
    it->current_node = NULL;
    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it) {
    Node* last_node_from_bucket = NULL;
    for(int i = hash_table_size(it->hash_tbl) - 1; i >= 0; i--) {
        if (it->hash_tbl->buckets[i] != NULL) {
            last_node_from_bucket = it->hash_tbl->buckets[i]->last;
            break;
        }
    }
    return it->current_node == last_node_from_bucket;
}

HashTableItem* hash_table_iterator_next(HashTableIterator *it) {
    HashTableItem* old_item = NULL;
    // se it->current_node == NULL, significa que é a primeira vez que a função é chamada
    if (it->current_node == NULL) {
        // procura o primeiro bucket que não é nulo
        for(int i = 0; i < hash_table_size(it->hash_tbl); i++) {
            if (it->hash_tbl->buckets[i] != NULL) {
                it->current_bucket_idx = i;
                it->current_node = it->hash_tbl->buckets[i]->head;
                old_item = it->current_node->value;
                break;
            }
        }
        return old_item;
    }

    // se o nó atual não é o último do bucket, avança para o próximo
    if (it->current_node != it->hash_tbl->buckets[it->current_bucket_idx]->last) {
        it->current_node = it->current_node->next;
        old_item = it->current_node->value;
        return old_item;
    }

    // se o nó atual é o último do bucket, procura o próximo bucket que não é nulo
    for(int i = it->current_bucket_idx + 1; i < hash_table_size(it->hash_tbl); i++) {
        if (it->hash_tbl->buckets[i] != NULL) {
            it->current_bucket_idx = i;
            it->current_node = it->hash_tbl->buckets[i]->head;
            old_item = it->current_node->value;
            break;
        }
    }
    return old_item;
}

void hash_table_iterator_destroy(HashTableIterator *it) {
    free(it);
}


// ANDREZA <3
// mim leva ;-; <------------------- 