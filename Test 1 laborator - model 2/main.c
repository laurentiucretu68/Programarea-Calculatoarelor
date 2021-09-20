#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Definirea structurii
typedef struct{
    char nume[30];
    char clasa_zbor;
    float greutate_bagaje;
    unsigned int cod;
}Pasager;

///Subpunctul 1
void citire(int nrPasageri,Pasager p[])
{
    for (int i=0; i<nrPasageri; i++)
    {
        printf("Pasagerul cu nr %d:\n",i+1);
        scanf("%s %c %500f",p[i].nume,&p[i].clasa_zbor,&p[i].greutate_bagaje);
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
            if (p[i].greutate_bagaje>p[j].greutate_bagaje)
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
        ///Aflarea numarului de pasageri de pe prima linie
        int nrPasageri=0;
        char buffer[30];
        char c;
        fscanf(fin,"%c",&c); fseek(fin,0,SEEK_SET);
        while (c!='\n')
        {
            fscanf(fin,"%s",buffer);
            fscanf(fin,"%c",&c);
            fseek(fin,-1,SEEK_CUR);
            nrPasageri++;
        }
        fseek(fin,0,SEEK_SET);
        ///***********///

        for (int i=1; i<=nrPasageri; i++)
        {
            char nume[30];
            char clasa_auxiliar[2];
            char clasa_zbor;
            float greutate_bagaje;

            ///Citirea numelor pasagerilor pana la pozitia i
            for (int j=1; j<=i-1; j++)
                fscanf(fin,"%s",buffer);
            ///Citirea numelui pasagerului de pe pozitia i
            fscanf(fin,"%s",nume);
            ///Citirea numelor pasagerilor dupa pozitia i
            for (int j=i+1; j<=nrPasageri; j++)
                fscanf(fin,"%s",buffer);

            ///Citirea claselor pasagerilor pana la pozitia i
            for (int j=1; j<=i-1; j++)
                fscanf(fin,"%s",buffer);
            ///Citirea clasei pasagerului de pe pozitia i
            fscanf(fin,"%s",clasa_auxiliar);
            clasa_zbor=clasa_auxiliar[0];
            ///Citirea claselor pasagerilor dupa pozitia i
            for (int j=i+1; j<=nrPasageri; j++)
                fscanf(fin,"%s",buffer);

            ///Citirea greutatii bagajelor pasagerilor pana la pozitia i
            for (int j=1; j<=i-1; j++)
                fscanf(fin,"%s",buffer);
            ///Citirea greutatii bagajului pasagerului de pe pozitia i
            fscanf(fin,"%f",&greutate_bagaje);
            ///Citirea greutatii bagajelor pasagerilor dupa pozitia i
            for (int j=i+1; j<=nrPasageri; j++)
                fscanf(fin,"%s",buffer);

            ///Executarea interogarii din enunt
            if (clasa_zbor=='B' && greutate_bagaje>30)
                printf("%s %c %.2f\n",nume,clasa_zbor,greutate_bagaje);

            ///Reintoarcerea la prima linie din fisier
            fseek(fin,0,SEEK_SET);
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
