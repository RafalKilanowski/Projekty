#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define 	BUFFER	100
char 				temp 	[BUFFER];
static 				int 				number = 0;

 struct List
{
	
	char 			* 	str;
	struct List 	*   next;
};
typedef struct List List;

// List options //
List * 	init();
int 	lenght(const List * t);
void 	append( List * t);
void 	push(List ** t);
void 	display(List * t);
void 	destroy(List ** t);
char 	* pop(List **t,char *);
void 	reverse (List ** t);
void 	sort(List ** t);
List * 	clone(List * t);
void show_menu();

int main()
{
	char switch1;
	List *  list1 = init();
	List * clone1;
	printf("What would you like to do with your list?\n");
	show_menu();
	scanf("%c",&switch1);
	while(getchar()!='\n')
				continue;
	while(switch1!='q')
	{

		switch(switch1)
		{
			case 	'1' : 	{  
								append(list1);
								break;
							}

			case 	'2' : 	{  	
								push(&list1);
								break;
							}

			case 	'3' : 	{
								display(list1);
								break;
							}

			case 	'4' : 	{	printf("Number of items = %d\n",lenght(list1));
								break;
							}

			case 	'5' : 	{	printf("Element = %s \bdeleted\n",pop(&list1,temp));
								break;
							}

			case 	'6' : 	{
								destroy(&list1);
								break;
							}

			case 	'7' : 	{
								clone1=clone(list1);
								printf("Cloned list ->\n");
								display(clone1);
								destroy(&clone1);
								break;
							}
			
			case 	'8' : 	
							{
								reverse(&list1);	
								break;			
							}
							

			case 	'9' : 	{
								sort(&list1);
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
	destroy(&list1);
	return 0;
}


List * init()
{
	List * test = malloc(sizeof(List));
	test->str=NULL;
	test->next=NULL;
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
	if(t==NULL)
	{
		printf("You destroyed whole list!\n");
	}
	else
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
		t->next=create;
		
	}
	else
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		strcpy(create->str,temp);
		while(t->next !=NULL)
		{
			t=t->next;
		}
		t->next=create;

	}
	number++;
}
}

void display(List * t)
{

	if(t==NULL)
	{
		printf("No list is created!\n");
	}
	else if(t->str==NULL)
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

void push(List ** t)
{
	if(*t==NULL)
	{
		printf("You destroyed whole list!\n");
	}
	else
	{

	char 	temp[BUFFER];
	int 	temp1;

	printf("New element added, insert the string :");
	

	fgets(temp,BUFFER-1,stdin);
	if(number==0)
	{
		
		temp1=strlen(temp)+1;
		(*t)->str=malloc(sizeof(char)*temp1);
		strcpy((*t)->str,temp);
		
	}
	else 
	{
		List * create = init();
		temp1=strlen(temp)+1;
		create->str=malloc(sizeof(char)*temp1);
		strcpy(create->str,temp);
		create->next=*t;
		*t=create;	
	}
	
	number++;
}
}	



void destroy(List ** t)
{
	while(*t)
		{
			List * temporary = (*t)->next;
			free((*t)->str);
			free(*t);
			*t=temporary;
			number--;	
		}
		(*t)=NULL;
	printf("List is empty now !\n");	
		
}

char * pop(List **t,char * temp)
{
	List * temporary=(*t);
	List * begin=(*t);
	if(*t)
	{
		if(temporary->next==NULL)
		{
			printf("The last element in the list\n");
			if(temporary->str != NULL)
			{
			strcpy(temp,temporary->str);
			free(temporary->str);
			free(temporary);
			*t=NULL;
			number--;
			return temp;
			}
			else
			{
				free(temporary);
				*t=NULL;
				temp="Brak";
				number--;
				return temp;
			}
		}
		else
		{
		while(temporary->next!=NULL)
			{
				(*t)=temporary;
				temporary=temporary->next;
			}
			strcpy(temp,temporary->str);
			free(temporary->str);
			free(temporary);
			number--;
			(*t)->next=NULL;
			(*t)=begin;
		}
	}
	else
	{
		printf("You can't pop empty list\n");
		temp="Brak";
	}

	return temp;
}

void reverse (List ** t)
{
	if((*t))
	{
		if((*t)->next)

	{
	
	List * temporary 	= (*t)->next;
	List * temporary1	= (*t)->next;
	(*t)->next=NULL;
	while(temporary->next !=NULL)
	{
		temporary1=temporary1->next;
		temporary->next=(*t);
		(*t)=temporary;
		temporary=temporary1;
	}
	temporary->next=(*t);
	(*t)=temporary;
	}
}
display((*t));
}

void	sort(List **t)
{
	if((*t))
	{
		List * temp = (*t);
		List * temp2 = (*t);
		List * previous;
		int i=number;
		int j=0;
		for(i;i>0;i--)
		{
			for(j=0;j<i-1;j++)
			{
				if(strcmp(temp->str,temp->next->str)>=0)
				{
					previous=temp2;
					temp2=temp;
					temp=temp->next;
					temp2->next=temp->next;
					temp->next=temp2;
					if(j==0)
					{	
						(*t)=temp;
						temp=temp2;
						temp2=(*t);
					}
					else
					{
						previous->next=temp;
						temp=temp2;
						temp2=previous->next;
					}
				}
				else
				{
					temp2=temp;
					temp=temp->next;
				}
			}
			temp=(*t);
			temp2=(*t);
		}
	}
}

List * 	clone(List * t)
{
	int temp1;
	List * new1 = init();
	List * new2 = new1;
	if(t)
	{
		temp1=strlen(t->str)+1;
		new1->str=malloc(sizeof(char)*temp1);
		strcpy(new1->str,t->str);
		if(t->next != NULL)
		{
			t=t->next;
			while(t->next !=NULL)
			{
				List * create = init();
				temp1=strlen(t->str)+1;
				create->str=malloc(sizeof(char)*temp1);
				strcpy(create->str,t->str);
				new1->next=create;
				new1=new1->next;
				t=t->next;
			}
		List * create = init();
		temp1=strlen(t->str)+1;
		create->str=malloc(sizeof(char)*temp1);
		strcpy(create->str,t->str);
		new1->next=create;
		}
	}
	return new2;
}


