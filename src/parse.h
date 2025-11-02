#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct tree {
    char* data;
    struct tree* left;
    struct tree* right;
} tree;


tree* findOparand (char str[]);
tree* createTreeInIt (char data[]);
tree* insertLeft (tree** head, int data);
tree* insertRight(tree** head, int data);
void inorderTraversal(struct tree* root);
void preorderTraversal(struct tree* root, int *firstPrint);
void postorderTraversal(tree* root, int *firstPrint);
float calculate (struct tree* root, float variableArray[100]);
float replace (float variableArray[100], char* data);
void freeTree (struct tree* node);
int checkParentheses(const char* expr);
int isValidNumber(const char* str);

