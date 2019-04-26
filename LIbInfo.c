// LIbInfo.cpp: 定义控制台应用程序的入口点。
//


#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "Data.h"
#include "func.h"
#include "Study.h"
#include "User.h"
#include "Worker.h"
#include "Communicate.h"

void sMenu()
{
	char ch;
	while (1)
	{
		printf("-----------------------------------------\n");
		printf("1.Query book（borrow book）   2.all book（borrow book）\n3.Personal information（return book）   4.forum    5.quit\n");
		ch = getch();
		while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5')
			ch = getch();
		switch (ch)
		{
		case '1':
			find_a_book();
			break;
		case '2':
			find_all_book();
			break;
		case '3':
			oneself(active_user, 0);
			break;
		case '4':
			forum(active_user);
			break;
		case '5':
			active_user = NULL;
			return;
		default:
			continue;
		}
	}
}
void mMenu()
{
	char ch;
	while (1)
	{
		printf("-----------------------------------------\n");
		printf("1.Query book（borrow book）  2. all book（borrow book）   3.Personal information（return book）\n");
		printf("【4】add book   【5】modify book\n【6】delete book   【7】user information\n【8】forum       【9】quit\n");
		ch = getch();
		while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' && ch != '6' && ch != '7' && ch != '8' && ch != '9')
			ch = getch();
		switch (ch)
		{
		case '1':
			find_a_book();
			break;
		case '2':
			find_all_book();
			break;
		case '3':
			oneself(active_user, 0);
			break;
		case '4':
			add_book();
			break;
		case '5':
			mod_book();
			break;
		case '6':
			del_book();
			break;
		case '7':
			list_student();
			break;
		case '8':
			forum(active_user);
			break;
		case '9':
			active_user = NULL;
			return;
		default:
			continue;
		}
	}
}
int main()
{
	init_data();
	char ch;
	while (1)
	{
		printf("-----------------------------------------\n");
		printf("            Library management system \n");
		printf("-----------------------------------------\n");
		printf("1.login   2.register   3.quit\n");
		ch = getch();
		while(ch != '1' && ch != '2' && ch != '3')
			ch = getch();
		switch (ch)
		{
		case '1':
			Login();
			//先First judge the front, if it is empty, exit directly. No need to worry about the back exception
			if (active_user != NULL && strcmp(active_user->data.username, manager_name) == 0)
			{
				mMenu();
			}
			else if (active_user != NULL)
			{
				sMenu();
			}
			break;
		case '2':
			Register();
			break;
		case '3':
			free_source();
			exit(1);
		default:
			continue;
		}	
	}
    return 0;
}


