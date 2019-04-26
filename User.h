#pragma once

//Statement£º
void Register();
int Login();
int oneself(LstudentPtr sptr, int is_manager);


//Rigister 
void Register()
{
	system("cls");     // clear screen
	char name[name_max] = {0};
	char password[pass_max] = {0};
	printf("         ¡¾Regist ID¡¿input q to return   \n");
	printf("-----------------------------------------\n");
	while (1)
	{
		printf("Please input the username£º");
		fgets(name, name_max, stdin);
		char* find = strchr(name, '\n');      //Find line breaks
		if (find)                            //if find is not an empty point 
			*find = '\0';                    //then put an empty point in here
		rewind(stdin);                       //Clear keyboard buffer
		if (*name == '\0')		//user input 'enter'
		{
			continue;
		}
		if (strcmp(name, "q") == 0)		//quit
		{
			return;
		}
		if (user_exist(name) != NULL)	//duplicated username
		{
			printf("¡¾Duplicated username¡¿\n");
			printf("-----------------------------------------\n");
			continue;
		}
		break;
	}
	
	while (1)
	{
		printf("Please input the password£º");
		fgets(password, pass_max, stdin);
		char* find = strchr(password, '\n');      //Find line breaks
		if (find)                            //if find is not an empty point
			*find = '\0';                    //then put an empty point in here
		rewind(stdin);
		if (*password == '\0')
		{
			continue;
		}
		if (strcmp(password, "q") == 0)		//quit
		{
			return;
		}
		break;
	}
	LstudentPtr sptr = lshead_ptr;
	LstudentPtr s = (LstudentPtr)malloc(sizeof(Lstudent));
	memset(s, 0, sizeof(Lstudent));
	strcpy(s->data.username, name);
	strcpy(s->data.password, password);
	add_student_data(s);             //save data
	//Insert node
	if (sptr->next == NULL)
	{
		sptr->next = s;
		s->prev = sptr;
	}
	else
	{
		s->next = sptr->next;
		sptr->next->prev = s;
		sptr->next = s;
		s->prev = sptr;
	}
	printf("                Success to register\n");
	printf("-----------------------------------------\n");
}

//LOGIN
int Login()
{
	system("cls");
	char name[name_max] = { 0 };
	char password[pass_max] = { 0 };
	LstudentPtr active = NULL;
	printf("            ¡¾Login¡¿input q to return   \n");
	printf("-----------------------------------------\n");
	while (1)
	{
		printf("Please input the username£º");
		fgets(name, name_max, stdin);
		char* find = strchr(name, '\n');      //Find line breaks
		if (find)                            //if find is not an empty point
			*find = '\0';                    //then put an empty point in here
		rewind(stdin);
		if (*name == '\0')		
		{
			continue;
		}
		else if (strcmp(name, "q") == 0)		//quit
		{
			return 0;
		}
		if ((active = user_exist(name)) == NULL)	//duplicated username
		{
			printf("¡¾Username doesn't exist¡¿\n");
			printf("-----------------------------------------\n");
			continue;
		}
		break;
	}

	while (1)
	{
		printf("Please input the password£º");
		fgets(password, pass_max, stdin);
		char* find = strchr(password, '\n');      //Find line breaks
		if (find)                            //if find is not an empty point
			*find = '\0';                    //then put an empty point in here
		rewind(stdin);

		if (*password == '\0')
		{
			continue;
		}
		if (strcmp(password, "q") == 0)		//quit
		{
			return 0;
		}
		if (strcmp(password, active->data.password) == 0)
		{
			active_user = active;
			printf("             Welcome£¡%s\n", active->data.username);
			printf("-----------------------------------------\n");
			return 1;
		}
		else
		{
			printf("             ¡¾Password is wrong¡¿\n");
			printf("-----------------------------------------\n");
			break;
		}
	}
	return 0;
}

//Personal information inquiry
int oneself(LstudentPtr sptr, int is_manager)
{
	//TempPool pool;
	int dis_num = 4;	//How much displays each time 
	char ch = 'd';
	int i_d = -1;
	int i_a = -1;
	int num = 0;		//displaying number
	int page = 0;

	//
	do
	{
		if (ch == 'd' || ch == 'D')// turn right
		{
			if (i_d < borrow_max - 1)
			{
				system("cls");
				page++;
				i_a = i_d;
				if (is_manager)
				{
					printf("      ¡¾%s¡¿Input a,d to turn page q to quit   \n", sptr->data.username);
					printf("-----------------------------------------\n");
					printf("               Currently the %u page               \n", page);
					printf("-----------------------------------------\n");
				}
				else
				{
					printf("     ¡¾%s¡¿Input a,d to turn page q to quit \n", sptr->data.username);
					printf("-----------------------------------------\n");
					printf("               Currently the %u page          \n", page);
					printf("-----------------------------------------\n");
				}
				num = 0;
				while (i_d < borrow_max - 1)
				{
					i_d++;
					if (sptr->data.borrow[i_d] != 0)
					{
						LbookPtr b_ptr = tag_book(sptr->data.borrow[i_d]);
						if (b_ptr == NULL)
						{
							printf("¡¾There is a book with lost information that may have been deleted by the manager\n");
							printf("only tag£º%u\n borrowing information will be cleared\n", sptr->data.borrow[i_d]);
							sptr->data.borrow[i_d] = 0;
							mod_student_data(sptr);
							printf("-----------------------------------------\n");
						}
						else
						{
							printf("¡¶%s¡·\n author£º%s\nID£º%s\n¡¾only tag¡¿£º%u\n",
								b_ptr->data.name, b_ptr->data.author, b_ptr->data.bookId, b_ptr->data.ident);
							printf("-----------------------------------------\n");
							num++;
						}
					}
					if (num == dis_num)
					{
						break;
					}
				}
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (page > 1 && i_a > 0)
			{
				system("cls");
				page--;
				i_d = i_a;
				if (is_manager)
				{
					printf("      ¡¾%s¡¿Input a,d to turn page q to quit   \n", sptr->data.username);
					printf("-----------------------------------------\n");
					printf("               Currently the %u page             \n", page);
					printf("-----------------------------------------\n");
				}
				else
				{
					printf("   ¡¾%s¡¿Input a,d to turn page q to quit \n", sptr->data.username);
					printf("-----------------------------------------\n");
					printf("               Currently the %u page              \n", page);
					printf("-----------------------------------------\n");
				}
				num = 0;
				while (i_a >= 0)
				{
					if (sptr->data.borrow[i_a] != 0)
					{
						LbookPtr b_ptr = tag_book(sptr->data.borrow[i_a]);
						if (b_ptr == NULL)
						{
							printf("¡¾There is a book with lost information that may have been deleted by the manager¡¿\n");
							printf("only tag£º%u\n borrowing information will be cleared\n", sptr->data.borrow[i_a]);
							sptr->data.borrow[i_a] = 0;
							mod_student_data(sptr);
							printf("-----------------------------------------\n");
						}
						else
						{
							printf("¡¶%s¡·\n author£º%s\n ID£º%s\n¡¾only tag¡¿£º%u\n",
								b_ptr->data.name, b_ptr->data.author, b_ptr->data.bookId, b_ptr->data.ident);
							printf("-----------------------------------------\n");
							num++;
						}
					}
					i_a--;
					if (num == dis_num)
					{
						break;
					}
				}
			}
		}
		else if (ch == 'q' || ch == 'Q')
		{
			break;
		}
		else if ((ch == 'b' || ch == 'B') && !is_manager)
		{
			printf("Enter the only tag to return  book£º");
			size_t booktag;
			scanf("%u", &booktag);
			getchar();
			LbookPtr borrow = tag_book(booktag);
			if (borrow != NULL)
				return_book(sptr, borrow);
			else
			{
				printf("              This book does not exist\n");
				printf("-----------------------------------------\n");
			}
		}
		ch = getch();
	} while (1);
	return 1;
}
