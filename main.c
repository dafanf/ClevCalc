#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "temperature.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void clevCalcMenu(){
	printf("\n------- Menu Aplikasi ClevCalc -------\n");
    printf("1. Kalkulator Ilmiah \n");
    printf("2. Suhu Konverter \n");
    printf("3. Keluar \n");
    printf("------------------------------\n");
    printf("Pilih nomor menu: ");
}
int main(int argc, char *argv[]) {
	int pil;
	clevCalcMenu();
	scanf("%d",&pil);
    fflush(stdin);
    if(pil==1){
        char expression[200];
        printf("Please enter an expression:");
        scanf("%s",expression);
        printf("The expression you entered is: %s\n",expression);
        struct treeNode* binaryTree=(struct treeNode *)malloc(sizeof(struct treeNode));
        binaryTree = makeTree(expression,0,strlen(expression)-1);
        printf("Your result is %d\n",count(binaryTree));
	}
	else if(pil==2){
		
	}
	else{
		exit(0);
	}
    return 0;
}
