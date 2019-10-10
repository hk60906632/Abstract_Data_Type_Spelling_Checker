#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

struct node{
  char* word;
  struct node *left;
  struct node *right;
};
typedef struct node node;

struct dic{
  node *root;
  int max_word;
};
typedef struct dic dic;

/*Create epmty dic*/
dic* dic_init(int size);

/*Add one element into the dic*/
void dic_insert(dic* s, char* v);

/*Returns true  if v is in the array, false elsewise*/
bool dic_isin(dic *s, char* v);

/*Finish up*/
/*Clears all space used, and sets pointer to NULL*/
void dic_free(dic** s);
