/* 
 * File:   double_list.h
 * Author: Ageliki Felimega
 *         1115201300192
 * 
 */

#ifndef DOUBLE_LIST_H
#define	DOUBLE_LIST_H
#include "myRecordDef.h"
typedef struct info_node  * info_pointer;

typedef struct type_node *type_pointer;

/*function declaration*/

/*creation/destruction of list*/
info_pointer LIST_create();
void LIST_destruct(info_pointer * linfo);
int LIST_empty(const info_pointer  linfo);
void LIST_change(info_pointer * const linfo, MyRecord stoixeio,int * error, type_pointer *p);
void LIST_average(const info_pointer  linfo, int * const error);
void LIST_entry(info_pointer * const linfo, MyRecord element,type_pointer *p, int *error);
void LIST_last(const info_pointer  linfo, int k, int * const error);
void list_range(info_pointer  const linfo, long r1, long r2, int *error);					
void list_percentile(info_pointer  const linfo, long rec,int k, int * const error);
void List_top(info_pointer  const linfo, int k, int * const error);

#endif	/* DOUBLE_LIST_H */
