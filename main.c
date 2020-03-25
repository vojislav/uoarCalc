#include<stdio.h>
#include "funkcije.h"

int main(){
	int opcija;
	printf("Izabrati oblast:\n");
	printf("1) Brojcani sistemi\n"
		   "2) RBS\n");
	scanf("%d", &opcija);
	switch (opcija){
		case 1:
			brSistemi();
			break;
		case 2:
			rbs();
			break;
	}
	return 0;
}
