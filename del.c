#include "func.h"

int tab_del(Table* tab){
    int key, a, i;

    printf("Key for del: ");
    a = getInt(&key);
    i = find(tab, key);

    if(i >= 0){
        tab->first[i].busy = 0;
        printf("Key %d was del\n", key);
    }else
    printf("Key %d doesnt exist\n", key);

    return 1;
}
