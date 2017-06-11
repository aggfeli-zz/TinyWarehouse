#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "double_list.h"

typedef struct info_node
{   int size;	
    type_pointer    start; 	/*deikths sto proto komvo tis listas*/
} info_node;     /* o komvos plhroforias ths listas*/        


typedef struct type_node
{   MyRecord data;	
    type_pointer    next; 	
    type_pointer    previous; 	
} type_node;	   /*o typos toy kombou ths listas*/


info_pointer LIST_create( )
{	
    info_pointer linfo;
    linfo = malloc(sizeof(info_node));
    linfo->size = 0;
    linfo->start = NULL;
    return linfo;
}

void LIST_destruct(info_pointer * linfo)
{
    type_pointer todel,todel2;
    todel = (*linfo)->start;
    while(todel != NULL)
    {   todel2 = todel;
	todel = (todel)->next;
	free(todel2);
    }
    (*linfo)->start = NULL;
    free(*linfo);
    (*linfo)=NULL;
}

int LIST_empty(const info_pointer  linfo)
{
    return ( linfo->start == NULL );
}

void LIST_change( info_pointer * const linfo , MyRecord element,int * error,type_pointer *p) //Update record
{  
    *error = 0;   
    if(*p != NULL)
    {
        (*p)->data.amount += element.amount;
        return;
    }
    else
       *error = 1;	
}

void LIST_average(const info_pointer  linfo, int * const error)  //Find and print avg of amounts
{   
    int sum = 0;
    type_pointer temp = (linfo)->start;
    *error = 0;	
    if(LIST_empty(linfo))
    {   *error=1;
	return;
    }
    while(temp != NULL)
    {   
        sum = sum + temp->data.amount;
        temp = temp->next;
    }
    float average = sum / linfo->size ; 
    printf("Average = %f\n", average); 
}

void LIST_entry(info_pointer *  const linfo,MyRecord element,type_pointer *p, int *error)
{
    type_pointer temp, pointer; 
    pointer = (*linfo)->start;
    temp = malloc(sizeof(type_node));
    if ( temp == NULL )
    {   *error = 1;
        return;
    }
    Set_Value(&(temp->data), element);
    if ((*linfo)->start==NULL)                    //First entry
    {
        temp->next = (*linfo)->start;
        temp->previous=NULL;
        (*linfo)->start = temp;  
    }
    else if (temp->data.amount >= pointer->data.amount)     //Entry at the beginning of the double list   
    {
        temp->next = pointer;
        temp->previous = NULL;
        pointer->previous = temp;  
        (*linfo)->start = temp;
    }
    else
    {
        int i = 0;
        while(pointer->next != NULL)             //While you aren't at the end of the list
        {
            pointer = pointer->next;
            if (temp->data.amount >= pointer->data.amount)     //Compare customers amounts 
            {                                                  //and find where to enter the new customer 
                temp->previous = pointer->previous;
                temp->next = pointer;
                pointer->previous->next = temp;
                pointer->previous = temp;
                i = 1;
                break;
            }
        }
        if (i != 1)     //New entry at the end of the list
        { 
            temp->previous = pointer;
            temp->next = NULL;
            pointer->next = temp;
        }
    }
    (*linfo)->size ++;
    *p = temp;
}


void LIST_last(info_pointer  const linfo, int k, int * const error)
{
    type_pointer temp;
    *error = 0;
    type_pointer last = NULL;
    int i;
    if(LIST_empty(linfo))           
	*error = 1;                 
    else             
    {
        temp = linfo->start;
	while (temp->next != NULL)
            temp = temp->next;
	last = temp;
        for (i = 0; i < k; i++)
        {
            Print_Value(last->data);
            last = last->previous;
        }
    }   
}


void List_top(info_pointer  const linfo, int k, int * const error)
{
    type_pointer pointer; 
    pointer = linfo->start;
    int i;
    for(i = 0; i < k; i++)
    {
        if(pointer->next != NULL)
        {
            Print_Value(pointer->data);
            pointer = pointer->next;
        }
    }
    return;
}

void list_range(info_pointer  const linfo, long r1, long r2, int *error)
{
    type_pointer temp1 = (linfo)->start;
    type_pointer temp2 = (linfo)->start;
    type_pointer temp;
    *error = 0;	
    if(LIST_empty(linfo))
    {   *error = 1;
	return;
    }
    while(temp1 != NULL)  //Find first record in the list
    {   
        if(temp1->data.custid == r1) break;
        temp1 = temp1->next;
    }
    while(temp2 != NULL)   //Find second record in the list
    {   
        if((temp2)->data.custid == r2) break;
        temp2 = temp2->next;
    }
    if ((temp1)->data.amount > (temp2)->data.amount)
    {
        temp = temp2->previous;
        while(temp != temp1)
        {
            Print_Value(temp->data);
            temp = temp->previous;
        }
    }
    else
    {
        temp = temp1->previous;
        while(temp != temp2)
        {
            Print_Value(temp->data);
            temp = temp->previous;  
        }
    }
}

void list_percentile(info_pointer  const linfo, long rec,int k, int * const error)
{
    type_pointer pointer; 
    pointer = linfo->start;
    int i;
    for(i = 0; i < k; i++)
    {
        if(pointer->next != NULL && pointer->data.custid != rec)
            pointer = pointer->next;
        else
            break;
    }
    float percentile = (100 * (i - 1.5)) / (float)k;
    printf("%f\n",percentile);
    return;
}
