#include "func.h"

const char* msgs[] = {"0. Quit", "1. Add", "2. Delete", "3. Find", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char* errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

int getInt(int* a){
    int e;

    do{
        e = scanf("%d", a);
        if (e < 0){
            return 0;
        }
        if (e == 0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (e == 0);
    return 1;
}

int tab_show(Table* tab){
    int c = tab->c, i;
    char* data = NULL;

    for(i=0; i < c; i++){
        if(tab->first[i].busy == 1){
            data = (char*)malloc(tab->first[i].len);
            fseek(tab->st, tab->first[i].offset, SEEK_SET);
            fread(data, sizeof(char), tab->first[i].len, tab->st);
            printf("key: %d - info: %s\n", tab->first[i].key, data);
            free(data);
        }
    }
    return 1;
}

void tab_free(Table* tab){
    free(tab->st);
    free(tab->first);
}

void tab_save(Table *tab){
    fseek(tab->st, sizeof(int), SEEK_SET);
    fwrite(&tab->c, sizeof(int), 1, tab->st);
    fwrite(tab->first, sizeof(Node), tab->c, tab->st);
    fclose(tab->st);
    tab->st = NULL;
}

int dialog(const char* msgs[], int N){
    int ch, i, n;
    char* errmsg = "";

    for(i = 0; i < N; ++i)
    puts(msgs[i]);

    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeate, please!";
        printf("Make your choice: ");
        n = getInt(&ch);
        if(n == 0)
        ch = 0;
    }while(ch < 0 || ch >= N);

    return ch;
}
