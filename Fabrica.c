#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int cod;
    char desc[31];
    int stock;
} ARTI;

typedef struct
{
    int m;
    int ca;
    int cup;
} PRODU;

int lectura (ARTI [], int );
int busqueda(ARTI [],int ,int );
void informe_A(ARTI [],int [][12],int ,int );
void informe_B(ARTI [],int [][12],int ,int );
void sumastock(ARTI [],int [][12], int ,int );
void grabar(ARTI [], int );

int main ()
{
    ARTI vp[100];
    FILE*pf;
    PRODU INFO;
    int cant,pos, cprod[100][12]={{0}};

    cant=lectura (vp,100);
    pf=fopen("PRODUCCION.dat","rb");
    fread(&INFO,sizeof(PRODU),1,pf);
    while (!feof(pf))
    {
        pos=busqueda(vp,INFO.ca,cant);
        if (pos>=0)
            cprod[pos][INFO.m-1]+=INFO.cup;
        else
            printf("\nERROR PRODUCTO.");
        fread(&INFO,sizeof(PRODU),1,pf);
    }
    fclose(pf);
    informe_A(vp,cprod,cant,12);
    informe_B(vp,cprod,cant,12);
    sumastock(vp,cprod,cant,3);
    grabar(vp,cant);

    getch();
}

int lectura (ARTI v[], int ce)
{
    int i;
    FILE*pf;

    i=0;
    pf=fopen("ARTICULOS.dat","rb");
    if (pf==NULL)
    {
        printf("\nNo se puede acceder al archivo.");
        getch();
        exit(0);
    }
    fread(&v[i],sizeof(ARTI),1,pf);
    while (!(feof(pf) || i>=ce))
    {
        i++;
        fread(&v[i],sizeof(ARTI),1,pf);
    };
    fclose(pf);
    return i;
}

int busqueda(ARTI v[],int cod,int ce)
{
    int i,pos;
    i=0;
    pos=-1;
    while (!(pos>=0 || i>=ce))
    {
        if (v[i].cod==cod)
            pos=i;
        else
            i++;
    };
    return pos;
}

void informe_A(ARTI v[],int m[][12],int cf,int cc)
{
    int i,j;
    printf("   ARTICULO\t\t\t\t\t\tPRODUCCION DEL MES");
    printf("\nCODIGO\tDESCRIPCION\tENE\tFEB\tMAR\tABR\tMAY\tJUN\tJUL\tAGO\tSEP\tOCT\tNOV\tDIC");
    for(i=0;i<cf;i++)
    {
        printf("\n %d\t %s\t",v[i].cod,v[i].desc);
        for(j=0;j<cc;j++)
            printf("\t%d",m[i][j]);
    }
}

void informe_B(ARTI v[], int m[][12], int cf, int cc)
{
    int i,j, sum;

    printf("\n\nARTICULOS SIN PRODUCCION EN 365 DIAS\nCODIGO\tDESCRIPCION");
    for(i=0;i<cf;i++)
    {
        sum=0;
        for(j=0;j<cc;j++)
            sum+=m[i][j];
        if (sum==0)
            printf("\n %d\t%s",v[i].cod,v[i].desc);
    }
}

void sumastock (ARTI v[],int m[][12], int cf,int cc)
{
    int i,j;

    for(i=0;i<cf;i++)
    {
        for(j=0;j<cc;j++)
            v[i].stock+=m[i][j];
    }
}

void grabar (ARTI v[], int n)
{
    int i;

    FILE*pf;
    pf=fopen("ARTICULOSACT.dat","wb");
    for(i=0;i<n;i++)
        fwrite(&v[i],sizeof(ARTI),1,pf);
    fclose(pf);
}
