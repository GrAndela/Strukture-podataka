#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 30
#define HASH_TABLE_MAX_SIZE (11)

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

struct _HashT;
typedef struct _HashT* HashTab;
typedef struct _HashT {
	PositionList* HeadList;
}HashT;

PositionList AddNewElementToList();
PositionList FindCountry(PositionList, char*);
PositionTree CreateTreeElement();
int ReadCountryFile(HashTab, char*);
int AddCountryToList(PositionList, char*, char*);
PositionTree AddCityToTree(PositionTree, char*, int);
PositionTree ReadCityFile(PositionTree, char*);
int PrintCountriesAndCities(PositionList);
int InOrderPrintTree(PositionTree);
int Choose(HashTab);
int FindPopulationsOfTheCitiesLargerThanX(PositionTree, int);

int AddCountryToHashTab(HashTab, char*, char*);
HashTab CreateHashTab();
int HashFunction(char*);
int AddCountryToHashTab(HashTab, char*, char*);


int main() {

	HashTab hashTab = NULL;

	hashTab = CreateHashTab();

	ReadCountryFile(hashTab, "filename.txt");

	Choose(hashTab);

	printf("Press enter to exit the program!\n");

	fseek(stdin, 0, SEEK_END);
	getchar();
	
	return EXIT_SUCCESS;
}

PositionList FindCountry(HashTab hashTab, char* country) {
	
	int index = HashFunction(country);
	PositionList headList = hashTab->HeadList[index];

	while (headList->next != NULL) {
		if (strcmp(country, headList->next->country) == 0) {
			return headList->next;
		}
		else {
			headList = headList->next;
		}
	}
	return NULL;
}

int Choose(HashTab hashTab) {
	PositionList q = NULL;
	char tmp1[MAX_SIZE];
	int tmp2;
	printf("Choose country you want to search: \n");
	scanf(" %s", tmp1);
	printf("Find all cities that have more population than x: \n");
	scanf("%d", &tmp2);
	q = FindCountry(hashTab, tmp1);
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

int ReadCountryFile(HashTab hashTab, char* filename) {
	char CountryName[MAX_SIZE] = "", FileCitiesName[MAX_SIZE] = "";

	FILE* dat = NULL;
	dat = fopen(filename, "r");
	if (!dat) {
		printf("Error while opening the file!\n");
		return EXIT_FAILURE;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %s", CountryName, FileCitiesName);
		AddCountryToHashTab(hashTab, CountryName, FileCitiesName);
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

int HashFunction(char* CountryName)
{
	int res = 0;

	for (int i = 0; i < strlen(CountryName) || i < 5; i++)
	{
		res += CountryName[i];
	}
	
	return res % HASH_TABLE_MAX_SIZE;
}

HashTab CreateHashTab()
{
	HashTab hash = NULL;
	int i = 0;

	hash = (HashTab)malloc(sizeof(HashT));

	if (hash == NULL)
	{
		printf("Couldn't allocate memory!\n");
		return NULL
	}

	hash->HeadList = (PositionList*)malloc(sizeof(PositionList) * HASH_TABLE_MAX_SIZE);
	if (hash->HeadList == NULL)
	{
		printf("Couldn't allocate memory!\n");
		return NULL;
	}

	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)
	{
		hash->HeadList[i] = AddNewElementToList();
	}

	return hash;
}

int AddCountryToHashTab(HashTab hashTab, char* CountryName, char* FileCitiesName)
{
	int index = 0;

	index = HashFunction(CountryName);

	AddCountryToList(hashTab->HeadList[index], CountryName, FileCitiesName);

	return EXIT_SUCCESS;
}