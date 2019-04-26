#pragma once
//statement：
void add_book();
void del_book();
void mod_book();
void list_student();


//add book
void add_book()
{
	system("cls");
	char	 name[name_max] = {0};
	char	 author[name_max] = { 0 };
	char	 bookId[num_max] = { 0 };
	size_t	 count = 0;
	int		 tag1;
	printf("         【add book】input q to return   \n");
	printf("-----------------------------------------\n");
	rewind(stdin);
	while (1)
	{
		printf("Please input the title：");
		fgets(name, name_max, stdin);
		char* find = strchr(name, '\n');      //Find line breaks
		if (find)                            //if find is not an empty point
			*find = '\0';                    //then put an empty point in here
		rewind(stdin);

		if (*name == '\0')		//user input the enter
		{
			continue;
		}
		if (strcmp(name, "q") == 0)		//quit
		{
			return;
		}
		break;
	}
	while (1)
	{
		printf("Please input the author：");
		fgets(author, name_max, stdin);
		char* find = strchr(author, '\n');      
		if (find)                            
			*find = '\0';                   
		rewind(stdin);

		if (*author == '\0')		
		{
			continue;
		}
		if (strcmp(author, "q") == 0)		
		{
			return;
		}
		break;
	}
	while (1)
	{
		printf("Please input ID：");
		fgets(bookId, num_max, stdin);
		char* find = strchr(bookId, '\n');      
		if (find)                            
			*find = '\0';                    
		rewind(stdin);

		if (*bookId == '\0')		
		{
			continue;
		}
		if (strcmp(bookId, "q") == 0)	
		{
			return;
		}
		break;
	}
	printf("Please input inventory：");
	scanf("%u", &count);
	rewind(stdin);
	tag1 = get_tag();
	
	LbookPtr bptr = lbhead_ptr;
	LbookPtr b = (LbookPtr)malloc(sizeof(Lbook));
	memset(b, 0, sizeof(Lbook));

	strcpy(b->data.name, name);
	strcpy(b->data.author, author);
	strcpy(b->data.bookId, bookId);
	b->data.count = count;
	b->data.ident = tag1;

	
	if (bptr->next == NULL)
	{
		bptr->next = b;
		b->prev = bptr;
	}
	else
	{
		b->next = bptr->next;
		bptr->next->prev = b;
		bptr->next = b;
		b->prev = bptr;
	}
	book_count++;
	add_book_data(b);
	printf("       【Succeed to add】only tag：%u   \n", tag1);
	printf("-----------------------------------------\n");
	return;
}

//delete books
void del_book()
{
	system("cls");
	int tag1;
	LbookPtr bptr = NULL;
	char ch = '0';
	printf("               【delete books】   \n");
	printf("-----------------------------------------\n");
	while (1)
	{
		printf("Please input the only tag of book：");
		scanf("%u", &tag1);
		bptr = tag_book(tag1);
		if (bptr == NULL)
		{
			printf("【This only tag doesn't exist】\n");
			break;
		}
		else
		{
			printf("-----------------------------------------\n");
			printf("《%s》\n author：%s\nID：%s\n inventory：%u\n",
				bptr->data.name, bptr->data.author, bptr->data.bookId, bptr->data.count);
			printf("-----------------------------------------\n");
			printf("【Whether need to delete y/n】：\n");
			ch = getch();
			while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
				ch = getch();
			if (ch == 'y' || ch == 'N')
			{
				if (bptr->next != NULL)
				{
					bptr->prev->next = bptr->next;
					bptr->next->prev = bptr->prev;
					//1.该结点的前一个的next指向该节点的下一个，即把上一个结点与下一个结点连接起来
					//2.该节点的下一个的prev指向该节点的上一个
				}
				else
				{
					bptr->prev->next = NULL;
				}
				free(bptr);
				book_count--;
				save_book_data();
				printf("              【Succeed to delete】\n");
				printf("-----------------------------------------\n");
				break;
			}
			else
			{
				printf("              【Cancel to delete】\n");
				printf("-----------------------------------------\n");
				break;
			}
		}
	}
}

//modify book information
void mod_book()
{
	system("cls");
	int tag1;
	LbookPtr bptr = NULL;
	char ch = '0';
	printf("            【modify book information】   \n");
	printf("-----------------------------------------\n");
	while (1)
	{
		printf("Please input the only tag of book：");
		scanf("%u", &tag1);
		rewind(stdin);
		bptr = tag_book(tag1);
		if (bptr == NULL)
		{
			printf("【This only tag doesn't exist】\n");
			break;
		}
		else
		{
			printf("-----------------------------------------\n");
			printf("《%s》\n author：%s\nID：%s\n inventory：%u\n",
				bptr->data.name, bptr->data.author, bptr->data.bookId, bptr->data.count);
			printf("-----------------------------------------\n");
			printf("1.title    2.author   3.ID  4.inventory   q. quit\n");
			printf("【Please input what you want to modify】：\n");
			ch = getch();
			while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != 'q')
				ch = getch();
			if (ch == '1')
			{
				char name[name_max] = { 0 };
				printf("【Please input the new title】：");
				fgets(name, name_max, stdin);
				char* find = strchr(name, '\n');      
				if (find)                            
					*find = '\0';                   
				rewind(stdin);

				strcpy(bptr->data.name, name);
				mod_book_data(bptr);
				printf("               【Modify finish】\n");
				printf("-----------------------------------------\n");
			}
			else if (ch == '2')
			{
				char author[name_max] = { 0 };
				printf("【Please input the new author】：");
				fgets(author, name_max, stdin);
				char* find = strchr(author, '\n');      
				if (find)                            
					*find = '\0';                   
				rewind(stdin);

				strcpy(bptr->data.author, author);
				mod_book_data(bptr);
				printf("               【Modify finish】\n");
				printf("-----------------------------------------\n");
			}
			else if(ch == '3')
			{
				char bookId[num_max] = { 0 };
				printf("【Please input the new ID】：");
				fgets(bookId, name_max, stdin);
				char* find = strchr(bookId, '\n');      
				if (find)                           
					*find = '\0';                    
				rewind(stdin);

				strcpy(bptr->data.bookId, bookId);
				mod_book_data(bptr);
				printf("               【Modify finish】\n");
				printf("-----------------------------------------\n");
			}
			else if (ch == '4')
			{
				size_t count = 0;
				printf("【Please input the new inventory】：");
				scanf("%u", &count);
				rewind(stdin);
				bptr->data.count = count;
				mod_book_data(bptr);
				printf("               【Modify finish】\n");
				printf("-----------------------------------------\n");
			}
			else
			{
				printf("               【quit modification】\n");
				printf("-----------------------------------------\n");
			}
			break;
		}
	}
}

//List all the users
void list_student()
{
	system("cls");
	printf("       Currently no registered users.，input q to quit       \n");
	printf("-----------------------------------------\n");
	char		name[name_max] = { 0 };
	LstudentPtr sptr = lshead_ptr;
	LstudentPtr sptr2 = lshead_ptr;
	size_t		dis_num = 4;			//num of people display each time
	size_t		num = 0;				//num has been dispalyed
	char ch = 'd';
	size_t		page = 0;
	do
	{
		if (ch == 'd' || ch == 'D')
		{
			if (sptr->next != NULL)
			{
				system("cls");
				sptr2 = sptr;
				page++;
				num = 0;
				printf("All registered users：input a,d turn page,q to quit,b Details\n");
				printf("-----------------------------------------\n");
				printf("              Currently is %u page               \n", page);
				printf("-----------------------------------------\n");
				while (sptr->next != NULL && num < dis_num)
				{
					sptr = sptr->next;
					printf("User：%s\n", sptr->data.username);
					printf("Borrowing information【唯一标识码】：");
					for (int i = 0; i < borrow_max; i++)
					{
						if (sptr->data.borrow[i] != 0)
						{
							printf("%u  ", sptr->data.borrow[i]);
						}
					}
					printf("\n");
					printf("-----------------------------------------\n");
					num++;
				}
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (sptr2->prev != NULL && page > 1)
			{
				system("cls");
				sptr = sptr2;
				page--;
				num = 0;
				printf("All registered users：input a,d turn page,q to quit,b Details\n");
				printf("-----------------------------------------\n");
				printf("              Currently is %u page               \n", page);
				printf("-----------------------------------------\n");
				while (sptr2->prev != NULL && num < dis_num)
				{
					sptr2 = sptr2->prev;
					printf("User：%s\n", sptr2->data.username);
					printf("Borrowing information【Only tag】：");
					for (int i = 0; i < borrow_max; i++)
					{
						if (sptr2->data.borrow[i] != 0)
						{
							printf("%u  ", sptr2->data.borrow[i]);
						}
					}
					printf("\n");
					printf("-----------------------------------------\n");
					num++;
				}
			}
		}
		else if (ch == 'b' || ch == 'B')
		{
			printf("Input username to check the detail information：");
			fgets(name, name_max, stdin);
			char* find = strchr(name, '\n');     
			if (find)                            
				*find = '\0';                    
			rewind(stdin);

			LstudentPtr s = user_exist(name);
			oneself(s, 1);						
		}
		else if (ch == 'q' || ch == 'Q')
		{
			printf("             Quit\n");
			printf("-----------------------------------------\n");
			break;
		}
		ch = getch();
	} while (1);
}

//List all books and books information to call find_all_book of Study.h
