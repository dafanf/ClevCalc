#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct treeNode{
    int isOperator;
    int data;//flag=0 
    char mathOperator;//flag=1
    struct treeNode * lChild;//Left child 
    struct treeNode * rChild;//Right child 
};

int count(struct treeNode *root);
//Method untuk menghitung total dari proses proses dalam tree
int check(char mathExpression[], int firstIndex, int lastIndex);
struct treeNode * makeTree(char mathExpression[], int firstIndex, int lastIndex);
