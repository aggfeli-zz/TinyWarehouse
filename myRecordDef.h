/* 
 * File:   myRecordDef.h
 * Author: Ageliki Felimega
 *         1115201300192
 * 
 */

#ifndef MY_RECORD_DEF_H
#define	MY_RECORD_DEF_H
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZEofBUFF 20
#define SSizeofBUFF 6

typedef struct MyRecord{
	long  	custid; 
	char 	FirstName[SIZEofBUFF];
	char 	LastName[SIZEofBUFF];
	char	Street[SIZEofBUFF];
	int 	HouseID;	
	char	City[SIZEofBUFF];
	char	postcode[SSizeofBUFF];
	float  	amount;
} MyRecord;


void Set_Value(MyRecord *Lhs, MyRecord Rhs); // Lhs = Rhs

void Print_Value(MyRecord V);


#endif	/*MY_RECORD_DEF_H */

