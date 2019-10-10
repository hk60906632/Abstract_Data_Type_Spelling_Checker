#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

struct data_tag{
  char* word;
};
typedef struct data_tag data_tag;

struct dic{
  data_tag* hsh_table;
  int filled;
  int table_siz;
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
