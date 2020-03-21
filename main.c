#include<stdio.h>
#include "funkcije.h"

int main(){
	int opcija;
	printf("Izabrati oblast:\n");
	printf("1) Brojcani sistemi\n");
	scanf("%d", &opcija);
	switch (opcija){
		case 1:
			brSistemi();
	}
	return 0;
}
