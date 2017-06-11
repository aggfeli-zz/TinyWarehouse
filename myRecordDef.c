#include "myRecordDef.h"


void Set_Value(MyRecord *Lhs, MyRecord Rhs)
{  
	strncpy(Lhs->FirstName, Rhs.FirstName, SIZEofBUFF);  
        strncpy(Lhs->LastName, Rhs.LastName, SIZEofBUFF); 
	Lhs->custid = Rhs.custid;
        strncpy(Lhs->Street, Rhs.Street, SIZEofBUFF);
        Lhs->HouseID = Rhs.HouseID;
        strncpy(Lhs->City, Rhs.City, SIZEofBUFF);
        strncpy(Lhs->postcode, Rhs.postcode, SSizeofBUFF); 
	Lhs->amount = Rhs.amount;
}


void Print_Value(MyRecord V)
{   
    printf("%ld %s %s  %s %d %s %s %-9.2f\n", \
            V.custid, V.LastName, V.FirstName, \
            V.Street, V.HouseID, V.City, V.postcode, \
            V.amount);
}
