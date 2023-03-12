#include "coada.h"

//initializarea cozii
TQueue InitQ(void (*elib)(void*), void (*print)(void*, FILE*))
{
    TQueue aux = malloc(sizeof(struct coada));
    aux->L = IniList(elib, print);
    return aux;
}

//introduc un element la sfarsitul cozii si returnez pozitia sa
int IntrQ(TQueue Q, void* info)
{
    int poz;
    InsUlt(Q->L, info, &poz);
    return poz;
}

//extrage primul element din coada
void* ExtrQ(TQueue Q)
{
    return ExtrPrim(Q->L);
}

//distruge coada
void DistrQ(TQueue Q)
{
    DistrugeL(Q->L);
    free(Q);
}

//extrage elementul cu valoarea info din coada folosind o coada ajutatoare
void* ExtrInfoQ(TQueue Q, void* info, int (*cmp)(void*, void*))
{
    TQueue aux = InitQ(Q->L->elib, NULL);
    void *x, *y;
    while(Q->L->prim != NULL && cmp(Q->L->prim->info, info) != 0)
    {
        x = ExtrQ(Q);
        IntrQ(aux, x);
    }
    x = ExtrQ(Q);
    while(Q->L->prim != NULL)
    {
        y = ExtrQ(Q);
        IntrQ(aux, y);
    }
    while(aux->L->prim != NULL)
    {
        y = ExtrQ(aux);
        IntrQ(Q, y);
    }
    DistrQ(aux);
    return x;
}