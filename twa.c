/* 
 * File:   twa.c
 * Author: Ageliki Felimega
 *         1115201300192
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "double_list.h"
#include "myRecordDef.h"
#include "linear_hashing.h"

int main(int argc, char** argv) 
{
    info_pointer list = NULL;
    type_pointer pointer;
    hash hashtable = NULL, p = NULL;
    FILE *fpb;
    MyRecord rec, rec1;
    long lSize;
    int numOfrecords, i = 0, error = 0, sum = 0, first_file = 0;
    
    list = LIST_create();
    int number_of_buckets = atoi(argv[4]);    //initial number of buckets

    hashtable = create(number_of_buckets, &p);
    char buf[200];
    char *datafile, *token = "l", *temp;
    
    
    while (strcmp(token,"e") != 0)
    {
        if ( first_file != 0){          //If first_file(argv[2]) hasn't been opened, don't read commands
            fgets(buf, sizeof(buf), stdin);
            token = strtok(buf," ");
        }
        if (strcmp(token,"l") == 0 || first_file == 0) i = 1;
        else if (strcmp(token,"i") == 0) i = 2;
        else if (strcmp(token,"q") == 0) i = 3;
        else if (strcmp(token,"t") == 0) i = 4;
        else if (strcmp(token,"b") == 0) i = 5;
        else if (strcmp(token,"a") == 0) i = 6; 
        else if (strcmp(token,"r") == 0) i = 7;
        else if (strcmp(token,"p") == 0) i = 8;
        else if (strcmp(token,"e") == 0) i = 9;
        else printf("Try again!\n");
        
        switch(i){
            case 1:                   //First case: syntax:l DataFile + creation of double list- hashtable 
                if (first_file != 0) {
                    while( token != NULL ) 
                    {
                       token = strtok(NULL, " ");
                       datafile = (char*)malloc(60*strlen(token));
                       strncpy(datafile,token,strlen(token)-1);
                       break;
                    } 
                    fpb = fopen (datafile,"rb");
                    if (fpb == NULL) {
                        printf("Cannot open binary file\n");
                        return 1;
                    }}
                else{                           //Open argv[2] datafile 
                    fpb = fopen (argv[2],"rb");
                    if (fpb == NULL) {
                        printf("Cannot open binary file\n");
                        return 1;
                    }
                    first_file = 1;           
                }
                
                fseek (fpb , 0 , SEEK_END);             // check number of records
                lSize = ftell (fpb);
                rewind (fpb);
                numOfrecords = (int) lSize/sizeof(rec);
                // printf("Records found in file %d \n", numOfrecords);
                // sleep(5);
                int round = 0, split = 0;
                for (i = 0; i < numOfrecords ; i++) 
                {
                    fread(&rec, sizeof(rec), 1, fpb);

                    LIST_entry(&list, rec, &pointer, &error); //Insert element in the double list
                    if (error == 1) printf("Error!Insertion of element %d failed\n", i);

                    insert_hash(&hashtable, &p, rec, round, atoi(argv[4]), split, &pointer); //Insert element in the hashtable
                    if ((((float) i )/ pow(number_of_buckets,2)) > atof(argv[6])) //Split
                    {                      
                       error = hash_entry(&hashtable, &p, number_of_buckets, round, split, &pointer); //Function handles split
                       if (error == 1) printf("Error while inserting new bucket\n");
                       number_of_buckets++;    //After split increase number of buckets
                    }
                    if(number_of_buckets == (2 * sum))  //new round
                    {
                        round++;
                        sum = number_of_buckets * 2;
                    }
                }

                printf("%d records inserted\n\n", i);
                fclose (fpb);
                free(datafile);
            break;
            case 2:      //Second case: syntax:i customerid lastname firstname street number postcode city amount
                i = 1;
                temp = (char*)malloc(60 * strlen(token));
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   
                   strncpy(temp,token,strlen(token));
                   if(i == 1) rec.custid = atoi(temp);
                   if(i == 2) strcpy(rec.LastName, temp);
                   if(i == 3) strcpy(rec.FirstName, temp);
                   if(i == 4) strcpy(rec.Street, temp);
                   if(i == 5) rec.HouseID = atoi(temp);
                   if(i == 6) strcpy(rec.postcode, temp);
                   if(i == 6) strcpy(rec.City, temp);
                   if(i == 7) rec.amount = atoi(temp); 
                   if (i==8) break;                    
                   i++;
                }
                int found = 0;
                search_hash(hashtable, rec, number_of_buckets,&pointer, &found);
                if (found == 0)
                {   
                    
                    LIST_entry(&list, rec, &pointer, &error);
                    if (error == 0) printf("Record inserted\n");
                    else printf("Error while inserting record\n");
                    round = 0;
                    split = 0;
                    insert_hash(&hashtable, &p, rec, round, atoi(argv[4]), split, &pointer);
                }
                else 
                {
                    LIST_change( &list, rec, &error, &pointer);
                    if (error == 0) printf("Record has been updated\n");
                    else printf("Error while updating record\n");
                }
                printf("\n");
                free(temp);
            break;
            case 3:  //Third case: syntax:q customerid 
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   temp = (char*)malloc(60*strlen(token));
                   strncpy(temp,token,strlen(token));
                   rec.custid = atoi(temp);
                   break;
                }
                search_hash(hashtable, rec, number_of_buckets,&pointer, &found);
                if (found == 0) printf("record with id: %lu does not exist\n",rec.custid);
                free(temp);
                printf("\n");
            break;
            case 4:  //Fourth case: syntax:t k
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   temp = (char*)malloc(60*strlen(token));
                   strncpy(temp,token,strlen(token));
                   i = atoi(temp);
                   break;  
                }
                List_top(list, i, &error); //Find and print k first customers
                if (error == 1) printf("Error with printing %d first customers\n", i);
                free(temp);
                printf("\n");
            break;
            case 5:  //Fifth case: syntax:b k
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   temp = (char*)malloc(60*strlen(token));
                   strncpy(temp,token,strlen(token));
                   i = atoi(temp);
                   break; 
                }
                LIST_last(list, i, &error);  //Find and print k last customers
                if (error == 1) printf("Error with printing %d last customers\n", i);
                free(temp);
                printf("\n");
            break;
            case 6: //Sixth case: syntax:a (something)
                LIST_average(list, &error);  //Find and print avg of amounts
                if (error == 1) printf("Error with average\n");
                printf("\n");
            break;
            case 7: //Seventh case: syntax:r custid1 custid2
                i = 1;
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   temp = (char*)malloc(60*strlen(token));
                   strncpy(temp,token,strlen(token));
                   if (i == 1) rec.custid = atoi(temp);
                   else
                    {
                       rec1.custid = atoi(temp);
                       break;
                    }
                   i++;
                }
                list_range(list, rec.custid, rec1.custid, &error); //Print every customer between these two records
                free(temp);
                printf("\n");
            break;
            case 8:         //eighth case: syntax:q customerid
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   temp = (char*)malloc(60*strlen(token));
                   strncpy(temp,token,strlen(token));
                   rec.custid = atoi(temp);
                   break;
                }
                list_percentile(list, rec.custid , numOfrecords, &error);
                
            break;
            case 9: //Ninth case: syntax: e (something) ->Free memory and terminate program
                LIST_destruct(&list); //Destruct double list
                destruct_hash(&hashtable, number_of_buckets); //Destruct hashtable
                strcpy(token,"e");
            break;
        }
    }

    return (EXIT_SUCCESS);
}