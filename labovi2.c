#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct _person;
typedef struct _person* position;
typedef struct _person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	position next;
}person;

int Prependlist(position head, char* name, char* surname, int birthYear);
int Appendlist(position head, char* name, char* surname, int birthYear);
int Printlist(position first);
position Addperson(char* name, char* surname, int birthYear);
int Addafter(position _position, position newperson);
position Findlast(position head);
position Findperson(position first, char* surname);
position Findbefore(position head, char* surname);
int Deleteperson(position head, char* surname);

int main(int argc,char** argv) 
{
	person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	
	position p = &head;
	position temp = NULL;

	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = NULL;
	int choice = 1;

	while (choice != 0) {
		Printlist(p->next);
		printf("\nAdding person on top of the list-1\n");
		printf("Adding student at the end of the list-2\n");
		printf("Finding person by surname-3\n");
		printf("Deleting person from the list-4\n");
		printf("Your choice: \n");
		scanf("%d", &choice);
	}

	if (choice == 1) {
		printf("Write name and surname of the student you want add to the list:\n");
		scanf("%s %s", name, surname);
		printf("Write his/her birth year:\n");
		scanf("%d", &birthYear);
		Prependlist(p, name, surname, birthYear);
	}
	else if (choice == 2) {
		printf("Write name and surname of the student you want add at the end of the list\n");
		scanf("%s %s", name, surname);
		printf("Write his/her birth year:\n");
		scanf("%d", &birthYear);
		Appendlist(p, name, surname, birthYear);
	}
	else if (choice == 3) {
		printf("Write surname of the student you want find\n");
		scanf("%s", surname);
		temp = Findperson(p, surname);
		if (temp) {
			printf("Name and surname: %s %s\nBirth year: %d\n",
				temp->name, temp->surname, temp->birthYear);
		}
		else {
			printf("This person is not on the list\n");
		}
	}
	else if (choice == 4) {
		printf("Write surname of the person you want delete\n");
		scanf("%s", surname);
		Deleteperson(p, surname);
	}
	else {
		printf("Error!\n");
	}


	return EXIT_SUCCESS;
}
int Prependlist(position head, char* name, char* surname, int birthYear) {
	position newperson = NULL;

	newperson = (position)malloc(sizeof(person));
	if (!newperson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthYear = birthYear;
	newperson->next = NULL;

	newperson->next = head->next;
	head->next = newperson;

	return EXIT_SUCCESS;
}

int Appendlist(position head, char* name, char* surname, int birthYear) {

	position newperson = NULL;
	position last = NULL;

	newperson = Addperson(name, surname, birthYear);
	if (!newperson) {
		return -1;
	}

	last = Findlast(head);
	Addafter(last, newperson);

	return EXIT_SUCCESS;
}

int Printlist(position first) 
{
	position temp = first;
	while (temp) 
	{
		printf("Name:%s,surname:%s,"
			"birth year:%d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

position Addperson(char* name, char* surname, int birthYear) {
	position newperson = NULL;

	newperson = (position)malloc(sizeof(person));

	if (!newperson) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newperson->name, name);
	strcpy(newperson->surname, surname);
	newperson->birthYear = birthYear;
	newperson->next = NULL;

	return newperson;
}

int Addafter(position _position, position newperson) {
	newperson->next = position->next;
	position->next = newperson;

	return EXIT_SUCCESS;
}

position Findlast(position head) 
{
	positon temp = head;

	while (temp->next) 
	{
		temp = temp->next;
	}

	return temp;
}

position Findperson(position first, char* surname) 
{
	position temp = first;
	while (temp) 
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp=temp->next;
	}
	
	return NULL;
}

position Findbefore(position head, char* surname) {

	for (position temp = head; temp->next; temp = temp->next){
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;
}

int Deleteperson(position head, char* surname) {

	position before = NULL;
	position to_Delete = NULL;


	before = Findbefore(head, surname);
	if (before == NULL) {
		printf("This person is not on the list.\n");

	}
	else {
		to_Delete = before->next;
		before->next = to_Delete->next;
		free(to_Delete);
	}
	return EXIT_SUCCESS;
}
