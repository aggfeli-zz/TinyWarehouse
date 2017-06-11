/* 
 * File:   linear_hashing.h
 * Author: Ageliki Felimega
 *         1115201300192
 * 
 */

#ifndef LINEAR_HASHING_H
#define	LINEAR_HASHING_H
#include <stdio.h>
#include <malloc.h>
#include "double_list.h"

typedef struct hash_table *hash;

typedef struct simple_list  * slist;


hash create(int m, hash *p);
int hash_entry(hash *bucket, hash *p, int m, int round, int split, type_pointer *pointer);
slist create_simplelist(MyRecord rec,long key, type_pointer *pointer);
void insert_hash(hash *bucket,hash *p, MyRecord rec, int round,int m,  int split,type_pointer *pointer);
void search_hash(hash bucket, MyRecord rec,int sum, type_pointer *p,int *found) ;
void destruct_hash(hash *bucket, int sum);

#endif	/* LINEAR_HASHING_H */

