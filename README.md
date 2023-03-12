# Tema2_SD

*ALEXANDRESCU MARIUS-CRISTIAN - 315CB*

*Tema 2*

Tema este compusa din 8 fisiere:
		- 4 fisiere .c;
		- 3 fisiere header;
		- 1 makefile.

In fisierul lista.c avem urmatoarele functii:

-IniList = initializeaza lista si aloca dinamic spatiu listei
		 = am folosit elib (primeste o functie care sterge lista
		   si elibereaza memoria ocupata de aceasta)
       
-AlocCelula = initializeaza celula listei si aloca dinamic spatiu acesteia

-InsPrim = adauga primul element in lista

-AfisareL = afiseaza lista in fisierul f dat ca parametru

-DistrugeL = distruge lista si elibereaza memoria

-ExtrPrim = extrage primul element din lista

-InsUlt = adauga un element pe ultima pozitie din lista

-InsPoz = adauga un element in lista pe pozitia poz data ca parametru

-ExtrInfo = extrage din lista elementul cu valoarea info dat ca parametru
		  = folosesc o functie cmp data ca parametru pentru compararea valorilor
      
-CautInfo = cauta si sterge elementul info dat ca parametru

-InsOrd = insereaza intr-o lista ordonata

In fisierul coada.c avem urmatoarele functii:

-InitQ = initializeaza coada si aloca dinamic spatiu cozii

-IntrQ = introduc valoarea info data ca parametru la sfarsitul
		 cozii si returneaza poztia sa
     
-ExtrQ = extrage primul element din coada

-DistrQ = distruge coada si elibereaza memoria acesteia

-ExtrInfoQ = extrage din coada elementul cu valoarea info dat ca parametru

In fisierul stiva.c avem urmatoarele functii:

-InitS = initializeaza stiva si aloca dinamic spatiu stivei

-Push = adauga in stiva valoarea info data ca parametru

-Pop = extrage primul element din stiva

-DistrS = distruge stiva si elibereaza memoria acesteia

-ExtrInfoS = extrage din stiva elementul cu valoarea info dat ca parametru

In fisierul main.c:

-declar structurile pentru serial, sezon si episod

-functia "del_ser" sterge si elibereaza memoria unui serial

-functia "prt_ser" afiseaza un serial in fisierul f dat ca parametru

-functia "crating" reprezinta functia de comparare dupa rating 
 folosita in functiile precedente
 
-functia "cname" reprezinta functia de comparare dupa nume folosita 
 in functiile precedente
 
-functia "top10" adauga in lista Top10 primele 10 seriale dupa rating (in caz
 de egalitate, dupa nume); daca exista deja 10 seriale, elementul se va adauga
 la pozitia favorabila, ultimul element fiind eliminat
 
-functia "del_sez" sterge si elibereaza memoria unui sezon

-functia "del_ep" sterge si elibereaza memoria unui episod

In main:

-intre liniile 111-121 declar si initializez listele, stivele si coada

-deschid fisierele de citire/scriere(123-124)

-de la linia 128 incep sa citesc instructiunile


-la linia 133, deoarece nu treuie sa afisam nimic din structura "sezon", am pus
	 NULL ca al doilea parametru al functiei "IniList"
   
-la linia 149 folosesc un switch case pentru a vedea in care din liste 
	 sa introduc serialul respectiv
   
-de la linia 181 caut serialul la care voi adauga sezonul

-intre liniile 203-230 avem cazul "add_top"

-la fel ca la cazul anterior, de la linia 238 incep cautarea in 
	 liste/stive/coada si elimin serialul
   
-intre liniile 256-288 avem cazul "watch"

-intre liniile 291-342 avem cazul "show" in care trec prin fiecare sub-caz
 in parte cu else-if
 
-la final, la liniile 344-350, distrug listele, iar apoi inchid fisierele(352-353)
