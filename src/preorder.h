#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct tree {
    char data;
    struct tree* left;
    struct tree* right;
} tree;


tree* findOparand (char str[]);
tree* createTreeInIt (int data);
tree* insertLeft (tree** head, int data);
tree* insertRight(tree** head, int data);
void inorderTraversal(struct tree* root);
void preorderTraversal(struct tree* root);


