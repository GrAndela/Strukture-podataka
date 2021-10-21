#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_BOD (100)

typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaIzDatoteke(char* NazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int BrojStudenata, char* NazivDatoteke);

int IspisStudenata(student* studenti, int BrojStudenata) {

	int max = 0;
	double Relativni = 0;

	max = MaksBrojBodova(studenti, BrojStudenata);
	for (int i = 0; i < BrojStudenata; i++){

		printf("%s	%s	%lf %lf\n",
			studenti[i].ime,
			studenti[i].prezime,
			studenti[i].bodovi / MAX_BOD * 100,
			studenti[i].bodovi / studenti[max].bodovi * 100);
	}

	return 1;
}
int MaksBrojBodova(student* studenti, int BrojStudenata) {
	int Max = 0;
	int i;

	for (i = 1; i < BrojStudenata; i++) {
		if (studenti[Max].bodovi < studenti[i].bodovi)
			Max = i;
	}

	return Max;
}

int main() {

	student* studenti=NULL;
	char* dat= "studentii.txt";
	int Brojstudenata =0;

	Brojstudenata = ProcitajBrojRedakaIzDatoteke(dat);
	if (Brojstudenata == -1)
		return 0;

	studenti = AlocirajMemorijuIProcitajStudente(Brojstudenata, dat);
	if (!studenti)
		return 0;

	IspisStudenata(studenti, Brojstudenata);


	return 0;
}
int ProcitajBrojRedakaIzDatoteke(char* NazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(NazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska!\n");
		return -1;
	}
	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	fclose(datoteka);

	return brojac;
}
student* AlocirajMemorijuIProcitajStudente(int BrojStudenata, char* NazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(sizeof(student) * BrojStudenata);
	datoteka = fopen(NazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska!\n");
		return NULL;
	}
	while (!feof(datoteka)) {
		fscanf(datoteka, "%s %s %lf",
			studenti[brojac].ime,
			studenti[brojac].prezime,
			&studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

