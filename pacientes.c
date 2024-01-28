#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACIENTES 100

struct Historia_clinica
{
    char nombre[80];
    char apellido[80];
    char direccion[100];
    int edad;
    char sexo;
    float peso;
    float altura;
    float imc;
    float presion;
    float frecuencia_cardiaca;
};

// Función para validar que la entrada sea 'M' o 'F'
int validarSexo(char sexo) {
    return (sexo == 'M' || sexo == 'F');
}

int main()
{
    struct Historia_clinica pacientes[MAX_PACIENTES];
    int total_pacientes = 0;
    int opcion;

    do
    {
        printf("1. Ingresar datos del paciente\n");
        printf("2. Ver datos de todos los pacientes\n");
        printf("3. Salir\n");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
            case 1:
                if (total_pacientes < MAX_PACIENTES) {
                    printf("Ingrese el nombre del paciente: ");
                    fgets(pacientes[total_pacientes].nombre, sizeof(pacientes[total_pacientes].nombre), stdin);
                    pacientes[total_pacientes].nombre[strcspn(pacientes[total_pacientes].nombre, "\n")] = '\0';

                    printf("Ingrese el apellido del paciente: ");
                    fgets(pacientes[total_pacientes].apellido, sizeof(pacientes[total_pacientes].apellido), stdin);
                    pacientes[total_pacientes].apellido[strcspn(pacientes[total_pacientes].apellido, "\n")] = '\0';

                    printf("Ingrese la dirección del paciente: ");
                    fgets(pacientes[total_pacientes].direccion, sizeof(pacientes[total_pacientes].direccion), stdin);
                    pacientes[total_pacientes].direccion[strcspn(pacientes[total_pacientes].direccion, "\n")] = '\0';

                    do {
                        printf("Ingrese la edad del paciente: ");
                        scanf("%d", &pacientes[total_pacientes].edad);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].edad <= 0);

                    do {
                        printf("Ingrese el sexo del paciente (M/F): ");
                        scanf(" %c", &pacientes[total_pacientes].sexo);
                        fflush(stdin);
                    } while (!validarSexo(pacientes[total_pacientes].sexo));

                    do {
                        printf("Ingrese el peso del paciente (kg): ");
                        scanf("%f", &pacientes[total_pacientes].peso);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].peso <= 0);

                    do {
                        printf("Ingrese la altura del paciente (metros): ");
                        scanf("%f", &pacientes[total_pacientes].altura);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].altura <= 0);

                    pacientes[total_pacientes].imc = pacientes[total_pacientes].peso / (pacientes[total_pacientes].altura * pacientes[total_pacientes].altura);

                    do {
                        printf("Ingrese la presion del paciente: ");
                        scanf("%f", &pacientes[total_pacientes].presion);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].presion <= 0);

                    do {
                        printf("Ingrese la frecuencia cardiaca del paciente: ");
                        scanf("%f", &pacientes[total_pacientes].frecuencia_cardiaca);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].frecuencia_cardiaca <= 0);

                    // Sección para escribir en el archivo
                    char archivo[] = "Historia_clinica.txt";
                    FILE *historia;

                    historia = fopen(archivo, "a");
                    if (historia == NULL)
                    {
                        printf("Error al abrir o crear el archivo\n");
                        return 1;
                    }

                    fseek(historia, 0, SEEK_END);
                    if (ftell(historia) == 0)
                    {
                        // Encabezado del archivo
                        fprintf(historia, "Nombre\tApellido\tEdad\tSexo\t\t\tDirección\t\t\t\tPeso (kg)\t\tAltura (metros)\t\tPresion\t\tFrecuencia cardiaca\t\tIMC\n");
                    }

                    // Escribir datos del paciente en el archivo
                    fprintf(historia, "%s \t%s\t%d\t\t%c\t\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t\t\t\t%.2f\n",
                            pacientes[total_pacientes].nombre, pacientes[total_pacientes].apellido, pacientes[total_pacientes].edad,
                            pacientes[total_pacientes].sexo, pacientes[total_pacientes].direccion, pacientes[total_pacientes].peso,
                            pacientes[total_pacientes].altura, pacientes[total_pacientes].presion, pacientes[total_pacientes].frecuencia_cardiaca,
                            pacientes[total_pacientes].imc);

                    fclose(historia);
                    // Fin de la sección para escribir en el archivo

                    total_pacientes++;
                } else {
                    printf("Se ha alcanzado el límite de pacientes. No se pueden ingresar más.\n");
                }
                break;

            case 2:
                printf("\n--- Datos de todos los pacientes ---\n");
                for (int i = 0; i < total_pacientes; i++) {
                    printf("Paciente %d:\n", i + 1);
                    printf("Nombre: %s %s\n", pacientes[i].nombre, pacientes[i].apellido);
                    printf("Edad: %d\n", pacientes[i].edad);
                    printf("Sexo: %c\n", pacientes[i].sexo);
                    printf("Dirección: %s\n", pacientes[i].direccion);
                    printf("Peso: %.2f kg\n", pacientes[i].peso);
                    printf("Altura: %.2f metros\n", pacientes[i].altura);
                    printf("Presion: %.2f\n", pacientes[i].presion);
                    printf("Frecuencia Cardiaca: %.2f\n", pacientes[i].frecuencia_cardiaca);
                    printf("IMC: %.2f\n", pacientes[i].imc);
                    printf("-----------------------------\n");
                }
                break;

            case 3:
                printf("Gracias por usar el programa.\n");
                break;

            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}

