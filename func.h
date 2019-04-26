#pragma once

//Statement£º
void save_book_data();
void add_book_data(LbookPtr b_ptr);
void add_student_data(LstudentPtr s_ptr);
void mod_student_data(LstudentPtr sptr);
void mod_book_data(LbookPtr bptr);
void read_book_data();
void read_student_data();
void manager();
void init_data();
LstudentPtr user_exist(const char* name);
size_t get_tag();
LbookPtr tag_book(size_t i);
void free_source();


//Definition

//save all data of books
void save_book_data()
{
	FILE* fd = fopen("book.data", "wb");
	if (fd == NULL)
	{
		exit(1);
	}
	LbookPtr b_ptr = lbhead_ptr;
	while (b_ptr->next != NULL)
	{
		b_ptr = b_ptr->next;
		fwrite(&b_ptr->data, sizeof(Book), 1, fd);
	}
	fclose(fd);
	return;

}

//Add book data (use append to add information at the end)
void add_book_data(LbookPtr b_ptr)
{
	FILE* fd = fopen("book.data", "ab");
	if (fd == NULL)
	{
		fd = fopen("book.data", "wb");
	}
	fwrite(&b_ptr->data, sizeof(Book), 1, fd);
	fclose(fd);
}

//add user data
void add_student_data(LstudentPtr s_ptr)
{
	FILE* fd = fopen("student.data", "ab");
	if (fd == NULL)
	{
		fd = fopen("student.data", "wb");
	}
	fwrite(&s_ptr->data, sizeof(Student), 1, fd);
	fclose(fd);
}

//Modify user data (use read and write to open and then modify the data in the middle)
void mod_student_data(LstudentPtr sptr)
{
	FILE* fp = fopen("student.data", "r+");
	if (fp == NULL)
	{
		return;
	}
	LstudentPtr s = (LstudentPtr)malloc(sizeof(Lstudent));
	memset(s, 0, sizeof(Lstudent));
	int size = sizeof(Student);
	while (fread(&s->data, size, 1, fp) == 1)//fread returns the read count(1)
	{
		if (strcmp(s->data.username, sptr->data.username) == 0)
		{
			fseek(fp, -size, SEEK_CUR);//File pointer back a distance of data
			fwrite(&sptr->data, size, 1, fp);
			break;
		}
	}
	fclose(fp);
}

//modify book data
void mod_book_data(LbookPtr bptr)
{
	FILE* fp = fopen("book.data", "r+");
	if (fp == NULL)
	{
		return;
	}
	LbookPtr b = (LbookPtr)malloc(sizeof(Lbook));
	memset(b, 0, sizeof(Lbook));
	int size = sizeof(Book);
	while (fread(&b->data, size, 1, fp) == 1)//fread returns the read count(1)
	{
		if (b->data.ident == bptr->data.ident)
		{
			fseek(fp, -size, SEEK_CUR);//File pointer back a distance of data
			fwrite(&bptr->data, size, 1, fp);
			break;
		}
	}
	fclose(fp);
}

//read book data
void read_book_data()
{
	FILE* fd = fopen("book.data", "rb");
	if (fd == NULL)
	{
		fd = fopen("book.data", "wb");
		fclose(fd);
		return;
	}
	LbookPtr b_ptr = lbhead_ptr;
	LbookPtr b = NULL;
	register int size = sizeof(Lbook);
	int size_book = sizeof(Book);
	while (!feof(fd))
	{
		b = (LbookPtr)malloc(size);
		memset(b, 0, size);
		fread(&b->data, size_book, 1, fd);
		if (!feof(fd) && *b->data.name != '\0')
		{
			b_ptr->next = b;
			b->prev = b_ptr;
			b_ptr = b;
			book_count++;
		}
		else
		{
			free(b);
		}
	}
	fclose(fd);
}

//read user data
void read_student_data()
{
	FILE* fd = fopen("student.data", "rb");
	if (fd == NULL)
	{
		fd = fopen("student.data", "wb");
		fclose(fd);
		return;
	}
	LstudentPtr s_ptr = lshead_ptr;
	LstudentPtr s = NULL;
	register int size = sizeof(Lstudent);
	int size_student = sizeof(Student);

	while (!feof(fd))
	{
		s = (LstudentPtr)malloc(size);
		memset(s, 0, size);
		fread(&s->data, size_student, 1, fd);
		if (!feof(fd))
		{
			s_ptr->next = s;
			s->prev = s_ptr;
			s_ptr = s;
		}
		else
		{
			free(s);
		}
	}
	fclose(fd);
}

//Add an administrator (only useful when opening the system for the first time)
void manager()
{
	if (lshead_ptr->next == NULL)
	{
		char name[name_max] = { 0 };
		char password[pass_max] = { 0 };
		LstudentPtr manager = (LstudentPtr)malloc(sizeof(Lstudent));
		memset(manager, 0, sizeof(Lstudent));
		printf("       Welcome to use this library management system for the first time.\n");
		printf("-----------------------------------------\n");
		printf("  Next you will register as an administrator user for this system. \n");
		while (1)
		{
			printf("Please input the username£º");
			fgets(name, name_max, stdin);
			char* find = strchr(name, '\n');      //Find line breaks
			if (find)                            //if find is not an empty point
				*find = '\0';                    //then put an empty point in here
			rewind(stdin);
			if (*name == '\0')		//user input 'enter'
			{
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
			break;
		}
		strcpy(manager->data.username, name);
		strcpy(manager->data.password, password);
		lshead_ptr->next = manager;
		manager->prev = lshead_ptr;
		add_student_data(manager);
		printf("¡¾registration success! Please remember the username and password¡¿\n%s  %s\n", manager->data.username, manager->data.password);
		printf("-----------------------------------------\n");
	}
	return;
}

//Data initialization (called when the program is opened)
void init_data()
{
	lshead_ptr = (LstudentPtr)malloc(sizeof(Lstudent));
	memset(lshead_ptr, 0, sizeof(Lstudent));

	lbhead_ptr = (LbookPtr)malloc(sizeof(Lbook));
	memset(lbhead_ptr, 0, sizeof(Lbook));

	read_student_data();
	read_book_data();

	manager();

	strcpy(manager_name, lshead_ptr->next->data.username);//Assign the administrator name to it
	/*The program is the first time to register the administrator, so the administrator is the second node.
	 Although the student registration uses the head insertion method,
	  the data is still stored at the very end after registration.*/
}

//Determine if the username exists
LstudentPtr user_exist(const char* name)
{
	LstudentPtr sptr = lshead_ptr;
	while (sptr->next != NULL)
	{
		sptr = sptr->next;
		if (strcmp(sptr->data.username, name) == 0)
		{
			return sptr;
		}
	}
	return NULL;
}

//get an only tag
size_t get_tag()
{
	size_t tag1 = 0;
	FILE* fd = fopen("tag", "rb");
	if (fd == NULL)
	{
		FILE* fd = fopen("tag", "wb");
		LbookPtr bptr = lbhead_ptr;
		while (1)
		{
			//If it is opened for the first time, then tag1 = 1, if not, it may be that the tag file was accidentally deleted.
			//So use a means of giving up part of the number to get a unique number.
			tag1 = tag1 + book_count + 1;
			
			while (bptr->next != NULL)
			{
				bptr = bptr->next;
				if (tag1 == bptr->data.ident)
				{
					continue;
				}
			}
			if (tag1 > 0xffff0000)
			
			{
				tag1 = 0;
				fwrite(&tag1, sizeof(size_t), 1, fd);
				fclose(fd);
				return tag1;
			}
			fwrite(&tag1, sizeof(size_t), 1, fd);
			fclose(fd);
			return tag1;
		}
	}
	else
	{
		fread(&tag1, sizeof(size_t), 1, fd);
		if (tag1 == 0)
		{
			fclose(fd);
			return tag1;
		}
		else
		{
			tag1 = tag1 + 1;
			fclose(fd);
			fd = fopen("tag", "wb");
			fwrite(&tag1, sizeof(size_t), 1, fd);
			fclose(fd);
			return tag1;
		}
	}
}

//return corresponding book through the only tag
LbookPtr tag_book(size_t i)
{
	LbookPtr lb_ptr = lbhead_ptr;
	while (lb_ptr->next != NULL)
	{
		lb_ptr = lb_ptr->next;
		if (i == lb_ptr->data.ident)
		{
			return lb_ptr;
		}
	}
	return NULL;
}

//release the source
void free_source()
{
	LstudentPtr sptr = lshead_ptr;
	LstudentPtr sptr_temp = lshead_ptr;
	LbookPtr bptr = lbhead_ptr;
	LbookPtr bptr_temp = lbhead_ptr;
	while (sptr->next != NULL)
	{
		sptr_temp = sptr;
		sptr = sptr->next;
		free(sptr_temp);
	}
	free(sptr);
	while (bptr->next != NULL)
	{
		bptr_temp = bptr;
		bptr = bptr->next;
		free(bptr_temp);
	}
	free(bptr);
}
