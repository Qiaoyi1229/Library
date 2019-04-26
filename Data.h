#pragma once

#define name_max    20
#define pass_max    10
#define num_max     20
#define borrow_max  10
#define tag			size_t
#define error		0
#define ok			1

//#define poolmax		10

typedef struct student
{
	char username[name_max];
	char password[pass_max];
	int  borrow[borrow_max];
}Student ,*StudentPtr;

typedef struct book
{
	char name[name_max];
	char author[name_max];
	char bookId[num_max];
	size_t	 count;
	size_t ident;			//only tag, starting with 1, each book is different
}Book, *BookPtr;

typedef struct lstudent
{
	Student data;
	struct	lstudent* next;//Doubly linked list
	struct	lstudent* prev;
}Lstudent, *LstudentPtr;

typedef struct lbook
{
	Book data;
	struct lbook* next;
	struct lbook* prev;
}Lbook, *LbookPtr;

LbookPtr	lbhead_ptr;
LstudentPtr	lshead_ptr;
size_t book_count;
size_t student_count;


char manager_name[name_max];
Lstudent*	active_user;	//current user

#define content_max 300
//forum information
typedef struct
{
	char name[name_max];
	char content[content_max];
	size_t no;
}Invitation;
