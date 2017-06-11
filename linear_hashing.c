#include "linear_hashing.h"


typedef struct simple_list{
    MyRecord data;
    type_pointer pointer;
    long key;
    slist next;
}simple_list;

typedef struct hash_table{
    int size;  //size of buckets
    slist head;    
}hash_table;



hash create(int m, hash *p)  //Create hashtable and pointer p 
{
    hash new_table = calloc(m, sizeof(hash_table));
    if (new_table == NULL) {
        return NULL;
    }
    *p = malloc(sizeof(hash_table));
    (*p)->head = NULL;
    (*p)->size = 0;
    return new_table;
}

int hash_entry(hash *bucket, hash *p, int m, int round, int split, type_pointer *pointer) //Handle split
{
    int error = 0, i = 0 ;
    MyRecord rec;
    slist node;
    split = 1;
    hash temp = (hash )realloc (*bucket, (m + 1) * sizeof(hash_table )); //Reallocate memory for hashtable
    if (temp != NULL) *bucket = temp;
    
    while((*bucket)[(*p)->size].head != NULL)  //For every record in the bucket that p points, rehash them  
    {
        Set_Value(&rec, (*bucket)[(*p)->size].head->data);
        
        node = (*bucket)[(*p)->size].head;
        if ((*bucket)[(*p)->size].head->next != NULL)
            (*bucket)[(*p)->size].head = (*bucket)[(*p)->size].head->next;
        else
            (*bucket)[(*p)->size].head = NULL;
        (*bucket)[(*p)->size].size --;
        free(node);
        insert_hash(bucket, p, rec, round, m, split, pointer);
        if ((*bucket)[(*p)->size].head != NULL)
        {
            if ((*bucket)[(*p)->size].head->data.custid == rec.custid)
                (*bucket)[(*p)->size].head = (*bucket)[(*p)->size].head->next;
        }
    }
    (*p)->size ++;

    return error;
}
   

slist create_simplelist(MyRecord rec,long key,type_pointer *p) //Create siple list
{
    slist temp = (slist) malloc(sizeof(simple_list));
    if ( temp == NULL )  return;   
    temp->pointer = *p;
    Set_Value(&(temp->data), rec);
    temp->key = key;
    temp->next = NULL;
        
    return temp;
}

void insert_hash(hash *bucket,hash *p, MyRecord rec, int round, int m, int split,type_pointer *pointer) 
{                                   //Function that inserts records in hashtable
    int key;
    int x = pow(2,round);                
    int h1 = rec.custid % (x * m);      //Find round's hash function 
    x = (int)(pow(2,round + 1));
    int h2 = rec.custid % (x * m);      //Fine next round's hash function

    if (split == 1) key = h2;                   //Choose key
    else if (h1 < (*p)->size) key = h2;
    else key = h1;
    slist temp =  create_simplelist(rec, key, pointer);

    if ((*bucket)[key].head == NULL) 
    {
        (*bucket)[key].head = temp;
        (*bucket)[key].size = 1;
        return;
    }

    temp->next = ((*bucket)[key].head);         //Add new node to the list 
    (*bucket)[key].head = temp;
    (*bucket)[key].size++;

    return;
  }


void destruct_hash(hash *bucket, int sum)
{ 
    int i;
    slist todel,todel2;
    for (i = 0; i < sum; i++)
    {
        todel = (*bucket)[i].head;
	while(todel != NULL)
	{   
            todel2 = todel;
            todel = (todel)->next;
            free(todel2);
	}
	(*bucket)[i].head = NULL;
    }
    free(*bucket);
    (*bucket)=NULL;
}

void search_hash(hash bucket, MyRecord rec, int sum, type_pointer *p, int *found)
{
    int i;
    slist temp;
    *found = 0;
    for(i = 0 ; i < sum ; i++)
    {
        if (bucket[i].size != 0)
        {
            temp = bucket[i].head;
            while(temp != NULL)
            {
                if (temp->data.custid == rec.custid)
                {
                    Print_Value( temp->data);
                    *p = temp->pointer;
                    *found = 1;
                    return;
                }
                temp = temp->next;
            }        
        }
        
    }
    return;
}