#include "func.h"

int load(Table* tab, char* name){
    tab->st = fopen(name, "r+b");

    if (tab->sz == 0)
    return 0;

    fread(&tab->sz, sizeof(int), 1, tab->st);
    tab->first = (Node*)calloc(tab->sz, sizeof(Node));
    fread(&tab->c, sizeof(int), 1, tab->st);
    fread(tab->first, sizeof(Node), tab->c, tab->st);

    return 1;
}

int create(Table* tab, char* name, int sz){
    tab->sz = sz;
    tab->c = 0;

    tab->st = fopen(name, "w+b");

    if (tab->st == NULL){
        tab->first = NULL;
        return 0;
    }

    tab->first = (Node*)calloc(tab->sz, sizeof(Node));
    fwrite(&tab->sz, sizeof(int), 1, tab->st);
    fwrite(&tab->c, sizeof(int), 1, tab->st);
    fwrite(tab->first, sizeof(Node), tab->sz, tab->st);

    return 1;
}

int tab_load(Table* tab){
    int size;
    char* file_name = NULL;

    file_name = readline("File name: ");

    if(file_name == NULL)
    return 0;

    if (load(tab, file_name) == 0){
        printf("Enter possible vector size: ");

        if (getInt(&size) == 0)
        return 0;

        create(tab, file_name, size);
    }
    free(file_name);
    return 1;
}
