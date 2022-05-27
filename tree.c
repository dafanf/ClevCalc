#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
        if(!isdigit(mathExpression[i])) return MAX;
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
    int cnt=0;
    int m;
    int i;
    if(firstIndex>lastIndex) return NULL;
    int posPlusOrSub=0;//Position of plus and minus signs 
    int numPlusOrSub=0;//Number of plus and minus signs 
    int posDivOrMul=0;//Multiply and divide sign position 
    int numDivOrMul=0;//Number of multiplication and division numbers
	int posExpOrSqrt=0;
	int numExpOrSqrt=0;
    int num;
    num=check(mathExpression,firstIndex,lastIndex);     
    if(num!=0x3f3f3f3f){//Only numbers 
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
                posDivOrMul=k;//Multiply and divide sign position 
                numDivOrMul++;//Number of multiplication and division numbers 
            }
        }
    }
    int pos_root;
    //Find the root node with addition and subtraction 
    if(numPlusOrSub){
        pos_root=posPlusOrSub;
    }
    else if(numDivOrMul){
        pos_root=posDivOrMul;
    }
    else{//The root cannot be found 
        return makeTree(mathExpression,firstIndex+1,lastIndex-1);
    }
    root->isOperator=1;
    root->mathOperator=mathExpression[pos_root];
    root->lChild = makeTree(mathExpression,firstIndex,pos_root-1);
    root->rChild = makeTree(mathExpression,pos_root+1,lastIndex);
    return root;
}
