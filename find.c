#include "func.h"

int find(Table* tab, int key){
    int i;

    for(i = 0; i < tab->c; ++i){
        if(tab->first[i].key == key && tab->first[i].busy !=0)
        return i;
    }

    return -1;
}

char* fData(Table* tab, int key){
    int i = find(tab, key);
    char* data = NULL;

    if (i >= 0){
        data = (char*)malloc(tab->first[i].len);
        fseek(tab->st, tab->first[i].offset, SEEK_SET);
        fread(data, sizeof(char), tab->first[i].len, tab->st);
    }

    return data;
}

int tab_find(Table* tab){
    int key, ch;
    char* data = NULL;

    printf("Enter key: ");
    ch = getInt(&key);
    if(ch == 0)
    return 0;

    data = fData(tab, key);

    if(data){
        printf("key: %d - info: %s\n", key, data);
        free(data);
    }
    else
    printf("Item %d doesnt wxist\n", key);

    return 1;
}
