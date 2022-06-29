#include "func.h"

int main(){
    Table* table = NULL;
    table = (Table*) calloc(1,sizeof(Table));
    int ch;
    int(*fptr[])(Table*) = {NULL, tab_add, tab_del, tab_find, tab_show};

    if (tab_load(table) == 0)
    return 1;

    while(ch = dialog(msgs, NMsgs)){
        if(!fptr[ch](table)){
            break;
        }
    }
    tab_save(table);
    tab_free(table);
    free(table);

    printf("That's all. Bye!\n");
    return 0;
}
