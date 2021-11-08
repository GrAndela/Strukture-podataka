#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element
{
	int coefficient;
	int exponent;
	Position next;
} Element;

int FillOutFileName(char* fileName);
int ReadFile(Position head1, Position head2, char* fileName);
int ParseStringIntoList(Position head, char* buffer);
int DeleteAfter(Position previous);
int InsertAfter(Position position, Position newElement);
int InsertSorted(Position head, Position newElement);
int MergeAfter(Position position, Position newElement);
Position CreateElement(int coefficient, int exponent);
int PrintPoly(char* name, Position first);
int CreateAndInsertAfter(int coefficient, int exponent, Position position);
int AddPoly1(Position resultHead, Position head1, Position head2);
int AddPoly2(Position resultHead, Position head1, Position head2);
int MultiplyPoly(Position resultHead, Position head1, Position head2);
int FreeMemory(Position head);

int main(int argc, char** argv)
{

	
	Element head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element resultAdd = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element resultMult = { .coefficient = 0, .exponent = 0, .next = NULL };
	char fileName[MAX_SIZE] = { 0 };

	FillOutFileName(fileName);

	if (ReadFile(&head1, &head2, fileName) == EXIT_SUCCESS)
	{
		PrintPoly("pol1", head1.next);
		PrintPoly("pol2", head2.next);

		AddPoly1(&resultAdd, &head1, &head2);
		MultiplyPoly(&resultMult, &head1, &head2);

		PrintPoly("polAdd", resultAdd.next);
		PrintPoly("polMult", resultMult.next);

		FreeMemory(&head1);
		FreeMemory(&head2);
		FreeMemory(&resultAdd);
		FreeMemory(&resultMult);
	}

	return EXIT_SUCCESS;
}


int FillOutFileName(char* fileName)
{

	printf("Enter name of file:\n");
	scanf(" %s", fileName);

	return EXIT_SUCCESS;
}

int ReadFile(Position head1, Position head2, char* fileName)
{
	FILE* file = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	file = fopen(fileName, "r");
	if (!file)
	{
		perror("Can't open file!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, file);
	status = ParseStringIntoList(head1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, file);
	status = ParseStringIntoList(head2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(file);

	return EXIT_SUCCESS;
}

int ParseStringIntoList(Position head, char* buffer)
{
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %d %d %n", &coefficient, &exponent, &numBytes);
		if (status != 2)
		{
			printf("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newElement = CreateElement(coefficient, exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		InsertSorted(head, newElement);

		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}

int DeleteAfter(Position previous)
{
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int MergeAfter(Position position, Position newElement)
{
	if (position->next == NULL || position->next->exponent != newElement->exponent)
	{
		InsertAfter(position, newElement);
	}
	else 
	{
		int resultCoefficient = position->next->coefficient + newElement->coefficient;
		if (resultCoefficient == 0) 
		{
			DeleteAfter(position);
		}
		else
		{
			position->next->coefficient = resultCoefficient;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}

int InsertSorted(Position head, Position newElement)
{
	Position temp = head;

	while (temp->next != NULL && temp->next->exponent < newElement->exponent) 
	{
		temp = temp->next;
	}

	MergeAfter(temp, newElement);

	return EXIT_SUCCESS;
}

Position CreateElement(int coefficient, int exponent)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Element));
	if (!element)
	{
		perror("Can't allocate memory!\n");
		return element; 
	}

	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;

	return element;
}

int PrintPoly(char* name, Position first) {
	printf(" %s = ", name);
	if (first) {
		if (first->exponent < 0) {
			if (first->coefficient == 1)
			{
				printf("x^(%d)", first->exponent);
			}
			else
			{
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else {
			if (first->coefficient == 1)
			{
				printf("x^%d", first->exponent);
			}
			else
			{
				printf("%dx^%d", first->coefficient, first->exponent);
			}
		}

		first = first->next;
	}

	for (; first != NULL; first = first->next) {
		if (first->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else {
				printf(" - %dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1)
				{
					printf(" + x^(%d)", first->exponent);
				}
				else
				{
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else
			{
				if (first->coefficient == 1)
				{
					printf(" + x^%d", first->exponent);
				}
				else
				{
					printf(" + %dx^%d", first->coefficient, first->exponent);
				}
			}
		}
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int CreateAndInsertAfter(int coefficient, int exponent, Position position)
{
	Position newElement = CreateElement(coefficient, exponent);
	if (!newElement)
	{
		return EXIT_FAILURE;
	}

	InsertAfter(position, newElement);
	position = position->next;

	return EXIT_SUCCESS;

}

int AddPoly1(Position resultHead, Position head1, Position head2)
{
	Position i = head1->next;
	Position j = head2->next;
	Position k = resultHead;
	Position temp = NULL;

	while (i != NULL && j != NULL) 
	{
		if (i->exponent == j->exponent)
		{
			CreateAndInsertAfter(i->coefficient + j->coefficient, i->exponent, k);
			i = i->next;
			j = j->next;
		}
		else if (i->exponent < j->exponent)
		{
			CreateAndInsertAfter(i->coefficient, i->exponent, k);
			i = i->next;
		}
		else 
		{
			CreateAndInsertAfter(j->coefficient, j->exponent, k);
			j = j->next;
		}

	}
	if (i == NULL)
	{
		temp = j;
	}
	else 
	{
		temp = i;
	}
	while (temp != NULL)  
	{
		CreateAndInsertAfter(temp->coefficient, temp->exponent, k);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int AddPoly2(Position resultHead, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		Position newElement = CreateElement(i->coefficient, i->exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		InsertSorted(resultHead, newElement);
	}
	for (j = head2->next; j != NULL; j = j->next)
	{
		Position newElement = CreateElement(j->coefficient, j->exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		InsertSorted(resultHead, newElement);
	}
	return EXIT_SUCCESS;
}

int MultiplyPoly(Position resultHead, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			Position newElement = CreateElement(i->coefficient * j->coefficient, i->exponent + j->exponent);
			if (!newElement)
			{
				return EXIT_FAILURE;
			}

			InsertSorted(resultHead, newElement);
		}
	}
	return EXIT_SUCCESS;
}
int FreeMemory(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		DeleteAfter(temp);
	}

	return EXIT_SUCCESS;
}