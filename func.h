#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

const char* msgs[5];
const int NMsgs ;
const char* errmsgs[3];

typedef struct Node{
    int key;
    int len;
    int offset;
    int busy;
}Node;

typedef struct Table{
    int c;
    int sz;
    Node* first;
    FILE* st;
}Table;

void tab_free(Table* tab);
void tab_save(Table* tab);
int tab_del(Table* tab);
int tab_show(Table* tab);
int tab_find(Table* tab);
int tab_load(Table* tab);
int tab_add(Table* tab);

char* findInfo(Table *tab, int key);
int create(Table* tab, char* name, int sz);
int load(Table* tab, char* name);
int find(Table *tab, int key);
int insert(Table *tab, char* str, int key);
int hash(char* data);
int getInt(int *a);
int dialog(const char *msgs[], int N);
