node* node_initial(char* v);
void node_insert(node* s, char* v);
bool node_isin(node *s, char* v);
void free_node (node *s);

dic* dic_init(int size){
  dic *a;
  a = (dic*) calloc(1,sizeof(dic));
    if(a == NULL){
      ON_ERROR("Creation of Dic Failed\n");
    }
  a->root = NULL;
  a->max_word = size;
  return a;
}

void dic_insert(dic* s, char* v){
  if (s->root==NULL){
    s->root = node_initial(v);
  }
  else{
    node_insert (s->root, v);
  }
}

bool dic_isin(dic *s, char* v){
  return node_isin(s->root, v);
}

void dic_free(dic** s){
  dic *a = *s;
  free_node (a->root);
  free(a);
  *s = NULL;
}

node* node_initial(char* v){
  node* root;
  root = (node*) calloc(1,sizeof(node));
    if(root == NULL){
      ON_ERROR("Creation of node Failed\n");
    }
  root->word = (char*) calloc(strlen(v)+1, sizeof(char));
    if(root->word == NULL){
      ON_ERROR("Creation of word Failed\n");
    }
  strcpy(root->word, v);
  root->left = NULL;
  root->right = NULL;
  return root;
}

void node_insert(node* s, char* v){
  node *p;
  if(s == NULL || strcmp(v , s->word) == 0){
    return;
  }
  if(strcmp(v, s->word)>0){
    if(s->left == NULL){
      p = node_initial(v);
      s->left = p;
    }
    else {
      node_insert(s->left, v);
    }
  }
  else {
    if(s->right == NULL){
      p = node_initial(v);
      s->right = p;
    }
    else {
      node_insert(s->right, v);
    }
  }
}

bool node_isin(node *s, char* v){
  if(s == NULL){
    return false;
  }
  if(strcmp(v, s->word)==0){
    return true;
  }
  if (strcmp(v, s->word)>0){
    return node_isin(s->left, v);
  }
  else{
    return node_isin(s->right, v);
  }
}

void free_node (node *s){
  if (s != NULL){
    free_node(s->right);
    free(s->word);
    free_node(s->left);
    free(s);
  }
}
