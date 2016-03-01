#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define 	BUFFER	100

static 				int 				number = 0;

 struct List
{
	
	char 			* 	str;
	struct List 	*   next;
	struct List  	*	previous;
};
typedef struct List List;


List * init();
void show_menu();
int lenght(const List * t);
void append( List * t);
void push(List * t);
void display(List * t);
void destroy(List * t);


int main()
{
	char switch1;
	List *  list1 = init();
	printf("What would you like to do with your list?\n");
	show_menu();
	scanf("%c",&switch1);
	while(getchar()!='\n')
				continue;
	while(switch1!='q')
	{

		switch(switch1)
		{
			case 	'1' : 	{  	append(list1);
								break;
							}

			case 	'2' : 	{  	push(list1);

								break;
							}

			case 	'3' : 	{
								display(list1);
								break;
							}

			case 	'4' : 	{	printf("Number of items = %d\n",lenght(list1));
								break;
							}
			default 	:	{ 	printf("Bad option, try once again\n");
								break;
							}
		}
		show_menu();
		
	
		scanf("%c",&switch1);
		while(getchar()!='\n')
				continue;
	}



	
	

	return 0;
}


List * init()
{
	List * test = malloc(sizeof(List));
	test->str=NULL;
	test->next=test->previous=NULL;
	return test;
}

void show_menu()
{
printf("*** Add new element at the end to the list - press 1\n*** Add new element at the begining of the list - press 2\n*** Display a list - press 3\n*** Show a lenght of the list - press 4\n*** Remove first element from the end of the list - press 5\n*** Destroy the list - press 6\n*** Make a sample copy of the list - press 7\n*** Reverse order of the list - press 8\n*** Sort the list - press 9\n*** QUIT - press q\n");

}

int lenght(const List * t)
{
	return number;
}

void append( List * t)
{
	char 	temp[BUFFER];
	int 	temp1;

	printf("New element added, insert the string :");
	

	fgets(temp,BUFFER-1,stdin);
	if(number==0)
	{
		
		temp1=strlen(temp)+1;
		t->str=malloc(sizeof(char)*temp1);
		strcpy(t->str,temp);
		
	}
	else if (number==1)
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		strcpy(create->str,temp);
		create->previous=t;
		t->next=create;
		t->previous=create;
		

	}
	else
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		strcpy(create->str,temp);
		t->previous->next=create;
		create->previous=t->previous;
		t->previous=create;

	}
	number++;
}

void display(List * t)
{
	if(t->str==NULL)
	{
		printf("List is empty!\n");
	}
	else
	{
	List * temporary = t;
	if(temporary->str != NULL)

		printf("%s",temporary->str);
		
	while(temporary->next != NULL)
	{
		temporary=temporary->next;
		printf("%s",temporary->str);	
	}
}
}

void push(List * t)
{
	char 	temp[BUFFER];
	int 	temp1;

	printf("New element added, insert the string :");
	

	fgets(temp,BUFFER-1,stdin);
	if(number==0)
	{
		
		temp1=strlen(temp)+1;
		t->str=malloc(sizeof(char)*temp1);
		strcpy(t->str,temp);
		
	}
	else if (number==1)
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		create->previous=t;
		t->next=create;
		t->previous=create;
		strcpy(create->str,t->str);
		strcpy(t->str,temp);
	}
	else
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		t->next->previous=create;
		create->next=t->next;
		create->previous=t;
		t->next=create;
		strcpy(create->str,t->str);
		strcpy(t->str,temp);
	}
	
	number++;
}	

