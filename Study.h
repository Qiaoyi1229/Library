#pragma once

//Statement：
static int borrow_book(LstudentPtr sptr, LbookPtr bptr);
static int return_book(LstudentPtr sptr, LbookPtr bptr);
int find_all_book();
int find_a_book();



//borrow
static int borrow_book(LstudentPtr sptr, LbookPtr bptr)
{
	//system("cls");
	printf("+          in the process of borrowing books for you.        +\n");
	printf("-----------------------------------------\n");
	int i = 0;
	while (sptr->data.borrow[i] != 0 && i < borrow_max)//get an empty place
	{
		i++;
	}
	if (i == borrow_max)
	{
		printf("+              You have reached the limit of borrowing         +\n");
		printf("-----------------------------------------\n");
		return error;
	}
	else
	{
		if (bptr->data.count > 0)
		{
			sptr->data.borrow[i] = bptr->data.ident;
			bptr->data.count -= 1;
			printf("You  succeed to borrow a book：《%s》\n", bptr->data.name);
			printf("-----------------------------------------\n");
			mod_student_data(active_user);
			mod_book_data(bptr);

			return ok;
		}
		else
		{
			printf("+              This book is no longer in stock             +\n");
			printf("-----------------------------------------\n");
			return error;
		}
	}
}

//return
static int return_book(LstudentPtr sptr, LbookPtr bptr)
{
	//system("cls");
	printf("+           in the process of returning books for you.        +\n");
	printf("-----------------------------------------\n");
	int i = 0;
	while (i < borrow_max)
	{
		if (sptr->data.borrow[i] == bptr->data.ident)
		{
			sptr->data.borrow[i] = 0;
			bptr->data.count += 1;
			printf("You  succeed to return a book：《%s》\n", bptr->data.name);
			printf("-----------------------------------------\n");
			mod_student_data(active_user);
			mod_book_data(bptr);
			return ok;
		}
		i++;
	}
	printf("+            You don't seem to borrow this book.         +\n");
	printf("-----------------------------------------\n");
	return error;
}

//find all books
int find_all_book()
{
	system("cls");
	printf("         Library is empty，input q to quit       \n");
	printf("-----------------------------------------\n");

	LbookPtr b_ptr = lbhead_ptr;	//pointer of adding pages
	LbookPtr b_ptr2 = lbhead_ptr;   //pointer of reducing pages
	size_t dis_num = 4;			//the num of book dispaly one time
	size_t book_num = 0;		//current num of book
	size_t page = 0;			//page 
	size_t total =  (book_count % dis_num) == 0 ? (book_count / dis_num) : (book_count / dis_num) + 1;//total page
	//这里是一个x == 0？x : y的运算符，主要用于总页数的判断如：10（总）/4（显示） = 2页是不对的，应该是3页
	char ch = 'd';
	do
	{
		if (ch == 'd' || ch == 'D')//turn right
		{
			if (page < total)
			{
				page++;	
				b_ptr2 = b_ptr;	//Assign the old b_ptr to b_ptr2
				system("cls");
				printf(" all books：inputa,d turn page,q quit,b borrow \n");
				printf("-----------------------------------------\n");
				printf("           Currently %u page，total %u page          \n", page, total);
				printf("-----------------------------------------\n");
				for (size_t i = 0; i < dis_num; i++)
				{
					if (b_ptr->next != NULL)
					{
						b_ptr = b_ptr->next;
						printf("《%s》\n author：%s\nID：%s\n inventory：%u\n【only tag】：%u\n",
							b_ptr->data.name, b_ptr->data.author, b_ptr->data.bookId, b_ptr->data.count, b_ptr->data.ident);
						printf("-----------------------------------------\n");
					}
				}
				if (b_ptr->next == NULL)
				{
					printf("         There are %u books in the library   \n", book_count);
					printf("-----------------------------------------\n");
				}
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (page > 1)
			{
				page--;	//减少1页
				b_ptr = b_ptr2;
				system("cls");
				printf(" all books：inputa,d turn page,q quit,b borrow \n");
				printf("-----------------------------------------\n");
				printf("           Currently %u page，total %u page          \n", page, total);
				printf("-----------------------------------------\n");
				for (size_t i = 0; i < dis_num; i++)
				{
					if (b_ptr2->prev != NULL)
					{
						printf("《%s》\n author：%s\nID：%s\n inventory：%u\n【only tag】：%u\n",
							b_ptr2->data.name, b_ptr2->data.author, b_ptr2->data.bookId, b_ptr2->data.count, b_ptr2->data.ident);
						printf("-----------------------------------------\n");
						b_ptr2 = b_ptr2->prev;
						book_num--;
					}
				}
			}
		}
		else if (ch == 'q' || ch == 'Q')
		{
			break;
		}
		else if (ch == 'b' || ch == 'B')
		{
			printf("Input the only tag to borrow book：");
			size_t booktag;
			scanf("%u", &booktag);
			getchar();
			LbookPtr borrow = tag_book(booktag);
			if(borrow != NULL)
				borrow_book(active_user, borrow);
			else
			{
				printf("              This book does not exist\n");
				printf("-----------------------------------------\n");
			}
		}
		ch = getch();
		//if (ch == '\0')
		//	ch = getch();
	} while (1);
	return 1;
}
//find a book
int find_a_book()
{
	
	printf("                Query book\n");
	printf("-----------------------------------------\n");
	printf("Please input the title，author or ID：");
	char buf[name_max] = {0};
	fgets(buf, name_max, stdin);
	char* find = strchr(buf, '\n');      
	if (find)                            
		*find = '\0';                   
	rewind(stdin);


	LbookPtr b_ptr = lbhead_ptr;	
	LbookPtr b_ptr2 = lbhead_ptr;   
	int dis_num = 4;	
	int page = 0;		
	int i = 0;
	char ch = 'd';
	do
	{
		if (ch == 'd' || ch == 'D')//turn right
		{
			i = 0;
			if (b_ptr->next != NULL)
			{
				b_ptr2 = b_ptr;
				system("cls");
				page++;
				printf("   all books：input a,d turn page,q quit,b borrow \n", buf);
				printf("-----------------------------------------\n");
				printf("                Currently %u page，total %u page            \n", page);
				printf("-----------------------------------------\n");
				while (i < dis_num && b_ptr->next != NULL)
				{
					b_ptr = b_ptr->next;
					if (strcmp(b_ptr->data.name, buf) == 0 || strcmp(b_ptr->data.author, buf) == 0 ||
						strcmp(b_ptr->data.bookId, buf) == 0)
					{
						printf("《%s》\n author：%s\nID：%s\n inventory：%u\n【only tag】：%u\n",
							b_ptr->data.name, b_ptr->data.author, b_ptr->data.bookId, b_ptr->data.count, b_ptr->data.ident);
						printf("-----------------------------------------\n");
						i++;
					}
				}
				if (b_ptr->next == NULL)
				{
					printf("                the last page   \n");
					printf("-----------------------------------------\n");
				}
			}
			if (book_count <= 0)
			{
				printf("          There is no book in the library     \n");
				printf("-----------------------------------------\n");
				break;
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			i = 0;
			if (b_ptr2->prev != NULL && page > 1)
			{
				b_ptr = b_ptr2;
				system("cls");
				page--;
				printf("   【%s】inputa,d turn page,q quit,b borrow \n", buf);
				printf("-----------------------------------------\n");
				printf("               Currently %u page              \n", page);
				printf("-----------------------------------------\n");
				while (i < dis_num && b_ptr2->prev != NULL)
				{
					if (strcmp(b_ptr2->data.name, buf) == 0 || strcmp(b_ptr2->data.author, buf) == 0 ||
						strcmp(b_ptr2->data.bookId, buf) == 0)
					{
						printf("《%s》\n author：%s\nID：%s\n inventory：%u\n【only tag】：%u\n",
							b_ptr2->data.name, b_ptr2->data.author, b_ptr2->data.bookId, b_ptr2->data.count, b_ptr2->data.ident);
						printf("-----------------------------------------\n");
						i++;
					}
					b_ptr2 = b_ptr2->prev;
				}
			}
		}
		else if (ch == 'q' || ch == 'Q')
		{
			break;
		}
		else if (ch == 'b' || ch == 'B')
		{
			printf("Input the only tag to borrow book：");
			size_t booktag;
			scanf("%u", &booktag);
			getchar();
			LbookPtr borrow = tag_book(booktag);
			if (borrow != NULL)
				borrow_book(active_user, borrow);
			else
			{
				printf("         This book does not exist\n");
				printf("-----------------------------------------\n");
			}
		}
		ch = getch();
		//if(ch == '\0')
		//	ch = getch();
	} while (1);
	return 1;
}
