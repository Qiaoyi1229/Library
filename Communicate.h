#pragma once
//Statement£º
void communicate();
void add_Invitation(LstudentPtr sptr);
void shield_Invitation();
void clear_Invitation();
void forum(LstudentPtr sptr);



//Communicate Area
void communicate()
{
	system("cls");
	printf("         ¡¾Library Forum¡¿q return\n");
	printf("-----------------------------------------\n");

	int size = sizeof(Invitation);
	Invitation* iptr = (Invitation*)malloc(size);
	memset(iptr, 0, size);
	FILE* fp = fopen("invitation.data", "rb");
	if (fp == NULL)
	{
		fp = fopen("invitation.data", "wb");
		fclose(fp);
		fp = fopen("invitation.data", "rb");
	}
	size_t page = 0;			//page
	size_t dis_num = 4;			//display number
	size_t num = 0;				//Number already displayed
	char ch = 'd';

	do
	{
		if (ch == 'd' || ch == 'D')//turn right
		{
			if (!feof(fp))
			{
				system("cls");
				page++;
				num = 0;
				printf("          ¡¾Library Forum¡¿q return\n");
				printf("-----------------------------------------\n");
				printf("               Currently %upage\n", page);
				printf("-----------------------------------------\n");
				while (fread(iptr, size, 1, fp) == 1 && num < 4)
				{
					if (*iptr->content == '\0')
					{
						continue;
					}
					printf("Username£º%s NO.£º%u\nContent£º%s\n", iptr->name, iptr->no, iptr->content);
					num++;
					printf("-----------------------------------------\n");
				}
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (page > 1)
			{
				system("cls");
				page--;
				num = 0;
				printf("          ¡¾Library Forum¡¿q return\n");
				printf("-----------------------------------------\n");
				printf("               Currently %upage\n", page);
				printf("-----------------------------------------\n");
				if (page == 1)
				{
					fseek(fp, 0, SEEK_SET); //Move the pointer to the first place
					while (fread(iptr, size, 1, fp) == 1 && num < 4)
					{
						if (*iptr->content == '\0')
						{
							continue;
						}
						printf("Username£º%s NO.£º%u\nContent£º%s\n", iptr->name, iptr->no, iptr->content);
						num++;
						printf("-----------------------------------------\n");
					}
				}
				else
				{
					fseek(fp, -(size * ((int)dis_num*2)), SEEK_CUR); //Move the pointer to the target
					while (fread(iptr, size, 1, fp) == 1 && num < 4)
					{
						if (*iptr->content == '\0')
						{
							continue;
						}
						printf("Username£º%s NO.£º%u\nContent£º%s\n", iptr->name, iptr->no, iptr->content);
						num++;
						printf("-----------------------------------------\n");
					}
				}
			}
		}
		else if (ch == 'q' || ch == 'Q')
		{
			printf("              You have left the forum\n");
			printf("-----------------------------------------\n");
			break;
		}
		ch = getch();
	} while (1);
	fclose(fp);
	free(iptr);
}

//Add invitation
void add_Invitation(LstudentPtr sptr)
{
	system("cls");
	int size = sizeof(Invitation);
	Invitation* iptr = (Invitation*)malloc(size);
	memset(iptr, 0, size);
	FILE* fp = fopen("invitation.data", "a");
	if (fp == NULL)
	{
		return;
	}
	printf("           ¡¾Post an invitation¡¿q return\n");
	printf("-----------------------------------------\n");

	printf("ÊäÈëÄÚÈÝ£º");
	fgets(iptr->content, content_max, stdin);
	char* find = strchr(iptr->content, '\n');      //Find line breaks
	if (find)                            //if find is not an empty point
		*find = '\0';                    //then put an empty point in here
	rewind(stdin);
	if (*iptr->content == '\0' || strcmp(iptr->content, "q") == 0)
	{
		free(iptr);
		fclose(fp);
		printf("                Fail to post\n");
		printf("-----------------------------------------\n");
		return;
	}
	strcpy(iptr->name, sptr->data.username);
	iptr->no = get_tag();
	fwrite(iptr, size, 1, fp);
	fclose(fp);
	printf("                Succeed to post\n");
	printf("-----------------------------------------\n");
}

//shield
void shield_Invitation()
{
	FILE* fp = fopen("invitation.data", "r+");
	if (fp == NULL)
	{
		return;
	}
	int size = sizeof(Invitation);
	Invitation* iptr = (Invitation*)malloc(size);
	memset(iptr, 0, size);
	printf("        ¡¾Delete¡¿input0quit\n");
	printf("-----------------------------------------\n");
	printf("Input the NO.to shield£º");
	size_t no;
	scanf("%u", &no);
	rewind(stdin);
	if (no == 0)
	{
		printf("                 Cancel to shield\n");
		printf("-----------------------------------------\n");
		fclose(fp);
		return;
	}
	else
	{
		while (fread(iptr, size, 1, fp) == 1)
		{
			if (iptr->no == no)
			{
				strcpy(iptr->content, "Content has been shielded");
				fseek(fp, -size, SEEK_CUR); 
				fwrite(iptr, size, 1, fp);
				fclose(fp);
				printf("                 Succeed to shield\n");
				printf("-----------------------------------------\n");
				return;
			}
		}
	}
}
//Clear
void clear_Invitation()
{
	FILE* fp = fopen("invitation.data", "wb");
	fclose(fp);
	printf("           All post has been cleared\n");
	printf("-----------------------------------------\n");
}
//Forum
void forum(LstudentPtr sptr)
{
	int is_mamager = 0;
	printf("             ¡¾Library Forum¡¿\n");
	printf("-----------------------------------------\n");
	printf("1.View forum    2.Post the post    3.return\n");
	if (strcmp(sptr->data.username, manager_name) == 0)
	{
		printf("¡¾4¡¿shield post    ¡¾5¡¿clear post\n");
		is_mamager = 1;
	}
	do
	{
		char ch = getch();
		while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5')
			ch = getch();
		if (ch == '1')
		{
			communicate();
		}
		else if (ch == '2')
		{
			add_Invitation(sptr);
		}
		else if (ch == '3')
		{
			break;
		}
		else if (ch == '4' && is_mamager)
		{
			shield_Invitation();
		}
		else if (ch == '5' && is_mamager)
		{
			clear_Invitation();
		}
		printf("             ¡¾Library Forum¡¿\n");
		printf("-----------------------------------------\n");
		printf("1.View forum    2.Post the post    3.return\n");
		if (is_mamager)
		{
			printf("¡¾4¡¿shield post    ¡¾5¡¿clear post\n");
		}
	} while (1);
}
