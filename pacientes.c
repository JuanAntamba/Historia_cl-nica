#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Historia_clinica
{
    float peso;
    float altura;
    float imc;
    char nombre[80];
    char apellido[80];
    int edad;
    char sexo[10];
    float presion;
    float frecuencia_cardiaca;
};

int main()
{
    struct Historia_clinica paciente;
    int opcion;
        do
        {
            printf("1. Ingresar datos del paciente\n");
            printf("2. Salir\n");
            scanf("%d", &opcion);
            fflush(stdin);
            switch (opcion)
            {
                case 1:
                    printf("Ingrese el nombre del paciente: ");
                    fgets(paciente.nombre, sizeof(paciente.nombre), stdin);
                    paciente.nombre[strcspn(paciente.nombre, "\n")] = '\0';
                    printf("Ingrese el apellido del paciente: ");
                    fgets(paciente.apellido, sizeof(paciente.apellido), stdin);
                    paciente.apellido[strcspn(paciente.apellido, "\n")] = '\0';
                    printf("Ingrese la edad del paciente: ");
                    scanf("%d", &paciente.edad);
                    fflush(stdin);
                    printf("Ingrese el sexo del paciente: ");
                    fgets(paciente.sexo, sizeof(paciente.sexo), stdin);
                    printf("Ingrese el peso del paciente: ");
                    scanf("%f", &paciente.peso);
                    fflush(stdin);
                    printf("Ingrese la altura del paciente: ");
                    scanf("%f", &paciente.altura);
                    fflush(stdin);
                    paciente.imc = paciente.peso / (paciente.altura * paciente.altura);
                    printf("Ingrese la presion del paciente: ");
                    scanf("%d", &paciente.presion);
                    fflush(stdin);
                    printf("Ingrese la frecuencia cardiaca del paciente: ");
                    scanf("%d", &paciente.frecuencia_cardiaca);
                    fflush(stdin);
                    break;
                case 2:
                    printf("Gracias por usar el programa\n");
                    break;
                default:
                    printf("Opcion no valida\n");
                    break;
            }
        } while (opcion != 2);

    char archivo[] = "Historia_clinica.txt";
    FILE *historia;

    historia = fopen(archivo, "a");
    if (historia == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }
    
    fseek(historia, 0, SEEK_END);
    if (ftell(historia) == 0)
    {
        fprintf(historia, "Nombre\tApellido\tEdad\tSexo\t\t\tPeso\t\tAltura\t\tPresion\t\tFrecuencia cardiaca\t\tIMC\n");
    }

    fprintf(historia, "%s \t%s\t%d\t\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t\t\t\t%.2f\n", paciente.nombre, paciente.apellido, paciente.edad, paciente.sexo, paciente.peso, paciente.altura, paciente.presion, paciente.frecuencia_cardiaca, paciente.imc);
    fclose(historia);
    return 0;
}
