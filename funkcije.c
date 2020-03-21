#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

#include "funkcije.h"

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
