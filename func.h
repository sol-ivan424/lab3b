#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

const char *msgs[5];
const int NMsgs ;
const char *errmsgs[3] ;

typedef struct Item{
    int key;
    int busy;
    int offset;
    int len;
}Item;

typedef struct Table{
    int n;
    int SZ;
    FILE *fd;
    Item *first;
}Table;

void D_Del(Table *ptab);
void D_Show(Table *ptab);
char * findInfo(Table ptab, int k);
int D_Find(Table *ptab);
int D_Load(Table *ptab);
int create(Table *ptab, char *fname, int sz);
int load (Table *ptab, char *fname);
int find(Table ptab, int k);
int insert(Table *ptab, int k, char *str);
void D_Save(Table *ptab);
int hash(char *info);
int getInt(int *a);
int D_Add(Table *ptab);
int dialog(const char *msgs[], int N);

