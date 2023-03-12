#ifndef STIVA_H_INCLUDED
#define STIVA_H_INCLUDED

#include "lista.h"

typedef struct stiva{
    TLista L;
}*TStack;

//functiile folosite
TStack InitS(void (*elib)(void*), void (*print)(void*, FILE*));
void Push(TStack S, void* info);
void* Pop(TStack S);
void DistrS(TStack S);
void* ExtrInfoS(TStack S, void* info, int (*cmp)(void*, void*));

#endif