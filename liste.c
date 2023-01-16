
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// SISTEMA = 1 -> Sistema Linux;
// SISTEMA = 0 -> Sistema Windows;
#ifndef SISTEMA
#define SISTEMA 0
#endif

#if SISTEMA == 0
char *pulisci = "cls";
#elif SISTEMA == 1
char *pulisci = "clear";
#endif

#ifndef T_CONTATTO
#define T_CONTATTO
typedef struct
{
    char nome[50];
    char cognome[50];
    char telefono[30];
    char email[100];
} t_contatto;
#endif

#ifndef ELEMENTO
#define ELEMENTO
struct elemento
{
    t_contatto inf;
    struct elemento *pun;
};
#endif

void visualizzaContatto(struct elemento *p);
struct elemento *aggiungiContatto(struct elemento *p);
struct elemento *modificaContatto(struct elemento *p);
struct elemento *rimuoviContatto(struct elemento *p);
struct elemento *leggiDaFile(struct elemento *p);
int salvaSuFile(struct elemento *p);
void substring(char *dest, char *source, int i_base, int i_dim);
void pausa();

int main()
{

    int scelta;
    struct elemento *lista = NULL;

    for (;;)
    {

        system(pulisci);
        printf(" #######################\n");
        printf(" # RUBRICA             #\n");
        printf(" #######################\n\n");
        printf(" 1) VISUALIZZA CONTATTO\n\n");
        printf(" 2) AGGIUNGI CONTATTO\n\n");
        printf(" 3) MODIFICA CONTATTO\n\n");
        printf(" 4) RIMUOVI CONTATTO\n\n");
        printf(" 5) LEGGI CONTATTI DA FILE\n\n");
        printf(" 6) SALVA CONTATTI SU FILE\n\n");
        printf(" 0) ESCI\n\n\n\n");
        printf(" la tua scelta > ");

        scanf("%d", &scelta);
        scelta = (int)scelta;

        if (scelta == 0)
        {

            system(pulisci);
            break;
        }
        else if (scelta == 1)
        {

            visualizzaContatto(lista);
        }
        else if (scelta == 2)
        {

            lista = aggiungiContatto(lista);
        }
        else if (scelta == 3)
        {

            lista = modificaContatto(lista);
        }
        else if (scelta == 4)
        {

            lista = rimuoviContatto(lista);
        }
        else if (scelta == 5)
        {

            lista = leggiDaFile(lista);
        }
        else if (scelta == 6)
        {

            salvaSuFile(lista);
        }
    }
}

void visualizzaContatto(struct elemento *p)
{

    if (p == NULL)
    {

        system(pulisci);
        printf(" Nessun contatto presente\n");
        pausa();
    }
    else
    {

        system(pulisci);
        printf(" # VISUALIZZA CONTATTO #\n");
        printf(" NOME > %s\n", p->inf.nome);
        printf(" COGNOME > %s\n", p->inf.cognome);
        printf(" TELEFONO > %s\n", p->inf.telefono);
        printf(" EMAIL > %s\n", p->inf.email);
        pausa();
    }
    while (p != NULL)
    {

        system(pulisci);
        printf(" # VISUALIZZA CONTATTO #\n");
        printf(" NOME > %s\n", p->inf.nome);
        printf(" COGNOME > %s\n", p->inf.cognome);
        printf(" TELEFONO > %s\n", p->inf.telefono);
        printf(" EMAIL > %s\n", p->inf.email);
        pausa();

        p = p->pun;
    }

    return;
}

struct elemento *aggiungiContatto(struct elemento *p)
{

    system(pulisci);
    printf(" # AGGIUNGI CONTATTO   #\n");

    char nome[50];
    char cognome[50];
    char telefono[30];
    char email[100];
    t_contatto daInserire;
    struct elemento *punt;

    printf(" NOME > ");
    scanf("%s", nome);
    strcpy(daInserire.nome, nome);
    printf(" COGNOME > ");
    scanf("%s", cognome);
    strcpy(daInserire.cognome, cognome);
    printf(" TELEFONO > ");
    scanf("%s", telefono);
    strcpy(daInserire.telefono, telefono);
    printf(" EMAIL > ");
    scanf("%s", email);
    strcpy(daInserire.email, email);

    if (p != NULL)
    {

        punt = (struct elemento *)malloc(sizeof(struct elemento));

        punt->inf = daInserire;

        punt->pun = p;
    }
    else
    {
        p = (struct elemento *)malloc(sizeof(struct elemento));

        p->inf = daInserire;

        p->pun = NULL;

        punt = p;
    }

    return (punt);
}

struct elemento *modificaContatto(struct elemento *p)
{

    struct elemento *twin = p;
    int subscelta;
    int i = 1;
    int n = 1;

    system(pulisci);
    printf(" # MODIFICA CONTATTO   #\n");

    while (p != NULL)
    {

        printf("%i) \t %s \t %s\n", i, p->inf.nome, p->inf.cognome);
        p = p->pun;
        i++;
    }

    p = twin;

    printf("\n\n Inserisci il numero del contatto che vuoi modificare: ");
    scanf("%i", &subscelta);

    for (n = 1; n < i; n++)
    {

        if (subscelta == n)
        {

            printf(" NOME [%s] > ", p->inf.nome);
            scanf("%s", p->inf.nome);
            printf(" COGNOME [%s] > ", p->inf.cognome);
            scanf("%s", p->inf.cognome);
            printf(" TELEFONO [%s] > ", p->inf.telefono);
            scanf("%s", p->inf.telefono);
            printf(" EMAIL [%s] > ", p->inf.email);
            scanf("%s", p->inf.email);
        }

        p = p->pun;
    }

    return twin;
}

struct elemento *rimuoviContatto(struct elemento *p)
{
    struct elemento *aus;
    struct elemento *twin = p;
    int subscelta;
    int i = 1;
    int n = 1;

    system(pulisci);

    printf(" # RIMUOVI CONTATTO    #\n");

    while (p != NULL)
    {

        printf("%i) \t %s \t %s\n", i, p->inf.nome, p->inf.cognome);
        p = p->pun;
    }

    p = twin;

    printf("\n\n Inserisci il numero del contatto che vuoi rimuovere: ");
    scanf("%i", &subscelta);

    if (subscelta < i)
    {

        if (p == NULL)
            return NULL;

        if (p->pun != NULL)
        {

            aus = p;
            n++;

            while (n != i)
            {

                if (subscelta == n)
                {

                    aus->pun = aus->pun->pun;
                }
                else
                {

                    aus = aus->pun;
                }

                n++;
            }
        }

        if (subscelta == 1)
        {

            p = p->pun;
        }
    }

    twin = p;

    return twin;
}

struct elemento *leggiDaFile(struct elemento *p)
{

    t_contatto daInserire;
    t_contatto vuoto;
    struct elemento *punt = p;
    char linea[500];
    int index = 0;

    FILE *stream = fopen("rubrica.txt", "r");

    while (fgets(linea, 500, stream) != NULL)
    {

        index = strcspn(linea, ",");
        strncpy(daInserire.nome, linea, index);
        substring(daInserire.nome, daInserire.nome, 0, index - 1);
        substring(linea, linea, index + 1, strlen(linea));
        index = strcspn(linea, ",");
        strncpy(daInserire.cognome, linea, index);
        substring(daInserire.cognome, daInserire.cognome, 0, index - 1);
        substring(linea, linea, index + 1, strlen(linea));
        index = strcspn(linea, ",");
        strncpy(daInserire.telefono, linea, index);
        substring(daInserire.telefono, daInserire.telefono, 0, index - 1);
        substring(linea, linea, index + 1, strlen(linea));
        index = strcspn(linea, ",");
        strncpy(daInserire.email, linea, index);
        substring(daInserire.email, daInserire.email, 0, index - 1);
        substring(linea, linea, index + 1, strlen(linea));

        p = punt;
        punt = (struct elemento *)malloc(sizeof(struct elemento));
        punt->inf = daInserire;
        punt->pun = p;

        daInserire = vuoto;
    }

    fflush(stream);
    fclose(stream);

    return (punt);
}

int salvaSuFile(struct elemento *p)
{

    FILE *stream = fopen("rubrica.txt", "w");

    while (p != NULL)
    {

        fprintf(stream, "%s,%s,%s,%s\n", p->inf.nome, p->inf.cognome, p->inf.telefono, p->inf.email);

        p = p->pun;
    }

    fflush(stream);
    fclose(stream);

    return 0;
}

void substring(char *dest, char *source, int i_base, int i_dim)
{
    int i = 0;

    for (i = i_base; i < i_dim + 1; i++)
    {

        dest[i - i_base] = source[i];
    }

    dest[i] = '\0';

    return;
}

void pausa()
{
    char invio;
    printf("\n\n - premi INVIO per continuare -\n");
    invio = getchar();
    return;
}