#ifndef COADA_H_INCLUDED
#define COADA_H_INCLUDED

#include "lista.h"

//structura cozii
typedef struct coada{
    TLista L;
}*TQueue;

//functiile folosite
TQueue InitQ(void (*elib)(void*), void (*print)(void*, FILE*));
int IntrQ(TQueue Q, void* info);
void* ExtrQ(TQueue Q);
void DistrQ(TQueue Q);
void* ExtrInfoQ(TQueue Q, void* info, int (*cmp)(void*, void*));

#endif