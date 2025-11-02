#include "parse.h"

int main (int argc, char * argv[]) {
    tree* head;    
    float ans; 
    float variableArray[10];
    if (!checkParentheses(argv[1])) {
    fprintf(stderr, "Syntax error: mismatched parentheses\n");
    return 1;
    }
    
    if (argc ==1 ){
        if (str == NULL){
            fprintf( stderr, "Error: undefined argument.\n");
            exit(1);
        }
        return -1;
    }else if(argc == 2 ){
        char *equa = argv[1];
        head = findOparand(argv[1]);
        //build variable array:
        while (*equa != '\0') {
            if (*equa == 'x') {
                fprintf(stderr, "Error: undefined argument.\n");
                freeTree(head);
                return 1;
            }
            equa++;
        }
        // No x found, just evaluate normally
        ans = calculate(head, variableArray);
        printf("%4.2f\n", ans);
        freeTree(head);
    }else if (argc == 3){
        //parse only if we find 3 args
        head = findOparand (argv[1]);
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
                if (!isValidNumber(temp)) {
                    fprintf(stderr, "Syntax error: invalid number token\n");
                    freeTree(head);
                    return 1;
                }
                variableArray[i] = atof(temp);
                i++;
            }else {
                var++;
            }
        }

        char *check = argv[1];
        while (*check != '\0') {
            if (*check == 'x') {
                check++;
                int index = atoi(check);  // e.g., from 'x2'
                if (index <= 0 || index > i) { // variable not assigned
                    fprintf(stderr, "Error: undefined argument.\n");
                    freeTree(head);
                    return 1;
                }
            } else {
                check++;
            }
        }

        ans = calculate(head, variableArray);
        printf( "%4.2f\n", ans);
        //printf("\n");
        freeTree(head);
    }
    
    return 0;
}

int checkParentheses(const char* expr) {
    int depth = 0;
    while (*expr) {
        if (*expr == '(') depth++;
        else if (*expr == ')') depth--;
        if (depth < 0) return 0; // closing parenthesis before opening
        expr++;
    }
    return depth == 0; // must end at 0
}

int isValidNumber(const char* str) {
    int dotCount = 0;
    if (*str == '\0') return 0;
    if (*str == '+' || *str == '-') str++; // optional sign
    if (*str == '\0') return 0;

    while (*str) {
        if (*str == '.') {
            dotCount++;
            if (dotCount > 1) return 0; // multiple dots
        } else if (!(*str >= '0' && *str <= '9')) {
            return 0; // invalid character
        }
        str++;
    }
    return 1;
}

void freeTree(struct tree* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node->data);
    free(node);
}

float replace (float variableArray[10], char* data){
    if (*data != 'x') {
        if (!isValidNumber(data)) {
            fprintf(stderr, "Syntax error: invalid number token\n");
            exit(1);
        }
        return atof(data);
    }
    if (*data == 'x') {
        data++;
        int index = atoi(data);
        if (index <= 0 || index > 9) {
            fprintf(stderr, "Error: variable index out of range.\n");
            exit(1);
        }
        return variableArray[index - 1];
    } else {
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
        if (righVal == 0.0f) {
            fprintf(stderr, "Error: division by zero.\n");
            exit(1);
        }
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
    if (str == NULL){
        fprintf( stderr, "Error: undefined argument.\n");
        exit(1);
    }
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
        if (str[0] != 'x' && !isValidNumber(str)) {
            fprintf(stderr, "Syntax error: invalid number token\n");
            exit(1);
        }
        return createTreeInIt(str);
    }
    return root;
}

