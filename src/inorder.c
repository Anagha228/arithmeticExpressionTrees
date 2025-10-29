void inorderTraversal(struct tree* root);

int main (int argc, char * argv[]){
}

//Inorder traversal
void inorderTraversal(struct tree* root) {
  if (root == NULL) return;
  inorderTraversal(root->left);  
  printf("%c ->", root->data);
  inorderTraversal(root->right);
}