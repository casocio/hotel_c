#include<stdio.h>
#include<stdlib.h>
//richiami delle funzioni
void Principale();
void Profilo();

//Menù principale del programma
void Principale(){
	int n;
	printf("Benvenuto UTENTE, scegli cosa desideri fare:\n0.Esci dal programma\n1.Profilo\n2.Acquista\n3.Carrello\n");
scanf("%d",&n);
switch(n){
	case 0:
		exit(1);
	break;
	case 1:
		Profilo();
	break;
	case 2:
		
	break;
	case 3:
		
	break;
}
}
//menù del profilo
void Profilo(){
	int n;
printf("Scegli cosa desideri fare:\n0.Esci dal programma\n1.C\n2.Pagamenti\n3.Torna Indietro\n");
printf("Carta di Credito:");
scanf("%d",&n);
if(n==0){exit(1);}
if(n==1){Principale()}
}
	
}





main(){
	int n;
Principale();

}

