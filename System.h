void AddBook();
void DisplayList();
void BorrowBook();
void ReturnBook();
void DeleteBook();
void SellBook();
void AddCopies(u8 Copies,u8 *Name,u8 MoreCopies);
s16 SearchBook(u8 *Name);
u8 EmptyIndex();
u8 SearchStatus (u8 Copies,u8 *Name, s16*count,u8 BookStatus);
void RemoveCopy(u8 Copies,u8 *Name);


void AddBook()
{
	u8 Name[50];
	s16 index=0,i=0,Local_Empty=0;
	u8 MoreCopies=0;
	
	if (size < LibLimit)
	{
		printf("enter the book name\n");
		scanf("%s",Name);
		index = SearchBook(Name);
		if(index==-1)
		{
			index=EmptyIndex();
			printf("now you can add details of new book\n");
			strcpy(B[index].Name,Name);
			printf("enter author name\n");
			scanf("%s",B[index].AuthorN);
			printf("enter publication year\n");
			scanf("%d",&B[index].PubY);
			printf("enter price of the book\n");
			scanf("%f",&B[index].Price);
			printf("enter number of copies\n");
			scanf("%d",&B[index].NC);
			if(size+B[index].NC>LibLimit)
			{
				printf("Copies is More than Size\n");
				printf("remaining spaces in library is %d\n",LibLimit-size);
				B[index].Name[0]='\0';
				return;
			}
			B[index].Status=Available;
			size++;
			if(B[index].NC>1)
			{
				while(i<B[index].NC-1)
				{

					Local_Empty=EmptyIndex();
					strcpy(B[Local_Empty].Name,Name);
					strcpy(B[Local_Empty].AuthorN,B[index].AuthorN);
					B[Local_Empty].PubY=B[index].PubY;
					B[Local_Empty].Price=B[index].Price;
					B[Local_Empty].NC=B[index].NC;
					B[Local_Empty].Status=Available;
					size++;
					i++;
				}
			}
			printf("\nThe Book Now is Added\n");
		}
		else
		{
			printf("\nThe Book is found\n");
			printf("enter number of copies\n");
			scanf("%d",&MoreCopies);
			if(size+MoreCopies<LibLimit)
			{
				AddCopies(B[index].NC,B[index].Name,MoreCopies);	
				while(i<MoreCopies)
				{

					Local_Empty=EmptyIndex();
					strcpy(B[Local_Empty].Name,B[index].Name);
					strcpy(B[Local_Empty].AuthorN,B[index].AuthorN);
					B[Local_Empty].PubY=B[index].PubY;
					B[Local_Empty].Price=B[index].Price;
					B[Local_Empty].NC=B[index].NC;
					B[Local_Empty].Status=Available;
					size++;
					i++;
				}
				printf("\nThe Copies is Added\n");
			}
			else
			{
				printf("Copies is More than Size\n");
				printf("remaining spaces in library is %d\n",LibLimit-size);
				return;
			}
		}
	}
	else
	{
		printf("you have reached the limit of library\n");
	}
}
void DisplayList()
{
	
	u16 i=0;
	u16 j=0,CurrentNumOfBooks=0;
	u8 found=0;
	printf(" \nYou can view the list of books\n");  
	if (size==0)
	{
		printf("there is no book in library\n");
	}
	else if (size>0)
	{
		printf(" \nThe list of books are: ");
		while(CurrentNumOfBooks<size && i<LibLimit)
		{
			if(B[i].Name[0]!='\0')
			{	
				CurrentNumOfBooks++;
				found=0;
				j=0;
				
				while(j<i)
				{
					if(B[j].Name[0]!='\0')
					{
						if(strcmp(B[i].Name, B[j].Name) == 0)
						{
							found = 1;
							break;
						}
					}
					j++;
				}
				if(found==1)
				{
					i++;
					continue;
				}
				printf("\nThe name of the book is: %s\n",B[i].Name);  
				printf("\nThe name of the author is: %s\n",B[i].AuthorN);  
				printf("\nThe publication Year is: %d\n",B[i].PubY);  
				printf("\nThe cost of the book is: %.2f\n",B[i].Price);
				printf("\nnumber of copies founded is: %d\n",B[i].NC);
				printf("\nBook Status is : %s\n",Status[SearchStatus(B[i].NC,B[i].Name,NULL,Available)]);
			}
			i++;
		}
	}
}
void BorrowBook()
{
	u8 Name[50];
	s16 index=0;
	if(size>0)
	{
		printf("enter the book name\n");
		scanf("%s",&Name);
		index = SearchBook(Name);

		if(index !=-1)
		{
			if(SearchStatus(B[index].NC,Name,&index,Available)==Available)
			{
				B[index].Status=Borrowed;
				printf("\nThe book now is Borrowed\n");
			}
		}
		else
		{
			printf("\nthe book is not found\n");
		}
	}
}
void ReturnBook()
{
	u8 Name[50];
	s16 index=0;
	if(size>0)
	{
		printf("enter the book name\n");
		scanf("%s",&Name);
		index = SearchBook(Name);
		if(index !=-1)
		{
			if(SearchStatus(B[index].NC,Name,&index,Borrowed)==Borrowed)
			{
				B[index].Status=Available;
				printf("\nThe book now is returned\n");
			}
		}
		else
		{
			printf("\nthe book is not found\n");
		}
	}
}
void DeleteBook()
{
	u8 Name[50];
	s16 index=0;
	if(size>0)
	{
		printf("enter the book name\n");
		scanf("%s",&Name);
		index = SearchBook(Name);
		if(index==-1)
		{
			printf("the book is not found\n");
			return;
		}
		while(index !=-1)
		{
			B[index].Name[0]='\0';
			size--;
			index = SearchBook(Name);
			printf("\nThe book now is Deleted\n");
		}
	}
}
void SellBook()
{
	u8 Name[50];
	s16 index=0;
	if(size>0)
	{
		printf("enter the book name\n");
		scanf("%s",&Name);
		index = SearchBook(Name);
		if(index==-1)
		{
			printf("the book is not found\n");
			return;
		}
		else
		{
			if(SearchStatus(B[index].NC,Name,&index,Available)==Available)
			{
				B[index].Status=NA;
				RemoveCopy(B[index].NC,Name);
				printf("\nThe book now is Selled\n");
			}
			size--;
		}
	}	
}
s16 SearchBook(u8 *Name)
{
	u16 i=0;
	s16 index=0;
	while(i<size)
	{
		if(B[index].Name[0]!='\0')
		{
			if(strcmp(Name,B[index].Name)==0)
			{
				return index;
			}
			i++;
		}
		index++;
	}
	
	return -1;
}
u8 EmptyIndex()
{
	u8 count=0;
	while(count<size)
	{
		if(B[count].Name[0]=='\0')
		{
			return count;
		}
		count++;
	}
		return count;
}
u8 SearchStatus (u8 Copies,u8 *Name, s16*count,u8 BookStatus)
{
	u8 Local_Status=NA;
	s16 index=0;
	u8 bookCopies = 0;
	while(bookCopies<Copies)
	{
		if(strcmp(B[index].Name,Name)==0)
		{
			if(B[index].Status<Local_Status){
				Local_Status = B[index].Status;
				if(Local_Status == BookStatus)
				{
					if(count != NULL)
						*count=index;
					return Local_Status;
				}
			}
			bookCopies++;
		}
		index++;
	}
	return Local_Status;
}
void RemoveCopy(u8 Copies,u8 *Name)
{
	s16 index=0;
	u8 bookCopies = 0;
	while(bookCopies<Copies)
	{
		if(strcmp(B[index].Name,Name)==0)
		{
			B[index].NC--;
			bookCopies++;
		}
		index++;
	}
}
void AddCopies(u8 Copies,u8 *Name,u8 MoreCopies)
{
	s16 index=0;
	u8 bookCopies = 0;
	while(bookCopies<Copies)
	{
		if(strcmp(B[index].Name,Name)==0)
		{
			B[index].NC=B[index].NC+MoreCopies;
			bookCopies++;
		}
		index++;
	}
}