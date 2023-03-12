//ALEXANDRESCU MARIUS-CRISTIAN - 315CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "coada.h"
#include "stiva.h"

//structura unui serial
typedef struct serial{
    int id, nr_sez, dur;
    char* nume;
    float rating;
    TLista sez;
}Series;

//structura unui sezon
typedef struct sezon{
    int nr_ep;
    TLista ep;
}Season;

//structura unui episod
typedef struct episod{
    int len;
}Episode;

//stergere serial
void del_ser(void* a)
{
    Series* aux = (Series*) a;
    free(aux->nume);
    DistrugeL(aux->sez);
    free(aux);
}

//afisare serial
void prt_ser(void* a, FILE* f)
{
    Series* aux = (Series*) a;
    fprintf(f, "(%s, %.1f)", aux->nume, aux->rating);
}

//functia de comparare dupa rating
int crating(void* a, void* b)
{
    Series* x = (Series*) a;
    Series* y = (Series*) b;
    if(x->rating < y->rating)
        return 1;
    else
        if(x->rating > y->rating)
            return -1;
        else
            return strcmp(x->nume, y->nume);
}

//functia care compara 2 nume de serial
int cname(void* a, void* b)
{
    Series* x = (Series*) a;
    Series* y = (Series*) b;
    return strcmp(x->nume, y->nume);
}

//creeaza lista de top 10 dupa rating
void top10(TLista L)
{
    int poz = 1;
    TCelula *aux, *urm;
    aux = L->prim;
    while(poz != 10 && aux != NULL)
    {
        aux = aux->urm;
        poz++;
    }
    if(aux != NULL)
    {
        urm = aux->urm;
        aux->urm = NULL;
        aux = urm;
        while(aux != NULL)
        {
            urm = aux->urm;
            L->elib(aux->info);
            free(aux);
            aux = urm;
        }
    }
}

//stergere sezon
void del_sez(void* a)
{
    Season* aux = (Season*) a;
    DistrugeL(aux->ep);
    free(aux);
}

//stergere episod
void del_ep(void* a)
{
    Episode* aux = (Episode*) a;
    free(aux);
}

int main(int argc, char** argv)
{
    TLista Tendinte, Documentare, Tutoriale, Top10;
    TQueue Watch_later;
    TStack Currently_watching, History;

    Tendinte = IniList(del_ser, prt_ser);
    Documentare = IniList(del_ser, prt_ser);
    Tutoriale = IniList(del_ser, prt_ser);
    Top10 = IniList(del_ser, prt_ser);
    Watch_later = InitQ(del_ser, prt_ser);
    Currently_watching = InitS(del_ser, prt_ser);
    History = InitS(del_ser, prt_ser);

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    int poz, j, k;
    char i[35];
    while(fscanf(in, "%s", i) == 1)
        if(strcmp(i, "add") == 0)
        {
            Series* new = (Series*) malloc(sizeof(Series));
            new->nume = (char*) malloc(32 * sizeof(char));
            new->sez = IniList(del_sez, NULL);
            fscanf(in, "%d %s %f %d", &new->id, new->nume, &new->rating, &new->nr_sez);
            for(j = 0; j < new->nr_sez; j++)
            {
                Season* new_s = (Season*) malloc(sizeof(Season));
                new_s->ep = IniList(del_ep, NULL);
                fscanf(in, "%d", &new_s->nr_ep);
                for(k = 0; k < new_s->nr_ep; k++)
                {
                    Episode* new_ep = (Episode*) malloc(sizeof(Episode));
                    fscanf(in, "%d", &new_ep->len);
                    new->dur += new_ep->len;
                    InsUlt(new_s->ep, (void*) new_ep, &poz);
                }
                InsUlt(new->sez, (void*) new_s, &poz);
            }
            switch (new->id)
            {
            case 1:
                InsOrd(Tendinte, (void*) new, crating, &poz);
                break;
            case 2:
                InsOrd(Documentare, (void*) new, crating, &poz);
                break;
            case 3:
                InsOrd(Tutoriale, (void*) new, crating, &poz);
                break;
            }
            fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", new->nume, poz);
        }
        else
            if(strcmp(i, "add_sez") == 0)
            {
                Series* aux = (Series*) malloc(sizeof(Series));
                aux->nume = (char*) malloc(sizeof(char) * 32);
                int sez_dur = 0;
                fscanf(in, "%s", aux->nume);
                Season* new_s = (Season*) malloc(sizeof(Season));
                new_s->ep = IniList(del_ep, NULL);
                fscanf(in, "%d", &new_s->nr_ep);
                for(j = 0; j < new_s->nr_ep; j++)
                {
                    Episode* new_ep = (Episode*) malloc(sizeof(Episode));
                    fscanf(in, "%d", &new_ep->len);
                    sez_dur += new_ep->len;
                    InsUlt(new_s->ep, (void*) new_ep, &poz);
                }
                Series* s_gasit = (Series*) malloc(sizeof(Series));
                void* s_cautat = NULL;
                s_cautat = CautInfo(Tendinte, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(Documentare, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(Tutoriale, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(Top10, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(Watch_later->L, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(Currently_watching->L, (void*) aux, cname);
                if(s_cautat == NULL)
                    s_cautat = CautInfo(History->L, (void*) aux, cname);
                s_gasit = (Series*) s_cautat;
                InsUlt(s_gasit->sez, (void*) new_s, &poz);
                free(aux->nume);
                free(aux);
                fprintf(out, "Serialul %s are un sezon nou.\n", s_gasit->nume);
                s_gasit->dur += sez_dur;
            }
            else
                if(strcmp(i, "add_top") == 0)
                {
                    Series* aux = (Series*) malloc(sizeof(Series));
                    aux->nume =(char*) malloc(sizeof(char) * 32);
                    aux->sez = IniList(del_sez, NULL);
                    int POZ;
                    fscanf(in, "%d", &POZ);
                    fscanf(in, "%s %f %d", aux->nume, &aux->rating, &aux->nr_sez);
                    for(j = 0; j < aux->nr_sez; j++)
                    {
                        Season* aux_s = (Season*) malloc(sizeof(Season));
                        aux_s->ep = IniList(del_ep, NULL);
                        fscanf(in, "%d", &aux_s->nr_ep);
                        for(k = 0; k < aux_s->nr_ep; k++)
                        {
                            Episode* aux_ep = (Episode*) malloc(sizeof(Episode));
                            fscanf(in, "%d", &aux_ep->len);
                            aux->dur += aux_ep->len;
                            InsUlt(aux_s->ep, (void*) aux_ep, &poz);
                        }
                        InsUlt(aux->sez, (void*) aux_s, &poz);
                    }
                    InsPoz(Top10, (void*) aux, POZ);
                    top10(Top10);
                    fprintf(out, "Categoria top10: ");
                    AfisareL(Top10, out);
                    fprintf(out, ".\n");
                }
                else
                    if(strcmp(i, "later") == 0)
                    {
                        Series* aux = (Series*) malloc(sizeof(Series));
                        aux->nume = (char*) malloc(sizeof(char) * 32);
                        void* s_cautat = NULL;
                        fscanf(in, "%s", aux->nume);
                        s_cautat = ExtrInfo(Tendinte, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfo(Documentare, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfo(Tutoriale, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfo(Top10, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfoQ(Watch_later, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfoS(Currently_watching, (void*) aux, cname);
                        if(s_cautat == NULL)
                            s_cautat = ExtrInfoS(History, (void*) aux, cname);
                        fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", aux->nume, IntrQ(Watch_later, s_cautat));
                        free(aux->nume);
                        free(aux);
                    }
                    else
                        if(strcmp(i, "watch") == 0)
                        {
                            Series* aux = (Series*) malloc(sizeof(Series));
                            aux->nume = (char*) malloc(sizeof(char) * 32);
                            int dur;
                            fscanf(in, "%s", aux->nume);
                            fscanf(in, "%d", &dur);
                            Series* s_gasit;
                            void* s_cautat = NULL;
                            s_cautat = ExtrInfo(Tendinte, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfo(Documentare, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfo(Tutoriale, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfo(Top10, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfoQ(Watch_later, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfoS(Currently_watching, (void*) aux, cname);
                            if(s_cautat == NULL)
                                s_cautat = ExtrInfoS(History, (void*) aux, cname);
                            s_gasit = (Series*) s_cautat;
                            if(s_gasit->dur > dur)
                            {
                                Push(Currently_watching, (void*)s_gasit);
                                s_gasit->dur -= dur;
                            }
                            else
                            {
                                Push(History, (void*)s_gasit);
                                fprintf(out, "Serialul %s a fost vizionat integral.\n", aux->nume);
                            }
                        }
                        else
                            if(strcmp(i, "show") == 0)
                            {
                                char X[10];
                                fscanf(in, "%s", X);
                                if(strcmp(X, "1") == 0)
                                {
                                    fprintf(out, "Categoria 1: ");
                                    AfisareL(Tendinte, out);
                                    fprintf(out, ".\n");
                                }
                                else
                                    if(strcmp(X, "2") == 0)
                                    {
                                        fprintf(out, "Categoria 2: ");
                                        AfisareL(Documentare, out);
                                        fprintf(out, ".\n");
                                    }
                                    else
                                        if(strcmp(X, "3") == 0)
                                        {
                                            fprintf(out, "Categoria 3: ");
                                            AfisareL(Tutoriale, out);
                                            fprintf(out, ".\n");
                                        }
                                        else
                                            if(strcmp(X, "top10") == 0)
                                            {
                                                fprintf(out, "Categoria top10: ");
                                                AfisareL(Top10, out);
                                                fprintf(out, ".\n");
                                            }
                                            else
                                                if(strcmp(X, "later") == 0)
                                                {
                                                    fprintf(out, "Categoria later: ");
                                                    AfisareL(Watch_later->L, out);
                                                    fprintf(out, ".\n");
                                                }
                                                else
                                                    if(strcmp(X, "watching") == 0)
                                                    {
                                                        fprintf(out, "Categoria watching: ");
                                                        AfisareL(Currently_watching->L, out);
                                                        fprintf(out, ".\n");
                                                    }
                                                    else
                                                        if(strcmp(X, "history") == 0)
                                                        {
                                                            fprintf(out, "Categoria history: ");
                                                            AfisareL(History->L, out);
                                                            fprintf(out, ".\n");
                                                        }
                            }
    DistrugeL(Tendinte);
    DistrugeL(Documentare);
    DistrugeL(Tutoriale);
    DistrugeL(Top10);
    DistrQ(Watch_later);
    DistrS(Currently_watching);
    DistrS(History);

    fclose(in);
    fclose(out);
    return 0;
}