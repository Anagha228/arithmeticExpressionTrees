#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct tree {
    int data;
    struct tree* left;
    struct tree* right;
} tree;


void findOparand (char str[]);
tree* createTreeInIt (int data);
tree* insertLeft (tree** head, int data);
tree* insertRight(tree** head, int data);
void inorderTraversal(struct tree* root);
void preorderTraversal(struct tree* root);
void postorderTraversal(struct tree* root);


int main (int argc, char * argv[]){
    tree* head; 

    printf("\n%s\n", argv[1]); 
    if(strlen(argv[1])>0){
        findOparand (argv[1]);
    }
    
    // tree* n0 = insertLeft(&head, '/');
    // tree* n1 = insertLeft(&n0, '+');
    // tree* n3 = insertLeft(&n1, 'X');
    // tree* n4 = insertRight(&n1, 'Y');
    // tree* n2 = insertRight(&n0, 'Z');
    //printf("\n%c\n", head->data);
    //inorderTraversal(n0);

    return 0;
}

tree* createTreeInIt (int data){
    tree* newtree = (tree*)malloc (sizeof(tree));
    newtree->data = data;
    newtree->left = NULL;
    newtree->right = NULL;
    return newtree;
}

tree* insertLeft (tree** head, int data){
    tree* childTree = createTreeInIt (data);
    if (*head == NULL){
        *head = childTree;
        return childTree;
    }else {
        
        (*head)->left = childTree;
    }
    return childTree;
}
tree* insertRight(tree** head, int data){
    tree* childTree = createTreeInIt (data);
    if (*head == NULL){
        *head = childTree;
        return childTree;
    }else {
        (*head)->right = childTree;
    }
    return childTree;
}
//Inorder traversal
void inorderTraversal(struct tree* root) {
  if (root == NULL) return;
  inorderTraversal(root->left);  
  printf("%c ->", root->data);
  inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct tree* root) {
  if (root == NULL) return;
  printf("%c ->", root->data);
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct tree* root) {
  if (root == NULL) return;
  postorderTraversal(root->left);  
  postorderTraversal(root->right);
  printf("%c ->", root->data);
}



void findOparand (char str[]){
    int pos =0;
    char * ptr = str;
    //bool found = 0; 
    while (*ptr != '/'&& *ptr != '\0'){
        ++(pos);
        ++ptr;
    }
    if(*ptr != '/'){
        ptr = str;
        pos = 0;
        while (*ptr != '+'&& *ptr != '\0'){
            ++(pos);
            ++ptr;
        }
    }
    if (str[pos]== '/' || str[pos]=='+'){
        printf("\nStrlen = %lu", strlen(str));
        printf("\npos found %d", pos);
        printf("\noparand found %c", str[pos]);
        
        if (pos>= 1){
            char LeftS[pos];
            for(int i =0; i<pos; i++){
                LeftS[i]= str[i];
            }
            LeftS[pos] = '\0';
            if(strlen(LeftS)>0){
                printf("\n%s Left", LeftS);
                findOparand(LeftS);
                
            }
            
        }
        int right =(strlen(str)-(pos + 1));
        if (right> 0){
            char RighS[ right +1];
            for(int i= pos+1; i<=strlen(str); i++){
                RighS[i-(pos+1)] = str[i];
                //printf("\n%c right side", str[i]);
            }
            RighS[right+1] = '\0';
            if(strlen(RighS)>0){
                printf("\n%s Righ", RighS);
                findOparand(RighS);
            }
        }
        
        //printf("\nStrlen = %lu\n", strlen(str));
    }
}


