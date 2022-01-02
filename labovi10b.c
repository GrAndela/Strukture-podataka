#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 30

//Task b) - Binary tree with bound list 

struct _ListNode;
typedef struct _ListNode* PositionList;
typedef struct _ListNode {
	char city[MAX_SIZE];
	int population;
	PositionList next;
} ListNode;

struct _TreeNode;
typedef struct _TreeNode* PositionTree;
typedef struct _TreeNode {
	char country[MAX_SIZE];
	PositionList cities;
	PositionTree left;
	PositionTree right;
} TreeNode;


PositionList CreateNewListElement();
PositionTree FindCountry(PositionTree, char*);
PositionTree CreateNewTreeElement(char*, PositionList);
PositionTree ReadCountryFile(PositionTree, char*);
int AddCityToList(PositionList, char*, int);
PositionTree AddCountryToTree(char*, PositionList, PositionTree);
PositionList ReadCityFile(char*);
int PrintList(PositionList);
int InOrderPrintTree(PositionTree);
int Choose(PositionTree);
int FindPopulationsLargerThanX(PositionList, int);

int main() {

	int var = 0;

	PositionTree headTree = NULL;

	headTree = ReadCountryFile(headTree, "Filename.txt");

	InOrderPrintTree(headTree);

	Choose(headTree);
	
	return EXIT_SUCCESS;
}

PositionTree FindCountry(PositionTree p, char* country) {
	if (p == NULL) {
		return NULL;
	}
	if (strcmp(country, p->country) == 0) {
		return p;
	}
	else if (strcmp(country, p->country) > 0) {
		return FindCountry(p->right, country);
	}
	return FindCountry(p->left, country);
}

int Choose(PositionTree headStablo) {
	PositionTree q = NULL;
	char tmp1[MAX_SIZE];
	int tmp2;
	printf("Choose country you want to search: \n");
	scanf("%s", tmp1);
	printf("Find all cities with population larger than X: \n");
	scanf("%d", &tmp2);
	q = FindCountry(headStablo, tmp1);
	if (!q) {
		printf("Chosen country does not exist!\n");
		return EXIT_FAILURE;
	}
	FindPopulationsLargerThanX(q->cities, tmp2);
	
	return EXIT_SUCCESS;
}

int FindPopulationsLargerThanX(PositionList headList, int populationX) {
	while (headList->next != NULL) {
		if (headList->population > populationX) {
			printf("%s %d, ", headList->city, headList->population);
		}
		headList = headList->next;
	}
	
	return EXIT_SUCCESS;
}

int PrintList(PositionList headList) {
	while (headList->next != NULL) {
		printf("%s %d ", headList->city, headList->population);
		headList = headList->next;
	}
	printf("\n\n");
	
	return EXIT_SUCCESS;
}

PositionList CreateNewListElement() {
	PositionList q = malloc(sizeof(ListNode));
	if (q == NULL) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(q->city, "");
	q->population = 0;
	q->next = NULL;
	return q;
}

PositionTree CreateNewTreeElement(char* country, PositionList cities) {
	PositionTree q = malloc(sizeof(TreeNode));
	if (q == NULL) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	q->cities = cities;
	strcpy(q->country, country);
	q->left = NULL;
	q->right = NULL;
	return q;
}

int InOrderPrintTree(PositionTree p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {
		InOrderPrintTree(p->left);
		printf("%s cities: ", p->country);
		PrintList(p->cities->next);
		InOrderPrintTree(p->right);
	}
	return EXIT_SUCCESS;
}

PositionTree ReadCountryFile(PositionTree headTree, char* Filename) {
	PositionList cities = NULL;
	char CountryName[MAX_SIZE] = "", FileCityName[MAX_SIZE] = "";

	FILE* dat = NULL;
	dat = fopen(Filename, "r");
	if (!dat) {
		printf("Error while opening file!\n");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %s", CountryName, FileCityName);
		cities = ReadCityFile(FileCityName);
		headTree = AddCountryToTree(CountryName, cities, headTree);
	}
	fclose(dat);
	
	return headTree;
}

int AddCityToList(PositionList headList, char* city, int population) {
	PositionList q = CreateNewListElement();
	strcpy(q->city, city);
	q->population = population;
	while (headList->next != NULL) {
		if (q->population > headList->next->population) {
			break;
		}
		headList = headList->next;
	}
	q->next = headList->next;
	headList->next = q;
	
	return EXIT_SUCCESS;
}

PositionList ReadCityFile(char* Filename) {
	PositionList q = NULL;
	q = CreateNewListElement();
	char CityName[MAX_SIZE] = "";
	int CityPopulation = 0;
	FILE* dat = NULL;

	dat = fopen(Filename, "r");
	if (!dat) {
		printf("Error while opening file!\n");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %d", CityName, &CityPopulation);
		AddCityToList(q, CityName, CityPopulation);
	}
	fclose(dat);
	
	return q;
}

PositionTree AddCountryToTree(char* country, PositionList cities, PositionTree p) {
	if (p == NULL) {
		p = CreateNewTreeElement(country, cities);
	}
	else {
		if (strcmp(country, p->country) < 0) {
			p->left = AddCountryToTree(country, cities, p->left);
		}
		if (strcmp(country, p->country) > 0) {
			p->right = AddCountryToTree(country, cities, p->right);
		}
	}

	return p;
}