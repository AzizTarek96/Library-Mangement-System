#include<stdio.h>
#include"STD_TYPES.h"
#include<string.h>

#define LibLimit 100

u16 size=0;

enum
{
	Available,
	Borrowed,
	NA,
};
typedef struct 
{
	u8 Name[100];
	u8 AuthorN[100];
	u8 Status;
	u16 PubY;
	u16 NC;
	f32 Price;
}Lib;
u8 Status[3][50]={"Available","Borrowed","N/A"};
Lib B[100];
#include "System.h"

int main ()
{

	u16 j=0,x=0;
	while (j!=7)
	{
		printf("\n1.add book details\n");
		printf("2.display the list of the books and its details\n");
		printf("3.borrow book\n");
		printf("4.delete book from the list\n");
		printf("5.Sell book and add to the list\n");
		printf("6.Return book\n");
		printf("7.exit program\n");
		printf("\nenter number\n ");
		scanf(" %d",&j);
		switch(j)
		{
			case 1 :
						AddBook(B);
						break;
			case 2 :
						DisplayList(B);
						break;
			case 3 :
						BorrowBook(B);
						break;
			case 4 :
						DeleteBook(B);
						break;
			case 5 :	
						SellBook(B);
						break;
			case 6 :  
						ReturnBook(B);
						break;
			case 7 :	
						break;
			default :	
						if(x<2)
						{
						printf("invalid number entered\n");
						printf("please enter number again\n");
						x++;
						}
						else
						{
							printf("Error\n");
							j=7;
						}
						break;
		}
	}
	
}