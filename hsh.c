/*testline// #include "hsh.h"*/
#define ARR_SIZE 79
#define PRIME 73
#define ALMOST_FULL 0.8
#define DOUBLE_SIZE 2
#define DOUBLE_HASH (index1 + i*index2)%(s->table_siz)

int hash_key_1(dic* s, char *word);
int hash_key_2(char *word);
bool is_prime(int x);
int next_prime(int x);
void add_word(dic *s, char* v);
dic* table_nw_size(int size);
void table_resize(dic* s, int size);
void table_siz_up (dic* s);

dic* dic_init(int size)
{
  dic* l;
  l = (dic*) calloc(1,sizeof(dic));
    if(l == NULL){
      ON_ERROR("Creation of Dic Failed\n");
    }
  l->hsh_table = (data_tag*) calloc(ARR_SIZE, sizeof(data_tag));
    if(l->hsh_table == NULL){
      ON_ERROR("Creation of hash table Failed\n");
    }
  l->table_siz = ARR_SIZE;
  l->filled = 0;
  l->max_word = size;
  return l;
}

void dic_insert(dic* s, char* v){
  if (s->filled > (s->table_siz*ALMOST_FULL)){
    /*testline//printf ("pz: %d\n",l->pz);*/
    table_siz_up (s);
  }
  add_word(s, v);
}

bool dic_isin(dic *s, char* v){
  int i = 0;
  int index1 = hash_key_1(s, v);
  int index2 = hash_key_2(v);
  while (s->hsh_table[DOUBLE_HASH].word != NULL){
    if (strcmp(s->hsh_table[DOUBLE_HASH].word, v) == 0){
      return true;
    }
    else{
      i++;
    }
  }
return false;
}

void dic_free(dic** s){
  int i;
  dic* a = *s;
  /*testline//printf ("pz is %d\n", a->pz);*/
  for (i = 0; i < a->table_siz; i++){
    if (a->hsh_table[i].word != NULL){
      free(a->hsh_table[i].word);
    }
  }
  free (a->hsh_table);
  free (a);
  *s = NULL;
}

/*Modified Bernstein hashing
5381 & 33 are magic numbers required by the algorithm*/
int hash_key_1(dic* s, char *word){
  unsigned long hash = 5381;
  int c;
  while((c=(*word++))){
    hash = 33 * hash ^ c;
  }
  return (int)(hash % s->table_siz);
}

int hash_key_2(char *word){
  int key2 = 0, word_size, i;
  word_size = strlen(word);
  for (i = 0; i < word_size; i++){
    key2 += word[i];
  }
  key2 = (PRIME - (key2 % PRIME));
  return key2;
}

bool is_prime(int x){
  int a;
  if (x < 2){
    return false;
  }
  if (x < 4){
    return true;
  }
  if ((x%2) == 0){
    return false;
  }
  for (a = 3; a <= floor(sqrt((double) x)); a += 2){
    if ((x % a)==0){
      return false;
    }
  }
  return true;
}

int next_prime(int x){ /*to keep the resized hash table as prime number size*/
  while (is_prime(x)!=true){
    x++;
  }
  return x;
}


void table_siz_up (dic* s){
  int new_size = (s->table_siz)*DOUBLE_SIZE;
  table_resize(s,new_size);
}


void table_resize(dic* s, int new_size){
  int i,temp_size;
  data_tag* temp_array;
  dic* new_table = table_nw_size(new_size);
  for (i = 0; i < s->table_siz; i++){ /*rehashing to new table*/
    if (s->hsh_table[i].word != NULL){
      add_word(new_table, s->hsh_table[i].word);
    }
  }
  temp_size = s->table_siz;
  s->table_siz = new_table->table_siz;
  new_table->table_siz = temp_size;

  temp_array = s->hsh_table;
  s->hsh_table = new_table->hsh_table;
  new_table->hsh_table = temp_array;
  dic_free (&new_table);
}

dic* table_nw_size(int new_size){
  dic* l;
   l = (dic*) calloc(1,sizeof(dic));
    if(l == NULL){
        ON_ERROR("Creation of new dic Failed\n");
    }
   l->table_siz = next_prime(new_size);
   l->hsh_table = (data_tag*) calloc(l->table_siz, sizeof(data_tag));
    if(l->hsh_table == NULL){
        ON_ERROR("Creation of new table Failed\n");
    }
   l->filled = 0;
   return l;
}

void add_word(dic *s, char* v){
  int i = 0, index;
  int index1 = hash_key_1(s, v);
  int index2 = hash_key_2(v);
  if (s->hsh_table[index1].word != NULL){
    i++;
    while (s->hsh_table[DOUBLE_HASH].word != NULL){
        i++;
      }
      index = DOUBLE_HASH;
      s->hsh_table[index].word = (char*) calloc(strlen(v)+1, sizeof(char));
        if(s->hsh_table[index].word == NULL){
          ON_ERROR("Creation of Word Space 1 Failed\n");
        }
      strcpy(s->hsh_table[index].word, v);
      s->filled++;
    }
  else{
    s->hsh_table[index1].word = (char*) calloc(strlen(v)+1, sizeof(char));
      if(s->hsh_table[index1].word == NULL){
        ON_ERROR("Creation of Word Space 2 Failed\n");
      }
    strcpy(s->hsh_table[index1].word, v);
    s->filled++;
  }
}

/*test based on ARR_SIZE  31, PRIME  7 and only double the size not triple,
this shows a very slow result so increase all these factors*/
/*int main(){
  char b[5];
  char c[5];
  strcpy (b, "abcd");
  strcpy (c, "bcde");
  dic* a = dic_init(50);
  printf("Filled:%d\n", a->filled);
  printf("Table size:%d\n", a->pz);
  printf("Hash key of b:%d\n", hash_key_1(a,b));
  add_word(a, b);
  printf("%s\n", a->array[22].word);
  printf("Filled:%d\n", a->filled);
  printf("Hash key of c:%d\n", hash_key_1(a,c));
  add_word(a, c);
  printf("%s\n", a->array[26].word);
  printf("Filled:%d\n", a->filled);
  add_word(a, b);
  printf("Filled:%d\n", a->filled);
  printf("#####Table size double####\n");
  table_siz_up (a);
  printf("Siz up filled:%d\n", a->filled);
  printf("Siz up table size:%d\n", a->pz);
  printf("New b hash key:%d\n", hash_key_1(a,b));
  printf("%s\n", a->array[59].word);
  printf("New c hash key:%d\n", hash_key_1(a,c));
  printf("%s\n", a->array[63].word);
  printf("%d\n",dic_isin(a,"abcd"));
  printf("#####Table size double####\n");
  table_siz_up (a);
  printf("Siz up filled:%d\n", a->filled);
  printf("Siz up table size:%d\n", a->pz);
  printf("New b hash key:%d\n", hash_key_1(a,b));
  printf("%s\n", a->array[120].word);
  printf("New c hash key:%d\n", hash_key_1(a,c));
  printf("%s\n", a->array[124].word);
  printf("%d\n",dic_isin(a,"abcd"));
}*/
