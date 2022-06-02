#include "func.h"

int main(){
    Table table = {0, 0, NULL, NULL};
    int rc, n;

    if (D_Load(&table) == 0)
    return 1;

    while(rc = dialog(msgs, NMsgs)){
        if(rc == 0)
	break;

	if(rc == 1)
	n = D_Add(&table);

	if(rc == 2)
	n = D_Find(&table);

	if(rc == 3)
	D_Del(&table);

	if(rc == 4)
	D_Show(&table);
    }
    D_Save(&table);
    free(table.fd);
    free(table.first);
    printf("That's all. Bye!\n");
    return 0;
}
