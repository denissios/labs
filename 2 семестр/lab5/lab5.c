#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define t 2

typedef struct info {
    int key;
    char* inf;
} info;

typedef struct knof {
    int nK;
    info keys[2 * t - 1];
    struct knof* ptrs[2 * t];
    int leaf;
} knof;

typedef struct kpos {
    knof* pos;
    int i;
} kpos;

typedef struct ifile {
    int key;
    int length;
} ifile;

void Find(knof* x);
void Clear(knof* x);
char* GetStr();
int Insert(knof* T);
void next_elementt(knof* x);
void Order_Print(knof* x, int);
int Tree_insert(knof** root, info* k);
int B_Delete(knof* x, int k, knof* cx, int);
kpos* B_Search(knof* x, int k, int flag1);
void B3(knof** x, knof* cx, int k, int i);
void B_Split(knof* y, int i, knof* x);
int BTI_NotFull(knof* x, info* k);
kpos* B_max(knof* x);
knof* root;
void abc(knof* x, kpos* poz);
knof* Zero_tree_create();
int GetInt(int* a);
void Clear_Save();
void readf();
void timing();
void dialog(int x);
void dialog_msg();

int main()
{
    root = Zero_tree_create();
    int x = -1;
    readf();
    while (x != 0)
    {
        dialog_msg();
        GetInt(&x);
        if (x < 0 || x > 6)
        {
            printf("[WARNING] Wrong option\n");
            continue;
        }
        printf("\n");
        dialog(x);
    }

    Clear_Save();
}

void dialog_msg()
{
    printf("\n0. Exit\n");
    printf("1. Insert element\n");
    printf("2. Timing\n");
    printf("3. Write info about element\n");
    printf("4. Next element\n");
    printf("5. Delete element\n");
    printf("6. Order print\n");
    printf("Your choice: ");
}

void dialog(int x)
{
    if (x == 1) {
       Insert(root);
    }

    if (x == 2) {
        timing();
        exit(0);
    }

    if (x == 3) {
        Find(root);
    }

    if ((x == 4) && (root->nK != 0)) {
        next_elementt(root);
    }

    if (x == 5) {
        Clear(root);
    }

    if (x == 6) {
        Order_Print(root, 0);
    }
}

void timing() {
    int key[10000], cnt = 100000, i, m;
    info* K = (info*)calloc(1, sizeof(info));
    if (!K)
        return;
    K->inf = NULL;
    clock_t first, last;

    srand(time(NULL));
    for (i = 0; i < 10000; i++)
        key[i] = rand() * rand();
    for (i = 0; i < cnt; i++) {
        K->key = rand() * rand();
        if (Tree_insert(&root, K));
        ++i;
    }
    m = 0;
    first = clock();
    for (i = 0; i < 10000; ++i)
        if (B_Search(root, key[i], 0)->pos != NULL)
            ++m;

    last = clock();
    printf("%d items were found\n", m);
    printf("time = %d\n", last - first);

}

void readf() {
    FILE* fd = fopen("Tree", "rb");
    if (fd == NULL) {
        return;
    }
    ifile* reads = (ifile*)malloc(sizeof(ifile));
    if (!reads)
        return;
    info* inf = (info*)calloc(1, sizeof(info));
    if (!inf)
        return;
    while (feof(fd) == 0) {
        if (!reads)
            return;
        fread(reads, sizeof(ifile), 1, fd);
        inf->key = reads->key;
        inf->inf = (char*)calloc(reads->length, 1);
        if (!(inf->inf))
            return;
        fread(inf->inf, reads->length, 1, fd);

        if ((B_Search(root, inf->key, 0))->pos == NULL) {
            Tree_insert(&root, inf);
        }

    }
    fclose(fd);
}

void Clear_Save() {
    FILE* fd;
    ifile* reads = (ifile*)malloc(sizeof(ifile));
    if (!reads)
        return;
    fd = fopen("Tree", "wb");
    while (root->nK != 0) {
        reads->key = root->keys[0].key;
        reads->length = strlen(root->keys[0].inf) + 1;
        fwrite(reads, sizeof(ifile), 1, fd);
        fwrite(root->keys[0].inf, 1, reads->length, fd);
        B_Delete(root, root->keys[0].key, NULL, 1);
    }
    free(root);
    fclose(fd);
}

void Find(knof* x) {
    int a;
    kpos* poz;
    printf_s(">>>>Enter key: ");
    GetInt(&a);
    return B_Search(x, a, 1);
}

knof* Zero_tree_create() {
    knof* root = (knof*)malloc(sizeof(knof));
    if (!root)
        return;
    root->nK = 0;
    root->leaf = 1;
    for (int i = 0; i < 2 * t; i++)
        root->ptrs[i] = NULL;
    return root;
}

void B_Split(knof* y, int i, knof* x) {
    for (int j = x->nK - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
        x->ptrs[j + 2] = x->ptrs[j + 1];
    }
    x->keys[i] = y->keys[t / 2];
    x->ptrs[i + 1] = (knof*)malloc(sizeof(knof));
    if (!(x->ptrs[i + 1]))
        return;
    x->ptrs[i + 1]->nK = t - 1;
    x->ptrs[i + 1]->leaf = y->leaf;
    for (int j = 0; j < 2 * t; j++)
        x->ptrs[i + 1]->ptrs[j] = NULL;
    x->nK += 1;
    y->nK = t - 1;
    for (int j = t; j < 2 * t - 1; j++)
        x->ptrs[i + 1]->keys[j - t] = y->keys[j];
    for (int j = t; j < 2 * t; j++)
        x->ptrs[i + 1]->ptrs[j - t] = y->ptrs[j];
}

int Tree_insert(knof** r, info* k) {
    knof* x = root;
    if ((root)->nK == 2 * t - 1) {
        knof* newroot = Zero_tree_create();
        newroot->leaf = 0;
        newroot->ptrs[0] = *r;
        B_Split((root), 0, newroot);
        root = newroot;

        return BTI_NotFull(root, k);
    }
    else return BTI_NotFull(root, k);

}

int BTI_NotFull(knof* x, info* k) {
    int i;
    while (x->leaf != 1) {
        for (i = 0; i < x->nK; i++) {
            if (x->keys[i].key == k->key) return -1;
            if (x->keys[i].key > k->key) break;
        }
        if (x->ptrs[i]->nK == 2 * t - 1) {
            B_Split(x->ptrs[i], i, x);
            if (k->key > x->keys[i].key) {
                x = x->ptrs[i + 1];
                continue;
            }
            if (k->key < x->keys[i].key) {
                x = x->ptrs[i];
                continue;
            }
            if (x->keys[i].key == k->key)
                return -1;
        }
        else x = x->ptrs[i];
    }
    if (x->nK == 0) {
        x->keys[0] = *k;
        x->nK++;
        return 1;
    }
    for (i = x->nK; i > 0; i--) {
        if (x->keys[i - 1].key >= k->key) {
            if (x->keys[i - 1].key == k->key)
                return -1;
            x->keys[i] = x->keys[i - 1];
        }
        else break;
    }
    x->keys[i] = *k;
    x->nK++;
    return 1;
}

kpos* B_Search(knof* x, int k, int flag1) {
    kpos* poz = (kpos*)malloc(sizeof(kpos));
    if (!poz)
        return;
    kpos* par = (kpos*)malloc(sizeof(kpos)); 
    if (!par)
        return;
    poz->pos = NULL;
    par->pos = NULL;
    int i;
    do {
        for (i = 0; i < x->nK; i++) {
            if (k < x->keys[i].key)
                break;
            if (k == x->keys[i].key) {
                poz->pos = x;
                poz->i = i;
                if (flag1)
                    printf_s("\nKey: %d,\nInfo: %s\n", poz->pos->keys[poz->i].key, poz->pos->keys[poz->i].inf);
                return poz;
            }
        }
        x = x->ptrs[i];
    } while (x != NULL);
    if (flag1)
    {
        printf("We don't have element with this key\n");
        return 0;
    }
    return poz;
}

int B_Delete(knof* x, int k, knof* cx, int fre) {
    knof* y, * cy;
    int i;
    info k1;
    for (i = 0; i < x->nK; i++) {
        if (k < x->keys[i].key) {
            break;
        }
        if (k == x->keys[i].key) {
            if ((x->leaf == 1) && ((x->nK > t - 1) || (cx == NULL))) {
                if (x->nK == 1) {
                    if (fre == 1)
                        free(x->keys[0].inf);
                    free(x);
                    root = Zero_tree_create();
                    return 1;
                }
                if (fre == 1)
                    free(x->keys[i].inf);
                for (int j = i + 1; j < x->nK; j++) {
                    x->keys[j - 1] = x->keys[j];
                }

                x->nK--;
                return 1;
            }
            if (x->leaf == 0) {
                if (x->ptrs[i]->nK > t - 1) {
                    y = x->ptrs[i];
                    cy = x;
                    if (y->ptrs[y->nK] == NULL)
                        k1 = y->keys[y->nK - 1];
                    else {
                        while (y->ptrs[y->nK]->leaf != 1) {
                            cy = y;
                            y = y->ptrs[y->nK];
                        }
                        k1 = y->ptrs[y->nK]->keys[y->nK - 1];
                    }
                    free(x->keys[i].inf);
                    x->keys[i] = k1;
                    return B_Delete(y, k1.key, cy, 0);

                }
                else {
                    if (x->ptrs[i + 1]->nK > t - 1) {
                        y = x->ptrs[i + 1];
                        cy = x;
                        if (y->ptrs[0] == NULL)
                            k1 = y->keys[0];
                        else {
                            while (y->ptrs[0]->leaf != 1) {
                                cy = y;
                                y = y->ptrs[0];
                            }
                            k1 = y->ptrs[0]->keys[0];
                        }
                        free(x->keys[i].inf);
                        x->keys[i] = k1;
                        return B_Delete(y, k1.key, cy, 0);
                    }
                    else {
                        y = x->ptrs[i];
                        B3(&x, cx, k, i);
                        return B_Delete(x, k, cx, fre); 

                    }
                }
            }
            return 1;
        }
    }
    if (x->ptrs[i] == NULL) {
        return-1;
    }
    if (x->ptrs[i]->nK > t - 1)
        B_Delete(x->ptrs[i], k, x, fre);
    else {
        y = x->ptrs[i];
        if (i > 0) {
            if (x->ptrs[i - 1]->nK > t - 1) {
                k1 = x->ptrs[i - 1]->keys[x->ptrs[i - 1]->nK - 1];
                for (int j = y->nK; j > 0; j--)
                    y->keys[j] = y->keys[j - 1];
                for (int j = y->nK + 1; j > 0; j--)
                    y->ptrs[j] = y->ptrs[j - 1];
                y->nK++;
                y->keys[0] = x->keys[i - 1];
                y->ptrs[0] = x->ptrs[i - 1]->ptrs[x->ptrs[i - 1]->nK];
                x->keys[i - 1] = k1;
                x->ptrs[i - 1]->nK--;
                B_Delete(y, k, x, fre);
            }
            else {
                if (i < x->nK) {
                    if (x->ptrs[i + 1]->nK > t - 1) {
                        k1 = x->ptrs[i + 1]->keys[0];
                        y->keys[y->nK] = x->keys[i];
                        y->ptrs[y->nK + 1] = x->ptrs[i + 1]->ptrs[0];
                        y->nK++;
                        x->keys[i] = k1;
                        for (int j = 1; j < x->ptrs[i + 1]->nK; j++)
                            x->ptrs[i + 1]->keys[j - 1] = x->ptrs[i + 1]->keys[j];
                        for (int j = 1; j < x->ptrs[i + 1]->nK + 1; j++)
                            x->ptrs[i + 1]->ptrs[j - 1] = x->ptrs[i + 1]->ptrs[j];
                        x->ptrs[i + 1]->nK--;
                        B_Delete(y, k, x, fre);
                    }
                    else {
                        B3(&x, cx, k, i);
                        B_Delete(y, k, x, fre);
                    }
                }
                else {
                    y = x->ptrs[i - 1];
                    B3(&x, cx, k, i - 1);
                    B_Delete(y, k, x, fre);
                }
            }
        }
        else {
            if (i < x->nK) {
                if (x->ptrs[i + 1]->nK > t - 1) {
                    k1 = x->ptrs[i + 1]->keys[0];
                    y->keys[y->nK] = x->keys[i];
                    y->ptrs[y->nK + 1] = x->ptrs[i + 1]->ptrs[0];
                    y->nK++;
                    x->keys[i] = k1;
                    for (int j = 1; j < x->ptrs[i + 1]->nK; j++)
                        x->ptrs[i + 1]->keys[j - 1] = x->ptrs[i + 1]->keys[j];
                    for (int j = 1; j < x->ptrs[i + 1]->nK + 1; j++)
                        x->ptrs[i + 1]->ptrs[j - 1] = x->ptrs[i + 1]->ptrs[j];
                    x->ptrs[i + 1]->nK--;
                    B_Delete(y, k, x, fre);
                }
                else {
                    B3(&x, cx, k, i);
                    B_Delete(y, k, x, fre);
                }
            }
        }

    }
    return -1;
}

void B3(knof** x, knof* cx, int k, int i) {
    knof* y = (*x)->ptrs[i];
    y->keys[y->nK] = (*x)->keys[i];
    for (int j = y->nK + 1; j < 2 * t - 1; j++) 
        y->keys[j] = (*x)->ptrs[i + 1]->keys[j - (y->nK + 1)];
    for (int j = y->nK + 1; j < 2 * t; j++)
        y->ptrs[j] = (*x)->ptrs[i + 1]->ptrs[j - (y->nK + 1)];
    y->nK = 2 * t - 1;
    free((*x)->ptrs[i + 1]);
    for (int j = i + 1; j < (*x)->nK; j++)
        (*x)->keys[j - 1] = (*x)->keys[j];
    for (int j = i + 2; j < (*x)->nK + 1; j++)
        (*x)->ptrs[j - 1] = (*x)->ptrs[j];
    (*x)->nK--;
    if ((*x)->nK == 0) {
        free((*x));
        if (cx != NULL) {
            for (int j = 0; j < cx->nK; j++) {
                if (cx->keys[j].key > k)
                    break;
            }
            cx->ptrs[i] = y;
            (*x) = y;
        }
        else
            root = y;
        (*x) = y;
    }
}

void Order_Print(knof* x, int l) {
    for (int i = x->nK - 1; i >= -1; i--) 
    {
        if (x->ptrs[i + 1] != NULL)
            Order_Print(x->ptrs[i + 1], l + 1);
        if (i > -1) {
            for (int j = 0; j < l; j++)
                printf_s("   ");
            printf_s("%d  \n", x->keys[i].key);
        }
    }
}

int Insert(knof* T) {
    info* infa = (info*)malloc(sizeof(info));
    if (!infa)
        return;
    printf_s(">>>>Please, input a key: ");
    GetInt(&(infa->key));
    if (!(B_Search(root, infa->key, 0))->pos == NULL)
    {
        printf("Error! Element with this key has already exists\n");
        return 0;
    }
    infa->inf = GetStr();
    Tree_insert(&T, infa);
    return 1;
}

void Clear(knof* x) {
    int a;
    printf_s("\nEnter a key: ");
    GetInt(&a);
    kpos* poz;
    poz = B_Search(root, a, 0);
    if (poz->pos == NULL)
    {
        printf("We don't have element with this key\n");
        return 0;
    }
    B_Delete(x, a, NULL, 1);
}

kpos* B_max(knof* x) {
    for (int i = x->nK; i >= 0; i--) {
        if (x->ptrs[i] != NULL)
            return B_max(x->ptrs[i]);
    }
    kpos* poz = (kpos*)malloc(sizeof(kpos));
    if (!poz)
        return;
    poz->i = x->nK - 1;
    poz->pos = x;
    return poz;
}

char* GetStr() {
    char buf[30] = { "" };
    int n;
    char* a = (char*)calloc(1, sizeof(char));
    if (!a)
        return;
    printf(">>>Input text (string) information:  ");
    scanf_s("%*[\n]");
    while (n = scanf("%29[^\n]", buf), n > 0) {
        int c = strlen(buf) + strlen(a);
        a = (char*)realloc(a, c + 1);
        if (!a)
            return;
        a[c - strlen(buf)] = '\0';
        strcat(a, buf);
    }
    if (n < 0) {
        free(a);
        exit(1);
    }
    return a;
}

int GetInt(int* a)
{
    int n;
    do {
        n = scanf_s("%d", a);
        if (n == 0) {
            printf("error\n");
            scanf_s("%*[^\n]");
        }
    } while (n == 0);
    return n < 0 ? 0 : 1;
}

void abc(knof* x, kpos* poz) {
    static int flag5 = 0;
    for (int i = 0; i <= x->nK; i++) {
        if (x->ptrs[i] != NULL)
            abc(x->ptrs[i], poz);
        if (i < x->nK)
        {
            if (flag5)
            {
                printf_s("\n1Key: %d,\nInfo: %s\n", x->keys[i].key, x->keys[i].inf);
                flag5 = 0;
                return 0;
            }
            if (poz->pos->keys[poz->i].key == x->keys[i].key)
            {
                flag5 = 1;
            }
        }
    }
}

void next_elementt(knof* x) {
    int a;
    printf_s(">>>>Enter key: ");
    GetInt(&a);
    kpos* poz;
    poz = B_Search(root, a, 0);
    if (poz->pos == NULL)
    {
        printf("We don't have element with this key\n");
        return 0;
    }
    if (poz->pos->keys[poz->i].key == B_max(root)->pos->keys[(B_max(root))->i].key)
    {
        printf("We don't have next element\n");
        return 0;
    }
    abc(x, poz);
}