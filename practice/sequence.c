/*
Program Name: sequence.c 
Description : program to find a sequence in a string
Programmer  : Sparsh Jain
Roll No     : 111601026
Date        : September 25, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main()
{
   int i,j,k,t, length, flag = -1;
   char c[1000], *temp, *check;
   temp = (char *)malloc(sizeof(char));
   check = (char *)malloc(sizeof(char));
   printf("\n Enter a string (max 1000 characters): ");
   scanf(" %[^\n]s", c);
   length = strlen(c);

   for(i = 0; i < length; i++)
   {
      for(j = i+1; j < length; j++)
      {
         if(c[j] == c[i])  //Potential sequence found
         {
            if((length - i)%(j-i) != 0)
               continue;
            
            free(temp);
            free(check);
            temp = (char *)calloc(j-i, sizeof(char));
            check = (char *)calloc(j-i, sizeof(char));
            for(k = 0; k < j-i; k++)
            {
               temp[k] = c[i+k];
               check[k] = c[j+k];
            }
            k = j;
            while(k != length)
            {
               flag = strcmp(temp, check);
               if(flag != 0)
                  break;
               k = k + j - i;
               for(t = 0; t < j-i; t++)
                  check[t] = c[k+t];               
            }
            if(flag == 0)
                 break;
         }
         if(flag == 0)
            break;
      }
      if(flag == 0)
         break;
   }

   if(flag != 0)
      printf("\n No sequence found!");
   else
      printf("\n \'%s\' is repeating sequence!", temp);
      //printf("\n \'%s\' is repeating from index %d", temp, i);

   
   free(temp);
   free(check);
   printf("\n\n");
   return 0;
}