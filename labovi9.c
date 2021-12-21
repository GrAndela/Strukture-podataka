#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN 10
#define MAX 90

struct _CvorStabla;
typedef struct _CvorStabla* Stablo;
typedef struct _CvorStabla {
	int number;
	Stablo left;
	Stablo right;
} CvorStabla;

struct _CvorListe;
typedef struct _CvorListe* Pozicija;
typedef struct _CvorListe {
	int number;
	Pozicija next;
} CvorListe;

Stablo StvoriStablo(int);
int InOrderPrint();
int InOrderPrintUListu(Pozicija, Stablo);
Stablo Insert(int, Stablo);
int Replace(Stablo);
int RandomStablo(Stablo);
int NadiRandomBroj(int, int);
int UpisiUDatoteku(Stablo, char*);

Pozicija StvoriListu();
int DodajNaKrajListe(int, Pozicija);
int IzbrisiListu(Pozicija);

int main() {
	
	srand(time(NULL));
	int duljina = 0, i = 0, num = 0;
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 }; 
	Stablo korijen = NULL;

	duljina = sizeof(niz) / sizeof(int);
	for (i = 0; i < duljina; i++) {
		korijen = Insert(niz[i], korijen);
	}

	printf("Originalno stablo: ");
	InOrderPrint(korijen);
	printf("\n");

	UpisiUDatoteku(korijen, "ispis.txt");

	printf("Sumirano stablo: ");
	Replace(korijen);
	InOrderPrint(korijen);
	printf("\n");

	UpisiUDatoteku(korijen, "ispis.txt");

	printf("Random stablo: ");
	RandomStablo(korijen);
	InOrderPrint(korijen);

	UpisiUDatoteku(korijen, "ispis.txt");

	return EXIT_SUCCESS;
}

int UpisiUDatoteku(Stablo p, char* imeDat) {
	Pozicija head = NULL;
	head = StvoriListu();

	InOrderPrintUListu(head, p);


	FILE* dat = NULL;
	dat = fopen(imeDat, "a"); 
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	while (head->next != NULL) {
		head = head->next;
		fprintf(dat, "%d ", head->number);
	}
	fprintf(dat, "\n");
	fclose(dat);
	IzbrisiListu(head);
	return 0;
}

int InOrderPrintUListu(Pozicija head, Stablo p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {

		InOrderPrintUListu(head, p->left);
		DodajNaKrajListe(p->number, head);
		InOrderPrintUListu(head, p->right);
	}
	return EXIT_SUCCESS;
}

int DodajNaKrajListe(int broj, Pozicija head) {
	Pozicija q = NULL;
	q = StvoriListu();

	while (head->next != NULL) {
		head = head->next;
	}

	q->number = broj;
	q->next = head->next;
	head->next = q;
	return EXIT_SUCCESS;
}

int IzbrisiListu(Pozicija head) {
	Pozicija tmp = NULL;
	while (head->next) {
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}
	return EXIT_SUCCESS;
}

Pozicija StvoriListu() {
	Pozicija q = malloc(sizeof(CvorListe));
	if (!q) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->number = 0;
	q->next = NULL;
	return q;
}

int RandomStablo(Stablo p) {
	if (p == NULL) {
		return 0;
	}
	p->number = NadiRandomBroj(MIN, MAX);
	if (p->left) {
		RandomStablo(p->left);
	}
	if (p->right) {
		RandomStablo(p->right);
	}
}

int NadiRandomBroj(int min, int max) {
	int r = (rand() % (max - min + 1)) + min;
	return r;
}

int Replace(Stablo p) {
	int tmp = 0;
	if (p == NULL) {
		return 0;
	}
	tmp = p->number;
	p->number = Replace(p->left) + Replace(p->right);
	return p->number + tmp;
}

Stablo StvoriStablo(int broj) {
	Stablo q = malloc(sizeof(CvorStabla));
	if (!q) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->number = broj;
	q->left = NULL;
	q->right = NULL;
	return q;
};

Stablo Insert(int broj, Stablo p) {
	if (p == NULL) {
		p = StvoriStablo(broj);
	}
	else {
		if (broj == p->number) {
			p->left = Insert(broj, p->left);
		}
		if (broj < p->number) {
			p->right = Insert(broj, p->right);
		}
		if (broj > p->number) {
			p->left = Insert(broj, p->left);
		}
	}
	return p;
}

int InOrderPrint(Stablo p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {

		InOrderPrint(p->left);
		printf("%d\t", p->number);
		InOrderPrint(p->right);
	}
	return EXIT_SUCCESS;
}