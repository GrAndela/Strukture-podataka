#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

struct _Directory;
typedef struct _Directory* PositionDirectory;
typedef struct _Directory {
	char name[MAX];
	PositionDirectory child;
	PositionDirectory neighbour;
} Directory;

struct _Cvor;
typedef struct _Cvor* Position;
typedef struct _Cvor {
	PositionDirectory parent;
	Position next;
} Cvor;

int Push(Position, PositionDirectory);
int PrintOptions();
int SortedAdd(PositionDirectory, PositionDirectory);
int dir(PositionDirectory);
int exit(Position, PositionDirectory);
PositionDirectory cdParents(Position);
PositionDirectory Pop(Position);
PositionDirectory cd(Position, PositionDirectory, char*);
PositionDirectory CreateDirectory(char*);
PositionDirectory md(Position, PositionDirectory, char*);
Position CreatePosition();


int main() {
	char operation = '0';
	int isActive = 1;

	char name[MAX];
	Position stog = NULL;
	PositionDirectory sqrt = NULL, current = NULL, result = NULL;


	stog = CreatePosition();
	sqrt = CreateDirectory("C:");
	current = sqrt;

	while (isActive) {
		PrintOptions();
		scanf(" %c", &operation);

		switch (operation) {
		case '1':
			printf("Choose: md\n");
			printf("Name of the new directory:\n");
			scanf("%s", name);
			result = md(stog, current, name);
			if (!result) {
				printf("Error while opening directory!\n");
			}
			break;
		case '2':
			printf("Choose: cd dir\n");
			printf("Name of the directory: \n");
			scanf("%s", name);
			result = cd(stog, current, name);
			if (!result) {
				printf("Error while opening directory!\n");
			}
			else {
				current = result;
			}
			break;
		case '3':
			printf("Choose: cd..\n");
			result = cdParents(stog);
			if (!result) {
				printf("Can't go pass sqrt!\n");
			}
			else {
				current = result;
			}
			break;
		case '4':
			printf("Choose: dir\n");
			dir(current);
			break;
		case '5':
			printf("Choose: End of the program");
			isActive = 0;
			break;
		default:
			printf("Wrong option - try again\n");
			break;
		}
	}
	return 0;
}

int dir(PositionDirectory current) {
	PositionDirectory tmp = NULL;
	printf("%s\n", current->name);
	if (current->child != NULL) {
		tmp = current->child;
		while (tmp != NULL) {
			printf("\t%s", tmp->name);
			tmp = tmp->neighbour;
		}
	}
	return 0;
};

PositionDirectory cd(Position stog, PositionDirectory current, char* name) {
	PositionDirectory q = NULL, tmp = NULL;
	if (current->child == NULL) {
		printf("Current directory is empty!\n");
		return NULL;
	}
	tmp = current->child;
	while (tmp != NULL) {
		if (strcmp(name, tmp->name) == 0) {
			q = tmp;
		}
		tmp = tmp->neighbour;
	}
	Push(stog, current);
	return q;
}

int SortedAdd(PositionDirectory current, PositionDirectory q) {
	PositionDirectory head = NULL, r = NULL;
	head = CreateDirectory(" ");
	r = head;


	if (current->child == NULL) {
		current->child = q;
		return 0;
	}

	head->neighbour = current->child;
	while (r->neighbour != NULL && strcmp(r->neighbour->name, q->name) < 0) {
		r = r->neighbour;
	}
	q->neighbour = r->neighbour;
	r->neighbour = q;
	current->child = head->neighbour;
	return 0;
};

PositionDirectory md(Position stog, PositionDirectory current, char* name) {
	PositionDirectory q = NULL;
	q = CreateDirectory(name);
	SortedAdd(current, q);
	return q;
}

int PrintOptions() {
	printf("\n\n********************************************************************\n\n");
	printf("Choose operation: \n\t 1. md (create directory) \n\t 2. cd dir (change directory) \n\t 3. cd.. (change to parent directory) "
		"\n\t 4. dir (print chosen directory) \n\t 5. end of the program\n");
	return 0;
}

Position CreatePosition() {
	Position q = malloc(sizeof(Cvor));
	if (!q) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	q->next = NULL;
	return q;
}

PositionDirectory CreateDirectory(char* name) {
	PositionDirectory q = malloc(sizeof(Directory));
	if (!q) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	q->neighbour = NULL;
	q->child = NULL;
	strcpy(q->name, name);
	return q;
}
PositionDirectory Pop(Position stog) {
	Position tmp = NULL;
	PositionDirectory p = NULL;
	if (stog == NULL || stog->next == NULL) {
		return NULL;
	}
	tmp = stog->next;
	p = tmp->parent;
	stog->next = tmp->next;
	free(tmp);
	return p;
}

int Push(Position stog, PositionDirectory current) {
	Position q = NULL;
	q = CreatePosition();
	q->parent = current;
	q->next = stog->next;
	stog->next = q;
	return 0;
}

PositionDirectory cdParents(Position stog) {
	return Pop(stog);
}