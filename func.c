#include "func.h"

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

void D_Show(Table *ptab){
    char *info = NULL;
    int c = ptab->n, i = 0;
    for(i=0; i < c; i++){
	if(ptab->first[i].busy == 1){
	    info = (char*)malloc(ptab->first[i].len);
	    fseek(ptab->fd,ptab->first[i].offset, SEEK_SET);
	    fread(info, sizeof(char), ptab->first[i].len, ptab->fd);
	    printf("key = %d | info = '%s'\n", ptab->first[i].key, info);
	    free(info);
	}
    }
}

void D_Del(Table *ptab){
    int k, n, i;

    printf("Enter key for delete: ");
    n = getInt(&k);

    i = find(*ptab, k);
    if(i >= 0){
	ptab->first[i].busy = 0;
	printf("Key %d was deleted\n", k);
    }else
	printf("Key %d was not found\n", k);
}

int find(Table ptab, int k){
    int i = 0;
    for(i = 0; i < ptab.n; ++i)
        if(ptab.first[i].key == k && ptab.first[i].busy !=0)
            return i;
    return -1;
}

char *findInfo(Table ptab, int k){
    char *info = NULL;
    int i = find(ptab, k);
    if (i >= 0){
	info = (char *)malloc(ptab.first[i].len);
	fseek(ptab.fd, ptab.first[i].offset, SEEK_SET);
        fread(info, sizeof(char), ptab.first[i].len, ptab.fd);
    }
    return info;
}

int D_Find(Table *ptab){
    char *info = NULL;
    int k, n, i;

    printf("Enter key: ");
    n = getInt(&k);

    if(n == 0)
        return 0;

    info = findInfo(*ptab, k);

    if(info){
        printf("key = %d | info = '%s'\n", k, info);
        free(info);
    }
    else
        printf("Item %d was not found\n", k);
    return 1;
}

int insert(Table *ptab, int k, char *str){
    if(find(*ptab, k) >= 0)
        return 1;
    if(ptab->n >= ptab->SZ)
        return 2;
    ptab->first[ptab->n].key = k;
    ptab->first[ptab->n].busy = 1;
    ptab->first[ptab->n].len = strlen(str) + 1;
    fseek(ptab->fd, 0, SEEK_END);
    ptab->first[ptab->n].offset = ftell(ptab->fd);
    fwrite(str, sizeof(char), ptab->first[ptab->n].len, ptab->fd);
    ++(ptab->n);
    return 0;
}

int getInt(int *a){
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

int hash(char *info){
    int s = 0, i = 0, res = 0, j = strlen(info);

    for(i = 0; i < j; i++){
    	s = s + info[i];
    }
    res = s % 60;
    return res;
}

void D_Save(Table *ptab){

    fseek(ptab->fd, sizeof(int), SEEK_SET);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->n, ptab->fd);

    fclose(ptab->fd);
    ptab->fd = NULL;
}

int load(Table *ptab, char *fname){
    ptab->fd = fopen(fname, "r+b");

    if (ptab->fd == 0)
        return 0;

    fread(&ptab->SZ, sizeof(int), 1, ptab->fd);
    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));
    fread(&ptab->n, sizeof(int), 1, ptab->fd);
    fread(ptab->first, sizeof(Item), ptab->n, ptab->fd);
    return 1;
}

int create(Table *ptab, char *fname, int sz){
    ptab->SZ = sz;
    ptab->n = 0;

    ptab->fd = fopen(fname, "w+b");

    if (ptab->fd == NULL){
	ptab->first = NULL;
        return 0;
    }
    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));
    fwrite(&ptab->SZ, sizeof(int), 1, ptab->fd);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->SZ, ptab->fd);
    return 1;
}

int D_Load(Table *ptab){
    int SZ;
    char *fname = NULL;
    fname = readline("Enter file name: ");

    if(fname == NULL)
        return 0;
    if (load(ptab, fname) == 0){
	printf("Enter possible vector size: ");
	if (getInt(&SZ) == 0)
	    return 0;
        create(ptab, fname, SZ);
    }
    free(fname);
    return 1;
}

int D_Add(Table *ptab){
    int k, rc;
    char *info = NULL;
    info = readline("Enter info: ");

    k = hash(info);
    rc = insert(ptab, k, info);

    free(info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

int dialog(const char *msgs[], int N){
    char *errmsg = "";
    int rc;
    int i, n;

    for(i = 0; i < N; ++i)
    puts(msgs[i]);

    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeate, please!";
        printf("Make your choice: ");
        n = getInt(&rc);
        if(n == 0)
        rc = 0;
    } while(rc < 0 || rc >= N);

    return rc;
}
