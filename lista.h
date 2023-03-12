#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//structura celulei
typedef struct celula{
    void* info;
    struct celula *urm;
} TCelula;

//structura listei
typedef struct lista{
    TCelula *prim;
    void (*elib)(void*);
    void (*print)(void*, FILE*);
} *TLista;

//functiile folosite
TLista IniList(void (*elib)(void*), void (*print)(void*, FILE*));
TCelula* AlocCelula(void *info, TCelula *urm);
void InsPrim(TLista L, void* info);
void AfisareL(TLista L, FILE* f);
void DistrugeL(TLista L);
void* ExtrPrim(TLista L);
void DelPrim(TLista L);
void InsUlt(TLista L, void* info, int* poz);
void InsPoz(TLista L, void* info, int poz);
void* ExtrInfo(TLista L, void* info, int (*cmp)(void*, void*));
void DelInfo(TLista L, void* info, int (*cmp)(void*, void*));
void* CautInfo(TLista L, void* info, int (*cmp)(void*, void*));
void InsOrd(TLista L, void* info, int (*cmp)(void*, void*), int* poz);

#endif