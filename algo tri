#include <stdio.h>

void print(int tab[], int a){
	for(int i=0;i<a;i++){
		printf("%d ",tab[i]);
		}
	printf("\n");
	}
	
void mergemoi(int tab[],int liun[], int lide[], int tun, int tde){
	int i=0,j=0,k=0;
	while(i<tun && j<tde){
		if (liun[i]< lide[j]){
			tab[k]=liun[i];
			i++;
			k++;
			}
		else{
			tab[k]=lide[j];
			j++;
			k++;
			}
		}
	while (i<tun){
		tab[k]=liun[i];
		i++;
		k++;
		}
	while (j<tde){
		tab[k]=lide[j];
		j++;
		k++;
		}
	//print(tab, tun+tde);
	}
	
void msort(int tab[], int l){
	if (l>1){
		int i,k=0;
		int mil=l/2;
		int tun = l - mil;
		int tde = l - tun;
		int liun[tun];
		int lide[tde];
		for (i=0;i<tun;i++){
			liun[k] = tab[k];
			k++;
			}
		for (i=0;i<tde;i++){
			lide[i] = tab[k];
			k++;
			}
		msort(liun, tun);
		msort(lide, tde);
		//printf("test\n");
		mergemoi(tab,liun,lide, tun, tde);
		}
	}

int main(){
	int l=7;
	int tab[7]={38,62,45,64,38,91,91};
	msort(tab, l);
	print(tab,l);
	}
