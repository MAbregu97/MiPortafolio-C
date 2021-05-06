#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int cod;
    char desc[31];
    int stock;
} info;

typedef struct
{
    int m;
    int ca;
    int cup;
} produccion;

void grabart (void);
void grabprod(void);
void lecturart (void);
int busqueda (info[],int,int);
void lecturprod (void);
int validarIVR (int, int, int);

int main ()
{
    info art;
    int opcion;
    do
    {
        printf("SELECCIONE UNA OPCION:");
        printf("\n  1. GRABACION");
        printf("\n  2. LECTURA");
        printf("\n Cualquier otro numero sale.\n\n");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                printf("\n  1. ARTICULOS\n  2. PRODUCCION\n\n");
                scanf("%d",&opcion);
                if (opcion==1)
                    grabart();
                else
                    grabprod();
                break;
            case 2:
                printf("\n  1. ARTICULOS\n  2. PRODUCCION\n\n");
                scanf("%d",&opcion);
                if (opcion==1)
                    lecturart();
                else
                    lecturprod();
        }
    }while (!(opcion!=1 && opcion!=2));
}

void grabart(void)
{
    FILE*pf;
    info art;
    int nro,i,codigo;
    i=0;
    pf=fopen("ARTICULOS.dat","wb");
    if(pf==NULL)
    {
        printf("\nNO SE PUEDE ACCEDER AL ARCHIVO");
        getch();
        exit(0);
    }
    printf("\n\n----COMPLETE CON LA INFORMACION DE LOS ARTICULOS----\n\t\t(finaliza con codigo 0)\n");
    printf("\n-ARTICULO %d-",i+1);
    printf("\nCODIGO: ");
    codigo=validarIVR(0,1000,9999);
    while (!(codigo==0))
    {
        art.cod=codigo;
        printf("DESCRIPCION: ");
        fflush(stdin);
        gets(art.desc);
        printf("STOCK: ");
        scanf("%d",&art.stock);
        fwrite(&art,sizeof(info),1,pf);
        i++;
        printf("\n-ARTICULO %d-",i+1);
        printf("\nCODIGO: ");
        codigo=validarIVR(0,1000,9999);
    }
    fclose(pf);
    printf("\n---FIN DEL INGRESO DE DATOS---\n\n");
}

void grabprod(void)
{
    FILE*pa,*pp;
    info art[100];
    produccion anio[100];
    int ca,i,mes,pos;
    i=0;
    ca=0;
    pa=fopen("ARTICULOS.dat","rb");
    pp=fopen("PRODUCCION.dat","wb");
    if (pa==NULL)
    {
        printf("\nNo se puede acceder al archivo.");
        getch();
        exit(0);
    }
    fread(&art[ca],sizeof(info),1,pa);
    while (!(feof(pa)))
    {
        ca++;
        fread(&art[ca],sizeof(info),1,pa);
    }
    printf("\n\n----COMPLETE CON LA INFORMACION DE LAS VENTAS----\n\t   (finaliza con mes 0)\n");
    printf("\n-PRODUCCION %d-\n",i+1);
    printf("MES: ");
    mes=validarIVR(0,1,12);
    while (!(mes==0))
    {
        anio[i].m=mes;
        do
        {
            printf("CODIGO:");
            anio[i].ca=validarIVR(0,1000,9999);
            pos=busqueda(art,anio[i].ca,100);
            if (pos==-1)
                printf("\nEl codigo ingresado no existe. Por favor Reintentar.\n\n");
        } while (!(pos!=-1));
        printf("CANTIDAD DE UNIDADES PRODUCIDAS: ");
        scanf("%d",&anio[i].cup);
        fwrite(&anio[i],sizeof(produccion),1,pp);
        i++;
        printf("\n-PRODUCCION %d-\n",i+1);
        printf("MES: ");
        mes=validarIVR(0,1,12);
    }
    fclose(pa);
    fclose(pp);
}

int validarIVR(int valor, int min, int max)
{
    int dato,b;
    b=0;
    do
    {
        if(b==1)
            printf("\nERROR. Por favor reintentar.\n");
        b=1;
        scanf("%d",&dato);
    }while(!(dato==0 || (dato>=min && dato<=max)));
    return dato;
}

void lecturart (void)
{
    info art[100];
    FILE*pf;
    int i,ca;
    ca=0;
    pf=fopen("ARTICULOS.dat","rb");
    if (pf==NULL)
    {
        printf("\nNo se puede acceder al archivo.");
        getch();
        exit(0);
    }
    fread(&art[ca],sizeof(info),1,pf);
    while (!(feof(pf)))
    {
        ca++;
        fread(&art[ca],sizeof(info),1,pf);
    }
    printf("\n////////////////DATOS DEL ARCHIVO////////////////");
    for (i=0;i<ca;i++)
    {
        printf("\n-ARTICULO %d-",i+1);
        printf("\nCODIGO: %d",art[i].cod);
        printf("\nDESCRIPCION: %s",art[i].desc);
        printf("\nSTOCK: %d",art[i].stock);
        printf("\n");
    }
    fclose(pf);
    printf("\n\n");
}

int busqueda (info arti[],int ca,int ce)
{
    int pos, i;
    pos=-1;
    i=0;
    while (!(pos!=-1 || i>=ce))
    {
        if (arti[i].cod==ca)
            pos=i;
        else
            i++;
    }
    return pos;
}

void lecturprod (void)
{
    produccion anio[100];
    FILE*pf;
    int i, ca;
    ca=0;
    pf=fopen("PRODUCCION.dat","rb");
    if (pf==NULL)
    {
        printf("\nNo se puede acceder al archivo.");
        getch();
        exit(0);
    }
    fread(&anio[ca],sizeof(produccion),1,pf);
    while (!(feof(pf)))
    {
        printf("\n\nVeces que leyo %d\n", ca+1);
        ca++;
        fread(&anio[ca],sizeof(produccion),1,pf);
    }
    printf("\n////////////////DATOS DEL ARCHIVO////////////////");
    for (i=0;i<ca;i++)
    {
        printf("\n-PRODUCCION %d-",i+1);
        printf("\nMES: %d",anio[i].m);
        printf("\nCODIGO: %d",anio[i].ca);
        printf("\nCant.Uni.Producidas: %d",anio[i].cup);
        printf("\n");
    }
    fclose(pf);
    printf("\n\n");
}
