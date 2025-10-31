#include "parse.h"

int main (int argc, char * argv[]) {
    tree* head;    
    float ans; 
    float variableArray[100];
    head = findOparand (argv[1]);
    //build variable array:
    //printf("%d\n", argc);
    if (argc ==1 ){
        printf("no argments passed");
    }else if (argc == 3){
        char * var = argv[2];
        char temp[50] ;
        int count = 0, i=0;
        while (*var != '\0'){
            if(*var == '='){
                var++;
                count = 0;
                while (*var != ';'&& *var != '\0'){
                    
                    temp[count] = *var;
                    count++;
                    var++;
                }
                temp[count] = '\0';
                variableArray[i] = atof(temp);
                i++;
            }else {
                var++;
            }
        }
        for(int j =0; j<i; j++){
            //printf("%f, ", variableArray[j]);
        }
    }
    ans = calculate(head, variableArray);
    printf( "%4.2f\n", ans);
    //printf("\n");
    return 0;
}

float replace (float variableArray[100], char* data){
    if(*data == 'x'){
        data++;
        int index = atoi(data);   // convert rest of string to integer
        return variableArray[index - 1];  // x1 → index 0
    }else {
        return atof(data);
    }

}

float calculate (struct tree* root, float variableArray[100]) {
    float leftVal, righVal;
    float var;
    if (root == NULL) return 0;
    
    leftVal = calculate(root->left, variableArray);  
    righVal = calculate(root->right, variableArray);
    if (strcmp (root->data, "+") == 0){
        //printf("\nleftVal+righVal = %f\n", leftVal+righVal);
        return leftVal+righVal;
    }
    else if (strcmp (root->data, "*") == 0){
        //printf("\nleftVal(%f)*righVal = %f\n", leftVal, leftVal*righVal);
        return leftVal*righVal;
    }
    else if (strcmp (root->data, "/") == 0){
        //printf("\nleftVal/righVal = %f\n", leftVal/righVal);
        return leftVal/righVal;
    }
    else if (strcmp (root->data, "-") == 0){
        //printf("\nleftVal-righVal = %f\n", leftVal-righVal);
        return leftVal-righVal;
    }
    else {
        var = replace (variableArray, root->data);
        //printf("var = %f", var);
        return var;
    }
    
}

tree* createTreeInIt(char *data) {
    tree* newtree = malloc(sizeof(tree));
    newtree->left = NULL;
    newtree->right = NULL;
    newtree->data = malloc(strlen(data) + 1);
    strcpy(newtree->data, data); // store the whole string
    return newtree;
}

tree* findOparand (char str[] ){
    tree *root  = NULL;
    int pos = 0;
    char op = '\0';
    char *ptr = str;
    int parenDepth =0;
    //printf("\n%c 1",op);
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

    //printf("\n%s2",str);printf("\n%s 3",str);
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
        //printf("\nStrlen = %lu", strlen(str));
        //printf("\npos found %d", pos);
        //printf("\noparand found %c", op);
        char opStr[2] = { op, '\0' };
        root = createTreeInIt(opStr);
        
        if (pos>= 1){
            char LeftS[pos];
            for(int i =0; i<pos; i++){
                LeftS[i]= str[i];
            }
            LeftS[pos] = '\0';
            if(strlen(LeftS)>0){
                //printf("\n%s Left", LeftS);
                root -> left = findOparand(LeftS);
                
            } 
        }
        int right =(strlen(str)-(pos + 1));
        if (right> 0){
            char RighS[ right +1];
            for(int i= pos+1; i<=strlen(str); i++){
                RighS[i-(pos+1)] = str[i];
            }
            RighS[right] = '\0';
            if(strlen(RighS)>0){
                //printf("\n%s Righ", RighS);
                root->right = findOparand(RighS);
            }
        }
        
    }else {
        // Base case: no operators found — it’s a number
        //printf("\nLeaf operand: %s\n", str);
        return createTreeInIt(str);
    }
    return root;
}

