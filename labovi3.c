#define _CRT_SECURE_NO_WARNING

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>

#define MAX_SIZE (50)
#define MAX (1024)

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	position next;
}person;


int PrependList(person* HEAD);
int AppendList(person* HEAD);
int PrintList(person* HEAD);
person* FindPersonBySurname(person* HEAD, char* surname);
person* FindLast(person* HEAD);
int DeletePerson(person* HEAD, person* element);
int AddAfter(person* element);
int AddBefore(person* HEAD, person* element);
int Sort(person* HEAD);
int SaveInFile(person* HEAD, char* filename);
int ReadFromFile(person* HEAD);

int main(int argc,char** argv) 
{
	person* HEAD = (person*)malloc(sizeof(person));
	person HEAD = { .name = {0}, .surname = {0}, .birthYear = {0}, .next = NULL };
	char surname[MAX_SIZE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	person temp = NULL;
	int birthYear = 0;
	int choice = 1;

	while (choice != 0) 
	{
		PrintList(HEAD);
		printf("\nAdding person on top of the list-1\n",
			"Adding person at the end of the list-2\n",
			"Searching person by the surname-3\n",
			"Deleting person from the list-4\n",
			"Adding person after another-5\n",
			"Adding person before another-6\n",
			"Sorting by surname-7\n",
			"Saving in file-8\n",
			"Reading from file-9\n");
		printf("Your choice: \n");
		scanf("%d", &choice);

		if (choice == 1)
		{
			printf("Enter name and surname of the student: \n");
			scanf("%s %s", name, surname);
			printf("Enter birth year: \n");
			scanf("%d", &birthYear);
			PrependList(HEAD);
		}
		else if (choice == 2)
		{
			printf("Enter name and surname of the student: \n");
			scanf("%s %s", name, surname);
			printf("Enter birth year: \n");
			scanf("%d", &birthYear);
			AppendList(HEAD);
		}
		else if (choice == 3)
		{
			printf("Enter surname of the student: \n");
			scanf("%s", surname);
			temp = FindPersonBySurname(HEAD, surname);
			if (temp)
			{
				printf("Name and surname: %s %s\nBirth year: %d\n",
					temp->name, temp->surname, temp->birthYear);
			}
			else
				printf("This person is not on the list!\n");
		}
		else if (choice == 4)
		{
			printf("Enter name and surname of the student: \n");
			scanf("%s", surname);
			DeletePerson(HEAD, surname);
		}
		else if (choice == 5)
		{
			printf("Enter surname of the student: \n");
			scanf("%s", surname);
			AddAfter(FindPersonBySurname(HEAD, surname));
		}
		else if (choice == 6)
		{
			printf("Enter surname of the student: \n");
			scanf("%s", surname);
			AddBefore(HEAD, FindPersonBySurname(HEAD, surname));
		}
		else if (choice == 7)
		{
			Sort(HEAD);
		}
		else if (choice == 8)
		{
			SaveInFile(HEAD, "list.txt");
		}
		else if (choice == 9)
		{
			ReadFromFile(HEAD);
		}
		else
			printf("Error!\n");
	}

	return EXIT_SUCCESS;
}


int PrependList(person* HEAD) 
{
	person* element = (person*)malloc(sizeof(person));

	element->next = HEAD->next;
	HEAD->next = element;

	printf("Enter name,surname and birth year of the student: \n");
	scanf("%s %s %d", element->name, element->surname, &element->birthYear);

	return EXIT_SUCCESS;
}

int AppendList(person* HEAD) 
{
	person* element = (person*)malloc(sizeof(person));
	person* p = HEAD;

	while (p->next != NULL)
		p = p->next;

	element->next = NULL;
	p->next = element;

	printf("Enter name,surname and birth year of the student: \n");
	scanf("%s %s %d", element->name, element->surname, &element->birthYear);

	return EXIT_SUCCESS;
}

int PrintList(person* HEAD)
{
	persop* p = HEAD->next;

	while (p != NULL) 
	{
		printf("Name: %s\nSurname: %s\nBirth Year: %d\n\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}

	return EXIT_SUCCESS;
}

person* FindPersonBySurname(person* HEAD, char* surname)
{
	person* p = HEAD->next;

	while (p != NULL && strcmp(p->surname, surname)) 
	{
		p = p->next;
	}

	return p;
}

person* FindLast(person* HEAD) 
{
	person* p = HEAD;

	while (p != NULL && p->next != NULL)
		p = p->next;

	return p;

}

int DeletePerson(person* HEAD, person* element)
{
	person* p = HEAD;

	while (p != NULL && p->next != element) 
	{
		p = p->next;
	}

	if (p == NULL)
		return -1;
	else
	{
		p->next = p->next->next;
		free(element);
	}

	return EXIT_SUCCESS;
}

int AddAfter(person* element)
{
	person* newelement = (person*)malloc(sizeof(person));

	newelement->next = element->next;
	element->next = newelement;

	printf("Enter name,surname and birth year: \n");
	scanf("%s %s %d", newelement->name, newelement->surname,&newelement->birthYear));

	return EXIT_SUCCESS;
}

int AddBefore(person* HEAD, person* element)
{
	person* p = HEAD;
	person* newelement = (person*)malloc(sizeof(person));

	while (p != NULL && p->next != element)
		p = p->next;

	if (p == NULL) 
	{
		free(newelement);
		return -1;
	}

	AddAfter(p);

	return EXIT_SUCCESS;
}

int Sort(person* HEAD) 
{
		person* p = HEAD;
		person* q = NULL;
		person* pre_q = NULL;
		person* last = NULL;

		while (p->next != last)
		{
			pre_q = p;
			q = pre_q->next;

			while (q->next != last)
			{
				if (strcmp(q->surname, q->next->surname) > 0)
				{
					pre_q->next = q->next;
					q->next = q->next->next;
					pre_q->next->next = q;
					q = pre_q->next;
				}
				pre_q = q;
				q = q->next;
			}
			last = q;
		}

		return EXIT_SUCCESS;
}

int SaveInFile(person* HEAD, char* filename)
{
	person* p = HEAD->next;
	FILE* fp = NULL;
	fp = fopen(filename, "w");

	if (fp == NULL)
		return -1;

	while (p != NULL) 
	{
		fprintf(fp, "Name: %s, Surname: %s, Birth year: %d\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadFromFile(person* HEAD)
{
	person* q;
	person* p = FindLast(HEAD);

	FILE* fp = NULL;
	fp = fopen("list.txt", "r");

	int _char = 0;
	int number = 0;
	int i = 0;
	char buffer[MAX] = { 0 };

	if (fp == NULL) {
		printf("Error while opening file!\n");
		return -1;
	}

	while (fgets(buffer, MAX, fp)) {
		number++;
	}

	rewind(fp);

	for (i = 0; i < number; i++) {
		q = (person*)malloc(sizeof(person));

		q->next = NULL;
		p->next = q;
		p = p->next;

		fscanf(fp, "%s %s %d", q->name, q->surname, &q->birthYear);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}





