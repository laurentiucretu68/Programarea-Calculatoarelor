#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Definirea structurii
typedef struct{
    char nume[50];
    char clasa_zbor;
    float greutate_bagaje;
    unsigned int cod:4;
}Pasager;

///Subpunctul 1
void citire(int nrPasageri,Pasager p[])
{
    for (int i=0; i<nrPasageri; i++)
    {
        printf("Pasagerul cu nr %d:\n",i+1);
        scanf("%s %c %100f",p[i].nume,&p[i].clasa_zbor,&p[i].greutate_bagaje);
    }
}

///Subpunctul 2
void codificare(int nrPasageri,Pasager p[])
{
    for (int i=0; i<nrPasageri; i++)
    {
        int aux = (int)p[i].nume[0];
        p[i].cod=0;
        while (aux)
        {
            if ((aux&1)==0)
                p[i].cod++;
            aux=aux>>1;
        }
    }
}

///Subpunctul 3
void sortare(int nrPasageri,Pasager p[])
{
    for (int i=0; i<nrPasageri-1; i++)
        for (int j=i+1; j<nrPasageri; j++)
            if (p[i].clasa_zbor<p[j].clasa_zbor)
            {
                Pasager auxiliar = p[i];
                p[i] = p[j];
                p[j] = auxiliar;
            }
}

void afisare(int nrPasageri,Pasager p[])
{
    for (int i=0; i<nrPasageri; i++)
        printf("%s %c %.2f %u\n",p[i].nume,p[i].clasa_zbor,p[i].greutate_bagaje,p[i].cod);
}

///Subpunctul 4
void interogare(FILE* fin)
{
    if (!fin)
        printf("Fisierul nu exista!");
    else
    {
        ///Citire caracter cu caracter deoarece spatierea dintre campuri
        ///sa nu existe
        char nume[50];
        char clasa_zbor;
        float greutate_bagaje;
        char c;
        while (!feof(fin))
        {
            ///Citirea numelui
            c=fgetc(fin);
            if ((c<'A' || c>'Z') && (c<'a' || c>'z'))
                break;
            nume[0]=c;
            int i=1; c=fgetc(fin);
            while (c>='a' && c<='z')
            {
                nume[i]=c;
                i++;
                c=fgetc(fin);
            }
            nume[i]=NULL;
            ///**************************///
            if (c>='A' && c<='Z')
            {
                clasa_zbor=c;
                fscanf(fin,"%f",&greutate_bagaje);
            }
            else
            {
                ///Citirea caracterelor ' ' pana la clasa_zbor(A/B/C/D)
                while (c==' ')
                    c=fgetc(fin);
                clasa_zbor=c;
                fscanf(fin,"%f",&greutate_bagaje); ///Citirea greutatii bagajului
            }
            ///Verificarea conditiei din enunt
            if (greutate_bagaje>30)
                printf("%s\n",nume);

            c=fgetc(fin); ///Citirea caracterului \n
        }
    }
}

int main()
{
    int nrPasageri;
    Pasager p[100];
    FILE* fin = fopen("pasageri.txt","r");
    /*printf("Numarul de pasageri este: ");
    scanf("%d",&nrPasageri);
    citire(nrPasageri,p);
    codificare(nrPasageri,p);
    sortare(nrPasageri,p);
    afisare(nrPasageri,p);*/
    interogare(fin);
    return 0;
}
