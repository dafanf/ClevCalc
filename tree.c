#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "tree.h"
#define MAX 0x3f3f3f3f

int count(struct treeNode *root){
    if(root->isOperator==1){
        switch(root->mathOperator){
            case '+':{
                return count(root->lChild)+count(root->rChild);
                break;
            }
            case '-':{
                return count(root->lChild)-count(root->rChild);
                break;
            }
            case '/':{
                return count(root->lChild)/count(root->rChild);
                break;
            }
            case '*':{
                return count(root->lChild)*count(root->rChild);
                break;
            }
            case '^':{
                return pow(count(root->lChild),count(root->rChild));
                break;
            }
        }
    }
    return root->data;
}
int check(char mathExpression[],int firstIndex,int lastIndex){
    int i;
    int sum=0;
    int isOperator=1;
    if(mathExpression[firstIndex]=='-'){
        isOperator=-1;
        firstIndex++;
    }
    for(i=firstIndex;i<=lastIndex;i++){
        if(!isdigit(mathExpression[i])){
			return MAX;	
		}
        sum=sum*10+mathExpression[i]-'0';
    }
    return sum*isOperator;
}
void postOrder(struct treeNode *root){
    if(root){
        postOrder(root->lChild);
        postOrder(root->rChild);
        if(root->isOperator==0){
            printf("%d ",root->data);
        }
        else{
            printf("%c ",root->mathOperator);
        }       
    }
} 
struct treeNode * makeTree(char mathExpression[],int firstIndex,int lastIndex){
   	struct treeNode * root=(struct treeNode *)malloc(sizeof(struct treeNode));
    int posPlusOrSub=0;//Posisi dari operator penjumlahan (-) dan pengurangan (-) 
    int numPlusOrSub=0;//Jumlah dari operator penjumlahan(+) dan pengurangan (-) 
    int posDivOrMul=0;//Posisi dari operator perkalian(*) dan pembagian (/) 
    int numDivOrMul=0;//Jumlah dari operator perkalian (*) dan pembagian(/)
	int posExp=0;//Posisi dari operator pangkat (^)
	int numExp=0;//Jumlah operator pangkat (^)
    int num;
    num=check(mathExpression,firstIndex,lastIndex);
	//Memeriksa jika hanya angka yang menjadi input     
    if(num!=MAX){
        root->isOperator=0;
        root->data=num;
        root->lChild=NULL;
        root->rChild=NULL;
        return root;
    }
    //There are operators 
    int in_brackets=0;//Identifiers not in parentheses
	int k; 
    for(k=firstIndex;k<=lastIndex;k++){
        if(mathExpression[k]=='('){
            in_brackets++;
        }
        else if(mathExpression[k]==')'){
            in_brackets--;
        }
        if(!in_brackets){//Outside the brackets 
            if(mathExpression[k]=='+'||mathExpression[k]=='-'){
                posPlusOrSub=k;
                numPlusOrSub++;
            }
            else if(mathExpression[k]=='*'||mathExpression[k]=='/'){
                posDivOrMul=k;
                numDivOrMul++;
            }
            else if(mathExpression[k]=='^'){
                posExp=k;
                numExp++;
            }
        }
    }
    int pos_root;
    
    //Mencari root dengan node penjumlahan dan pengurangan
    if(numPlusOrSub){
        pos_root=posPlusOrSub;
    }
    //Mencari root dengan node penjumlahan dan pengurangan
    else if(numDivOrMul){
        pos_root=posDivOrMul;
    }
    //Mencari root dengan node perpangkatan
    else if(numExp){
        pos_root=posExp;
    }
    //Jika root tidak dapat ditemukan
    else{
        return makeTree(mathExpression,firstIndex+1,lastIndex-1);
    }
    root->isOperator=1;
    root->mathOperator=mathExpression[pos_root];
    root->lChild = makeTree(mathExpression,firstIndex,pos_root-1);
    root->rChild = makeTree(mathExpression,pos_root+1,lastIndex);
    return root;
}
