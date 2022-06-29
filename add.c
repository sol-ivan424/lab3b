#include "func.h"

int tab_add(Table* tab){
    int res, key;
    char* data = NULL;

    data = readline("Enter data: ");
    key = hash(data);
    res = insert(tab, data, key);

    printf("%s: %d\n", errmsgs[res], key);

    free(data);
    return 1;
}

int hash(char* data){
    int sum = 0, i, j = strlen(data);

    for(i = 0; i < j; i++)
    sum = sum + data[i];
    sum = sum % 123;

    return sum;
}

int insert(Table* tab, char* str, int key){

    if(find(tab, key) >= 0)
    return 1;

    if(tab->c >= tab->sz)
    return 2;

    tab->first[tab->c].key = key;
    tab->first[tab->c].busy = 1;
    tab->first[tab->c].len = strlen(str) + 1;
    fseek(tab->st, 0, SEEK_END);
    tab->first[tab->c].offset = ftell(tab->st);
    fwrite(str, sizeof(char), tab->first[tab->c].len, tab->st);
    tab->c = tab->c + 1;

    return 0;
}
