#include "lista.h"

//initializarea listei
TLista IniList(void (*elib)(void*), void (*print)(void*, FILE*))
{
    TLista aux = (TLista) malloc(sizeof(struct lista));
    aux->prim = NULL;
    aux->elib = elib;
    aux->print = print;
    return aux;
}

//initializarea celulei
TCelula* AlocCelula(void *info, TCelula *urm)
{
    TCelula *aux = (TCelula*) malloc(sizeof(TCelula));
    aux->info = info;
    aux->urm = urm;
    return aux;
}

//inserarea primului element in lista
void InsPrim(TLista L, void* info)
{
    L->prim = AlocCelula(info, L->prim);
}

//afisarea listei
void AfisareL(TLista L, FILE* f)
{
    TCelula* aux = L->prim;
    fprintf(f, "[");
    while(aux != NULL)
    {
        L->print(aux->info, f);
        if(aux->urm != NULL)
            fprintf(f, ", ");
        aux = aux->urm;
    }
    fprintf(f, "]");
}

//distrugere lista
void DistrugeL(TLista L)
{
    TCelula *aux, *urm;
    aux = L->prim;
    while(aux != NULL)
    {
        urm = aux->urm;
        L->elib(aux->info);
        free(aux);
        aux = urm;
    }
    free(L);
}

//extrage primul element
void* ExtrPrim(TLista L)
{
    void* aux;
    TCelula* C = L->prim;
    if(L->prim == NULL)
        return NULL;
    aux = C->info;
    L->prim = L->prim->urm;
    free(C);
    return aux;
}

//inserare la final
void InsUlt(TLista L, void* info, int* poz)
{
    *poz = 1;
    if(L->prim == NULL)
        L->prim = AlocCelula(info, NULL);
    else
    {
        TCelula *aux = L->prim;
        *poz = 2;
        while(aux->urm != NULL)
        {
            aux = aux->urm;
            *poz = *poz + 1;
        }
        aux->urm = AlocCelula(info, NULL);
    }
}

//inserare la pozitia poz
void InsPoz(TLista L, void* info, int poz)
{
    if(poz == 1)
        L->prim = AlocCelula(info, L->prim);
    else
    {
        TCelula* aux = L->prim;
        while(poz != 2 && aux->urm != NULL)
        {
            aux = aux->urm;
            poz--;
        }
        aux->urm = AlocCelula(info, aux->urm);
    }
}

//extrage elementul cu valoarea info
void* ExtrInfo(TLista L, void* info, int (*cmp)(void*, void*))
{
    if(L->prim == NULL)
        return NULL;
    TCelula* C = L->prim;
    void* aux;
    if(cmp(L->prim->info, info) == 0)
    {
        aux = C->info;
        L->prim = L->prim->urm;
        free(C);
        return aux;
    }
    while(C->urm != NULL)
    {
        if(cmp(C->urm->info, info) == 0)
        {
            TCelula* C2 = C->urm;
            aux = C2->info;
            C->urm = C->urm->urm;
            free(C2);
            return aux;
        }
        C = C->urm;
    }
    return NULL;
}

//cauta in lista si returneaza elementul cu valoarea info
void* CautInfo(TLista L, void* info, int (*cmp)(void*, void*))
{
    TCelula* aux = L->prim;
    while(aux != NULL)
        if(cmp(aux->info, info) == 0)
            return aux->info;
        else
            aux = aux->urm;
    return NULL;
}

//inserare la pozitia care convine astfel incat valorile sa fie ordonate dupa cerinta
void InsOrd(TLista L, void* info, int (*cmp)(void*, void*), int* poz)
{
    *poz = 1;
    if(L->prim == NULL)
        L->prim = AlocCelula(info, NULL);
    else
    {
        if(cmp(L->prim->info, info) > 0)
        {
            L->prim = AlocCelula(info, L->prim);
            return;
        }
        TCelula* aux = L->prim;
        *poz = 2;
        while(aux->urm != NULL && cmp(aux->urm->info, info) < 0)
        {
            aux = aux->urm;
            *poz = *poz + 1;
        }
        aux->urm = AlocCelula(info, aux->urm);
    }
}