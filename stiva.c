#include "stiva.h"

//initializare stiva
TStack InitS(void (*elib)(void*), void (*print)(void*, FILE*))
{
    TStack aux = malloc(sizeof(struct stiva));
    aux->L = IniList(elib, print);
    return aux;
}

//pune in stiva valoarea info
void Push(TStack S, void* info)
{
    InsPrim(S->L, info);
}

//extrage elementul din varful stivei
void* Pop(TStack S)
{
    return ExtrPrim(S->L);
}

//distruge stiva
void DistrS(TStack S)
{
    DistrugeL(S->L);
    free(S);
}

//cauta un elementul cu valoarea info in stiva folosind o stiva ajutatoare
void* ExtrInfoS(TStack S, void* info, int (*cmp)(void*, void*))
{
    TStack aux = InitS(S->L->elib, NULL);
    void *x, *y;
    while(S->L->prim != NULL && cmp(S->L->prim->info, info) != 0)
    {
        x = Pop(S);
        Push(aux, x);
    }
    x = Pop(S);
    while(aux->L->prim != NULL)
    {
        y = Pop(aux);
        Push(S, y);
    }
    DistrS(aux);
    return x;
}