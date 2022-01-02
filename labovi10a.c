#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 30

//Task a) - list with binary trees

struct _TreeNode;
typedef struct _TreeNode* PositionTree;
typedef struct _TreeNode {
	char city[MAX_SIZE];
	int population;
	PositionTree left;
	PositionTree right;
} TreeNode;

struct _ListNode;
typedef struct _ListNode* PositionList;
typedef struct _ListNode {
	char country[MAX_SIZE];
	PositionTree cities;
	PositionList next;
} ListNode;

PositionList AddNewElementToList();
PositionList FindCountry(PositionList, char*);
PositionTree CreateTreeElement();
int ReadCountryFile(PositionList, char*);
int AddCountryToList(PositionList, char*, char*);
PositionTree AddCityToTree(PositionTree, char*, int);
PositionTree ReadCityFile(PositionTree, char*);
int PrintCountriesAndCities(PositionList);
int InOrderPrintTree(PositionTree);
int Choose(PositionList);
int FindPopulationsOfTheCitiesLargerThanX(PositionTree, int);

int main() {

	int var = 0;

	PositionList headList = NULL;

	headList = AddNewElementToList();

	ReadCountryFile(headList, "filename.txt");

	PrintCountriesAndCities(headList->next);

	Choose(headList);
	
	return EXIT_SUCCESS;
}

PositionList FindCountry(PositionList headList, char* drzava) {
	while (headList != NULL) {
		if (strcmp(drzava, headList->country) == 0) {
			return headList;
		}
		else {
			headList = headList->next;
		}
	}
	return NULL;
}

int Choose(PositionList headList) {
	PositionList q = NULL;
	char tmp1[MAX_SIZE];
	int tmp2;
	printf("Choose country you want to search: \n");
	scanf(" %s", tmp1);
	printf("Find all cities that have more population than x: \n");
	scanf("%d", &tmp2);
	q = FindCountry(headList, tmp1);
	if (!q) {
		printf("Country you choe does not exist!");
		return EXIT_FAILURE;
	}
	FindPopulationsOfTheCitiesLargerThanX(q->cities, tmp2);
	
	return EXIT_SUCCESS;
}

int FindPopulationsOfTheCitiesLargerThanX(PositionTree p, int populationX) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}

	FindPopulationsOfTheCitiesLargerThanX(p->left, populationX);

	if (p->population > populationX) {
		printf("%s %d, ", p->city, p->population);
	}
	FindPopulationsOfTheCitiesLargerThanX(p->right, populationX);

	return EXIT_SUCCESS;
}

int PrintCountriesAndCities(PositionList headList) {
	while (headList != NULL) {
		printf("%s cities: \n", headList->country);
		InOrderPrintTree(headList->cities);
		printf("\n");
		headList = headList->next;
	}
}

PositionList AddNewElementToList() {
	PositionList q = malloc(sizeof(ListNode));
	if (q == NULL) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(q->country, "");
	q->cities = NULL;
	q->next = NULL;
	return q;
}

PositionTree CreateTreeElement(char* city, int population) {
	PositionTree q = malloc(sizeof(TreeNode));
	if (q == NULL) {
		printf("Couldn't allocate memory!\n");
		return NULL;
	}
	strcpy(q->city, city);
	q->population = population;
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
		printf("%s %d, ", p->city, p->population);
		InOrderPrintTree(p->right);
	}
	return EXIT_SUCCESS;
}

int ReadCountryFile(PositionList headList, char* Filename) {
	char CountryName[MAX_SIZE] = "", FileCitiesName[MAX_SIZE] = "";

	FILE* dat = NULL;
	dat = fopen(Filename, "r");
	if (!dat) {
		printf("Error while opening the file!\n");
		return EXIT_FAILURE;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %s", CountryName, FileCitiesName);
		AddCountryToList(headList, CountryName, FileCitiesName);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int AddCountryToList(PositionList headList, char* country, char* FileCitiesName) {
	PositionList tmp = NULL;
	char tmp1[MAX_SIZE], tmp2[MAX_SIZE];

	tmp = AddNewElementToList();
	strcpy(tmp->country, country);

	tmp->cities = ReadCityFile(tmp->cities, FileCitiesName);

	strcpy(tmp1, country);
	while (headList->next != NULL) {
		strcpy(tmp2, headList->next->country);
		if (strcmp(strupr(tmp1), strupr(tmp2)) > 0) {
			headList = headList->next;
			continue;
		}
		break;
	}

	tmp->next = headList->next;
	headList->next = tmp;
}

PositionTree ReadCityFile(PositionTree headTree, char* Filename) {
	char CityName[MAX_SIZE] = "";
	int CityPopulation = 0;
	FILE* dat = NULL;

	dat = fopen(Filename, "r");
	if (!dat) {
		printf("Error while opening the file!\n");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %d", CityName, &CityPopulation);
		headTree = AddCityToTree(headTree, CityName, CityPopulation);
	}
	fclose(dat);
	return headTree;
}

PositionTree AddCityToTree(PositionTree p, char* city, int population) {
	if (p == NULL) {
		p = CreateTreeElement(city, population);
	}
	else if (population == p->population) {
		if (strcmp(city, p->city) < 0) {
			p->left = AddCityToTree(p->left, city, population);
		}
		if (strcmp(city, p->city) > 0) {
			p->right = AddCityToTree(p->right, city, population);
		}
	}
	else {
		if (population < p->population) {
			p->left = AddCityToTree(p->left, city, population);
		}
		if (population > p->population) {
			p->right = AddCityToTree(p->right, city, population);
		}
	}
	return p;
}