#include "parse.h"

int main (int argc, char * argv[]){
    tree* head; 

    printf("\n%s\n", argv[1]); 
    
    head = findOparand (argv[1]);
    preorderTraversal(head);
    printf("\n\n");
    return 0;
}

tree* createTreeInIt(char *data) {
    tree* newtree = malloc(sizeof(tree));
    newtree->left = NULL;
    newtree->right = NULL;
    newtree->data = malloc(strlen(data) + 1);
    strcpy(newtree->data, data); // store the whole string
    return newtree;
}

// tree* insertLeft (tree** head, int data){
//     tree* childTree = createTreeInIt (data);
//     if (*head == NULL){
//         *head = childTree;
//         return childTree;
//     }else {
        
//         (*head)->left = childTree;
//     }
//     return childTree;
// }

// tree* insertRight(tree** head, int data){
//     tree* childTree = createTreeInIt (data);
//     if (*head == NULL){
//         *head = childTree;
//         return childTree;
//     }else {
//         (*head)->right = childTree;
//     }
//     return childTree;
// }

// Preorder traversal
void preorderTraversal(struct tree* root) {
  if (root == NULL) return;
  printf("%s ", root->data);
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

//parse operators
tree* findOparand (char str[] ){
    tree *root  = NULL;
    int pos = 0;
    char op = '\0';
    char *ptr = str;
    int parenDepth =0;
    printf("\n%c 1",op);
    int len = strlen(str);
    if (len >= 2 && str[0] == '(' && str[len - 1] == ')') {
        parenDepth = 0;
        int matched = 1;
        for (int i = 0; i < len; i++) {
            if (str[i] == '(') parenDepth++;
            else if (str[i] == ')') parenDepth--;
            if (parenDepth == 0 && i < len - 1) {
                matched = 0; // there are inner characters outside the outer parentheses
                break;
            }
        }
        if (matched) {
            char inner[len - 1];
            strncpy(inner, str + 1, len - 2);
            inner[len - 2] = '\0';
            return findOparand(inner); // recurse without outer parentheses
        }
    }

    printf("\n%s2",str);printf("\n%s 3",str);
    // ----- Pass 1: Look for * or / -----
    while (*ptr != '\0') {
        if (*ptr == '('){
            parenDepth++;
        } 
        else if (*ptr == ')') {
            parenDepth--;
        }
        if (parenDepth == 0 && ((*ptr == '*') || *ptr == '/')) {
            op = *ptr;
            break;
        }
        ptr++;
        pos++;
        
    }
    
    // If no * or / found, reset and look for + or -
    if (op=='\0') {
        pos = 0;
        parenDepth = 0;
        ptr = str;
        while (*ptr != '\0') {
            if (*ptr == '('){
                parenDepth++;
            } 
            else if (*ptr == ')') {
                parenDepth--;
            }
            if (parenDepth == 0 && ((*ptr == '+') || *ptr == '-')) {
                op = *ptr;
                break;
            }
            ptr++;
            pos++;
        }
    }

    // If we found an operator
    if (op != '\0') {
        printf("\nStrlen = %lu", strlen(str));
        printf("\npos found %d", pos);
        printf("\noparand found %c", op);
        char opStr[2] = { op, '\0' };
        root = createTreeInIt(opStr);
        
        if (pos>= 1){
            char LeftS[pos];
            for(int i =0; i<pos; i++){
                LeftS[i]= str[i];
            }
            LeftS[pos] = '\0';
            if(strlen(LeftS)>0){
                printf("\n%s Left", LeftS);
                root -> left = findOparand(LeftS);
                
            } 
        }
        int right =(strlen(str)-(pos + 1));
        if (right> 0){
            char RighS[ right +1];
            for(int i= pos+1; i<=strlen(str); i++){
                RighS[i-(pos+1)] = str[i];
            }
            RighS[right+1] = '\0';
            if(strlen(RighS)>0){
                printf("\n%s Righ", RighS);
                root->right = findOparand(RighS);
            }
        }
        
    }else {
        // Base case: no operators found — it’s a number
        printf("\nLeaf operand: %s\n", str);
        return createTreeInIt(str);
    }
    return root;
}




