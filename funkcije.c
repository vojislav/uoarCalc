#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

#include "funkcije.h"

/********************************************************************
 _               _                 _       _     _                 _
| |__  _ __ ___ (_) ___ __ _ _ __ (_)  ___(_)___| |_ ___ _ __ ___ (_)
| '_ \| '__/ _ \| |/ __/ _` | '_ \| | / __| / __| __/ _ \ '_ ` _ \| |
| |_) | | | (_) | | (_| (_| | | | | | \__ \ \__ \ ||  __/ | | | | | |
|_.__/|_|  \___// |\___\__,_|_| |_|_| |___/_|___/\__\___|_| |_| |_|_|
              |__/

**********************************************************************/


void brojToUpper (char broj[]){
	int duzina = strlen(broj);
	for (int i = 0; i < duzina; i++){
		if (broj[i] >= 'a' && broj[i] <= 'z'){
			broj[i] = toupper(broj[i]);
		}
	}
	return ;
}

int provera (char broj[], int osnova){
	osnova = abs(osnova);
	char cifre[] = "0123456789ABCDEF", trenCifra;
	int duzina = strlen(broj), pozicija;

	for (int i = 0; i < duzina; i++){
		trenCifra = broj[i];
		if (trenCifra != '.'){
			pozicija = strchr(cifre, trenCifra) - cifre;
			if (pozicija >= osnova)
				return 0;
		}
	}

	return 1;
}

double uDekadni(char broj[], int osnovaIz){
	char hex[]="0123456789ABCDEF";
	int duzina = strlen(broj), ceoDeo = 0, cifra = 0, pocetak = 0, index = 0;
	double razlomDeo = 0;
	if (strchr(broj, '.'))
		pocetak = strchr(broj, '.') - broj;

	else
		pocetak = 0;

	if (pocetak){  // ima tacka
		for (int i = pocetak-1; i >= 0; i--){
			cifra = strchr(hex, broj[i]) - hex;
			ceoDeo += cifra * pow(osnovaIz, index);
			index++;
		}
		index = 1;
		for (int i = pocetak+1; i < duzina; i++){
			cifra = strchr(hex, broj[i]) - hex;
			razlomDeo += cifra * pow(osnovaIz, -index);
			index++;
		}
		//printf("%lf", ceoDeo + razlomDeo);
		return ceoDeo + razlomDeo;

	}
	else{
		index = duzina - 1;
		for (int i = 0; i < duzina; i++){
			cifra = strchr(hex, broj[i]) - hex;
			ceoDeo += cifra * pow(osnovaIz, index);
			index--;
		}
		//printf("%d", ceoDeo);
		return ceoDeo;
	}
}

void izDekadnog(double broj, int osnovaU){
	char hex[]="0123456789ABCDEF";
	char prevod[64], i = 0;
	int ceoDeo = broj;
	if (ceoDeo){
		while (ceoDeo){
			prevod[i] = hex[ceoDeo % osnovaU];
			ceoDeo /= osnovaU;
			i++;
		}
		for (int j = i-1; j >= 0; j--){
			printf("%c", prevod[j]);
			prevod[j] = ' ';
		}
	}
	else
		printf("0");
	i = 0;
	if (fmod(broj, 1.0) != 0){
		printf(".");
		double razlom = fmod(broj, 1.0);
		while (razlom){
			razlom *= osnovaU;
			prevod[i] = hex[(int)razlom];
			printf("%c", prevod[i]);
			razlom -= (int)razlom;
			i++;
		}
	}
	return ;
}


void brSistemi(void){
	char broj[32];
	char noviBroj[32];
	int osnovaU = 0, osnovaIz = 0;
	double realanBroj = 0;
	printf("Uneti mesoviti ili ceo broj, osnovu tog broja i osnovu sistema u koji se prevodi (npr. 107.125 10 6): ");
	scanf("%s %d %d", broj, &osnovaIz, &osnovaU); // uneti broj se gleda kao string

	brojToUpper(broj);

	if (osnovaIz > 16 || osnovaU > 16){
		printf("Maksimalna dozvoljena osnova je 16.");
		return ;
	}

	if (!provera(broj, osnovaIz)){
		printf("Broj %s nije validan broj u sistemu osnove %d.", broj, osnovaIz);
		return ;
	}

	if (osnovaIz == 10){				  // ukoliko se prebacuje iz dekadnog
		sscanf(broj, "%lf", &realanBroj); // tj. nema slova u sebi tj. broj je, a ne string,
		izDekadnog(realanBroj, osnovaU);  // da iz stringa izvuce broj kao double
	}

	else if (osnovaU == 10)
		printf("%lf", uDekadni(broj, osnovaIz));

	else{
		uDekadni(broj, osnovaIz);
		izDekadnog(uDekadni(broj, osnovaIz), osnovaU);
	}
	printf("\n");

	return ;
}


/**********************************************
 ____    ____    ____
|  _ \  | __ )  / ___|
| |_) | |  _ \  \___ \
|  _ <  | |_) |  ___) |
|_| \_\ |____/  |____/

***********************************************/

void ispis(int *ostaci, int n){
	for (int i = 0; i < n; i++){
		printf("%d ", ostaci[i]);
	}
	printf("\n");

	return ;
}

int *unos(int n){
	int *ostaci = malloc(n * sizeof(int));
	if (ostaci == NULL)
		exit(1);
	for (int i = 0; i < n; i++){
		scanf("%d", &ostaci[i]);
	}

	return ostaci;
}


int *uRBS(int broj, int n, int *ostaciSistema){
	int *ostaciPrevoda = malloc(n * sizeof(int));
	if (ostaciPrevoda == NULL)
		exit(1);

	if (broj >= 0){
		for (int i = 0; i < n; i++)
			ostaciPrevoda[i] = broj % ostaciSistema[i];
	}
	else {
		for (int i = 0; i < n; i++)
			ostaciPrevoda[i] = ostaciSistema[i] - (abs(broj) % ostaciSistema[i]);
	}
	return ostaciPrevoda;

}

int uDek(int n, int *ostaciSistema, int *ostaciBroja){
	int t = 1, broj = 0, moduo = 1;
	int *tezine = (int *)malloc(n * sizeof(int));
	if (tezine == NULL)
		exit(1);

	for (int i = 0; i < n; i++){  // ovaj deo trazi tezine pozicija u RBS sistemu
		t = 1;
		for (int j = 1; j < n; j++){ 		// i for petlja ide kroz brojeve osnove RBS-a, a j petlja uzima ostale brojeve
			t *= ostaciSistema[(i+j)%n];	// brojevi osim i su deljivi s tim brojem, pa je t oblika svih njihovih proizvoda
		}									// paralela sa pravim nacinom radjenja zadatka, ovo je deo gde prvo na najvisu poziciju stavimo
		moduo *= ostaciSistema[i];			// da je kongruentan sa 1 dok su ostale 0 tj. deljivi s tim brojem, t je potom oblika tog broja

		for (int k = 1; k < ostaciSistema[i]; k++){		// kad se nadje kog je oblika broj, trazi se za koje k ce taj broj biti kongruentan 1
			if ( (t * k) % ostaciSistema[i] == 1){
				t *= k;
				break;
			}
		}

		broj += t * ostaciBroja[i];			// krajnja vrednost ce biti jednaka ostacima broja pomnozenim tezinama
	}

	return broj % moduo;
}

int *saberi(int *ostaci1, int *ostaci2, int n, int *ostaciSistema){
	int *ostaciPrevoda = malloc(n * sizeof(int));
	if (ostaciPrevoda == NULL)
		exit(1);

	for (int i = 0; i < n; i++){
		ostaciPrevoda[i] = (ostaci1[i] + ostaci2[i]) % ostaciSistema[i];
	}

	return ostaciPrevoda;
}

int *oduzmi(int *ostaci1, int *ostaci2, int n, int *ostaciSistema){
	int *ostaciPrevoda = malloc(n * sizeof(int));
	if (ostaciPrevoda == NULL)
		exit(1);

	for (int i = 0; i < n; i++){
		ostaciPrevoda[i] = (ostaci1[i] - ostaci2[i]) % ostaciSistema[i];
		if (ostaciPrevoda[i] < 0)
			ostaciPrevoda[i] = (ostaciSistema[i] + ostaciPrevoda[i]) % ostaciSistema[i];
	}

	return ostaciPrevoda;
}

int *mnozi(int *ostaci1, int *ostaci2, int n, int *ostaciSistema){
	int *ostaciPrevoda = malloc(n * sizeof(int));
	if (ostaciPrevoda == NULL)
		exit(1);
	for (int i = 0; i < n; i++)
		ostaciPrevoda[i] = (ostaci1[i] * ostaci2[i]) % ostaciSistema[i];

	return ostaciPrevoda;
}

void dekadni(void){
	int opcija, broj1, broj2, n, *ostaciSistema, *ostaci1, *ostaci2;
	printf("1) Prevod u RBS\n"
		   "2) Sabiranje\n"
		   "3) Oduzimanje\n"
		   "4) Mnozenje\n");
	scanf("%d", &opcija);
	switch (opcija){
		case 1:
			printf("Uneti broj: ");
			scanf("%d", &broj1);
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);
			ispis(uRBS(broj1, n, ostaciSistema), n);
			break;

		case 2:
			printf("Uneti prvi broj: ");
			scanf("%d", &broj1);
			printf("Uneti drugi broj: ");
			scanf("%d", &broj2);
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);

			ostaci1 = uRBS(broj1, n, ostaciSistema);
			ostaci2 = uRBS(broj2, n, ostaciSistema);

			ispis(saberi(ostaci1, ostaci2, n, ostaciSistema), n);

			break;

		case 3:
			printf("Uneti prvi broj: ");
			scanf("%d", &broj1);
			printf("Uneti drugi broj: ");
			scanf("%d", &broj2);
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);

			ostaci1 = uRBS(broj1, n, ostaciSistema);
			ostaci2 = uRBS(broj2, n, ostaciSistema);

			ispis(oduzmi(ostaci1, ostaci2, n, ostaciSistema), n);
			break;

		case 4:
			printf("Uneti prvi broj: ");
			scanf("%d", &broj1);
			printf("Uneti drugi broj: ");
			scanf("%d", &broj2);
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);

			ostaci1 = uRBS(broj1, n, ostaciSistema);
			ostaci2 = uRBS(broj2, n, ostaciSistema);

			ispis(mnozi(ostaci1, ostaci2, n, ostaciSistema), n);
			break;
	}

	return ;
}

void aritUnosDek(int *broj1, int *broj2, int *n, int *ostaciSistema){
			printf("Uneti prvi broj: ");
			scanf("%d", broj1);
			printf("Uneti drugi broj: ");
			scanf("%d", broj2);
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(*n);

			return ;
}

void rbsBr(void){
	int opcija, broj, n, *ostaciSistema, *ostaci1, *ostaci2;
	printf("1) Prevod u dekadni\n"
		   "2) Sabiranje\n"
		   "3) Oduzimanje\n"
		   "4) Mnozenje\n");
	scanf("%d", &opcija);
	switch (opcija){
		case 1:
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);
			printf("Uneti ostatke broja: ");
			ostaci1 = unos(n);
			printf("%d\n", uDek(n, ostaciSistema, ostaci1));
			break;

		case 2:
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);
			printf("Uneti ostatke prvog broja: ");
			ostaci1 = unos(n);
			printf("Uneti ostatke drugog broja: ");
			ostaci2 = unos(n);
			ispis(saberi(ostaci1, ostaci2, n, ostaciSistema), n);
			break;

		case 3:
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);
			printf("Uneti ostatke prvog broja: ");
			ostaci1 = unos(n);
			printf("Uneti ostatke drugog broja: ");
			ostaci2 = unos(n);
			ispis(oduzmi(ostaci1, ostaci2, n, ostaciSistema), n);
			break;

		case 4:
			printf("Uneti broj ostataka sistema: ");
			scanf("%d", &n);
			printf("Uneti ostatke sistema: ");
			ostaciSistema = unos(n);
			printf("Uneti ostatke prvog broja: ");
			ostaci1 = unos(n);
			printf("Uneti ostatke drugog broja: ");
			ostaci2 = unos(n);
			ispis(mnozi(ostaci1, ostaci2, n, ostaciSistema), n);
			break;
	}

	free(ostaciSistema);
	free(ostaci1);
	free(ostaci2);
	return ;
}

void rbs(void){
	int opcija;
	printf("1) Dekadni brojevi\n"
		   "2) RBS brojevi\n");
	scanf("%d", &opcija);
	switch (opcija){
		case 1:
			dekadni();
			break;
		case 2:
			rbsBr();
			break;
	}
}
