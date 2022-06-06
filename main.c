#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>

const int maxServicios = 15;

typedef struct
{
    int IdCliente;
    int DNI;
    char apellidoYnombre[40];
    int telefono;
    char email[40];
    char domicilio[40];
    int BajaCliente;
} stCliente;

typedef struct
{
    int IdServicio;
    char Nombre[40];
    int costo;
} stServicio;

typedef struct
{
    int dia;
    int mes;
    int anio;
} stFecha;

typedef struct
{
    int IdTurno;
    stFecha fechaTurno;
    long int DNICliente;
    int IdCliente;
    char descripcion[300]
    stServicio servicios[maxServicios];
    int QServicios;
    int costoTotal;
    int Anulado;
} stTutno;

int ContarServicios(char Archivo[]);
stServicio CargarUnServicio(int id);
void CargarServicios(char Archivo[]);
void MostrarUnServicio(stServicio aux);
void MostrarServicios(char Archivo[]);
stCliente CargarUnCliente(int id);
int ValidacionCliente(char Archivo[], stCliente cliente);
void CargarClientes(char Archivo[]);
void MostrarUnCliente(stCliente aux);
void MostrarClientes(char Archivo[]);

int main()
{
    printf("\nCARGAR SERVICIOS\n");

    char ArchivoServicios[]="Servicios";

    CargarServicios(ArchivoServicios);

    printf("\n\n");
    system("pause");
    system("cls");

    MostrarServicios(ArchivoServicios);

    printf("\n\n");
    system("pause");
    system("cls");

    printf("\n\nCARGAR CLIENTES");

    char ArchivoClientes[]="Clientes";

    CargarClientes(ArchivoClientes);

    printf("\n\n");
    system("pause");
    system("cls");

    MostrarClientes(ArchivoClientes);

    return 0;
}

int ContarServicios(char Archivo[])
{
    FILE *buffer=fopen(Archivo, "rb");
    int i=0;
    stServicio aux;

    if(buffer== NULL)
    {
        i=0;
    }
    else
    {
        while(fread(&aux, sizeof(stServicio), 1, buffer) > 0)
        {
            i++;
        }

        fclose(buffer);
    }
    return i;
}

stServicio CargarUnServicio(int Id)
{
    stServicio servicio;

    servicio.IdServicio= Id + 1;

    printf("\nIngrese nombre del servicio:\n\n");
    fflush(stdin);
    gets(servicio.Nombre);

    printf("\nIngrese costo del servicio:\n\n");
    scanf("%i", &servicio.costo);

    return servicio;
}

void CargarServicios(char Archivo[])
{
    FILE *buffer= fopen(Archivo, "ab");
    int i=0;
    stServicio servicio;
    char control='s';

    if(buffer == NULL)
    {
        printf("\nNo pudo abrirse el archivo");
    }
    else
    {
        i=ContarServicios(Archivo);

        while(control=='s' || control=='S')
        {
            servicio= CargarUnServicio(i);

            fwrite(&servicio, sizeof(stServicio), 1, buffer);

            i++; ///contador para el id

            printf("\nQuiere seguir cargando? s o n\n");
            fflush(stdin);
            control= getch();
        }
        fclose(buffer);
    }
}

void MostrarUnServicio(stServicio aux)
{

    printf("\n\n\t---SERVICIO--\n");

    printf("\n\tID: %i", aux.IdServicio);
    printf("\n\tNombre: %s", aux.Nombre);
    printf("\n\tCosto: $%i", aux.costo);
}


void MostrarServicios(char Archivo[])
{
    FILE *buffer=fopen(Archivo, "rb");
    stServicio aux;

    if(buffer== NULL)
    {
        printf("\nNo pudo abrirse el archivo\n");
    }
    else
    {
        while(fread(&aux, sizeof(stServicio), 1, buffer) > 0)
        {

            MostrarUnServicio(aux);
        }

        fclose(buffer);
    }
}

int ContarClientes(char Archivo[])
{
    FILE *buffer=fopen(Archivo, "rb");
    int i=0;
    stCliente aux;

    if(buffer== NULL)
    {
        i=0;
    }
    else
    {
        while(fread(&aux, sizeof(stCliente), 1, buffer) > 0)
        {
            i++;
        }

        fclose(buffer);
    }
    return i;
}

stCliente CargarUnCliente(int Id) ///aca si no mando la posicion actual por par�metro no se graban los datos en el archivo hasta que no cierro el buffer y no los cuenta
{
    stCliente Cliente;
    int alta=1;

    Cliente.IdCliente= Id + 1;

    printf("\n\nIngrese DNI del cliente:\n\n");
    scanf("%i", &Cliente.DNI);

    printf("\nIngrese nombre completo del cliente:\n\n");
    fflush(stdin);
    gets(Cliente.apellidoYnombre);

    printf("\nIngrese telefono del cliente:\n\n");
    scanf("%i", &Cliente.telefono);

    printf("\nIngrese email del cliente:\n\n");
    fflush(stdin);
    gets(Cliente.email);

    printf("\nIngrese domicilio del cliente:\n\n");
    fflush(stdin);
    gets(Cliente.domicilio);

    Cliente.BajaCliente = alta;

    return Cliente;
}

int ValidacionCliente(char Archivo[], stCliente cliente)
{
    int flag=0;
    stCliente aux;

    FILE *buffer= fopen(Archivo, "rb");

    if(buffer == NULL)
    {
        printf("\nNo pudo abrirse el archivo");
    }
    else
    {
        while((fread(&aux, sizeof(stCliente), 1, buffer) > 0)&& flag==0)
        {
            if(cliente.DNI == aux.DNI)
            {
                flag=1;
            }
        }

    fclose(buffer);
    }
    return flag;
}

void CargarClientes(char Archivo[])
{
    FILE *buffer= fopen(Archivo, "ab");
    int i=0, validacion=0;
    stCliente cliente;
    char control='s';

    if(buffer == NULL)
    {
        printf("\nNo pudo abrirse el archivo");
    }
    else
    {
        i= ContarClientes(Archivo);

        while(control=='s' || control=='S')
        {
            cliente= CargarUnCliente(i);

            validacion= ValidacionCliente(Archivo, cliente);///Como validar un cliente cuando los datos no se guardan en el archivo?

            if(validacion== 0)
            {
                fwrite(&cliente, sizeof(stCliente), 1, buffer);

                i++;
            }
            else
            {
                printf("\n\n[!!]El cliente ya esta cargado en el sistema\n");
            }

            printf("\nQuiere seguir cargando? s o n\n");
            fflush(stdin);
            control= getch();
        }
        fclose(buffer);
    }
}

void MostrarUnCliente(stCliente aux)
{

    printf("\n\t---CLIENTE--\n");

    printf("\n\tID: %i", aux.IdCliente);
    printf("\n\tDNI: %i", aux.DNI);
    printf("\n\tNombre: %s", aux.apellidoYnombre);
    printf("\n\tTelefono: %i", aux.telefono);
    printf("\n\tEmail: %s", aux.email);
    printf("\n\tDomicilio: %s", aux.domicilio);
    if(aux.BajaCliente == 1)
    {
        printf("\n\tEstado: Activo\n");
    }
    else
    {
        printf("\n\tEstado: Inactivo\n");
    }

}

void MostrarClientes(char Archivo[])
{
    FILE *buffer=fopen(Archivo, "rb");
    stCliente aux;

    if(buffer== NULL)
    {
        printf("\nNo pudo abrirse el archivo\n");
    }
    else
    {
        while(fread(&aux, sizeof(stCliente), 1, buffer) > 0)
        {

            MostrarUnCliente(aux);
        }

        fclose(buffer);
    }
}
stFecha cargarFecha ()
{
    stFecha fecha;
    printf("dia (xx): ");
    scanf("%i", fecha.dia);
    printf("mes (xx): ");
    scanf("%i", fecha.mes);
    printf("anio (xx): ");
    scanf("%i", fecha.anio);
    return fecha;
}

stServicio buscarServicioPorID

int cargarArregloServicios (stServicio servicios[])
{
    char control = 's';
    int i=0;
    stServicio auxServi;
    while (i<maxServicios && (control=='s' || control=='S'))
    {
        printf("\n Ingrese el IDServicio requerido: ");
        scanf("%i", auxServi.IdServicio);





    }
    return servicio;
}

stCliente devolverCliente (char Archivo[], long int DNI)
{
    int flag=0;
    stCliente aux;
    stCliente valido;
    FILE *buffer= fopen(Archivo, "rb");

    if(buffer == NULL)
    {
        printf("\nNo pudo abrirse el archivo");
    }
    else
    {
        while((fread(&aux, sizeof(stCliente), 1, buffer) > 0)&& flag==0)
        {
            if(DNI == aux.DNI)
            {
                valido=aux;
                flag=1;
            }
        }

    fclose(buffer);
    }
    return valido;
}

void cargarUnTurno (char archivoTurno[], char archivoCliente[])
{
    stTutno turno;
    int QArchi;
    stCliente auxCte;
    stFecha auxFecha;
    FILE*bufferTurno = fopen(nombreA, "r+b");
    if  (bufferTurno==NULL)
    {
        printf("El archivo no pudo abrirse");
    }
    else
    {
        fseek(buffer,0,2);
        QArchi = ftell(buffer)/sizeof(stTutno);
        turno.IdTurno = QArchi + 1;
        printf("\n Ingrese el DNI del Cliente: ");
        scanf("%i", &turno.DNICliente);
        FILE*bufferCliente=fopen(nombreArchiCliente, "rb"); /// Se carga el IDCte sin pedirlo al USU.
        if (bufferCliente==NULL)
        {
            printf("El archivo de clientes no pudo abrirse");
        }
        else
        {
            turno.IdCliente=0;
            while (fread((&auxCte),sizeof(stCliente),1,bufferCliente)>0 && turno.IdCliente==0)
            {
                if (auxCte.DNI==turno.DNICliente)
                {
                    turno.IdCliente=auxCte.IdCliente;
                }
            }
            fclose(bufferCliente);
        }
        if (turno.IdCliente!=0)
        {
            turno.fechaTurno = cargarFecha();
            MostrarServicios(archivoServicios);

        }


        fclose(bufferTurno);
    }


}
