void postorderTraversal(struct tree* root);

int main (int argc, char * argv[]){
}

// Postorder traversal
void postorderTraversal(struct tree* root) {
  if (root == NULL) return;
  postorderTraversal(root->left);  
  postorderTraversal(root->right);
  printf("%c ->", root->data);
}