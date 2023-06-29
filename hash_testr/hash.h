
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef struct HashTableIterator HashTableIterator;

typedef struct HashTable HashTable;

typedef int (*HashFunction)(HashTable *, void *);
typedef int (*CmpFunction)(void *k1, void *k2);

typedef struct HashTableItem {
    void *key;
    void *val;
} HashTableItem;

/// @brief Cria um iterador para a tabela hash
/// @param h    Tabela hash
/// @return HashTableIterator*
HashTableIterator* hash_table_iterator_construct(HashTable *h);

/// @brief Verifica se o iterador chegou ao fim da tabela hash
/// @param it  Iterador
/// @return int
int hash_table_iterator_is_over(HashTableIterator *it);

/// @brief Retorna o próximo item da tabela hash
/// @param it 
/// @return HashTableItem*
HashTableItem* hash_table_iterator_next(HashTableIterator *it);

/// @brief Libera o espaço alocado para o iterador
/// @param it 
void hash_table_iterator_destroy(HashTableIterator *it);

/**
 * @brief Cria a tabela hash
 * @param table_size
 * Número de buckets na tabela hash
 * @param hash_fn
 * Ponteiro de função que recebe como entrada uma chave do tipo void* e retorna um inteiro
 * @param cmp_fn
 * Ponteiro de função que recebe como entrada dois void* representando duas chaves e tem a mesma semântica da função strcmp
 * @return HashTable*
 * Retorna o ponteiro da tabela hash recém alocada.
 */
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);

// funcao para insercao/atualizacao de pares chave-valor em O(1).
void* hash_table_set(HashTable *h, void *key, void *val);

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void* hash_table_get(HashTable *h, void *key);

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void* hash_table_pop(HashTable *h, void *key);

// numero de buckets
int hash_table_size(HashTable *h);

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h);

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h);

void hash_table_print(HashTable* h, void (*print_key_fn)(void*), void (*print_val_fn)(void*));

#endif