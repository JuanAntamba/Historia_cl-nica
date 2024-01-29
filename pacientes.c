#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion del numero maximo de pacientes
#define MAX_PACIENTES 100

// Estructura que representa la historia clinica de un paciente
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

int validarSexo(char sexo) {
    return (sexo == 'M' || sexo == 'F');
}

// Funcion principal del programa
int main()
{
    // Declaracion del arreglo de estructuras para almacenar la informacion de los pacientes
    struct Historia_clinica pacientes[MAX_PACIENTES];
    int total_pacientes = 0;

    // Variable para la seleccion de opciones del menu
    int opcion;

    // Bucle principal del programa
    do
    {
        // Menu principal
        printf("1. Ingresar datos del paciente\n");
        printf("2. Ver datos de todos los pacientes\n");
        printf("3. Salir\n");

        // Lectura de la opcion seleccionada por el usuario
        scanf("%d", &opcion);
        fflush(stdin);

        // Evaluacion de la opcion seleccionada
        switch (opcion)
        {
            case 1:
                // Ingresar datos del paciente
                if (total_pacientes < MAX_PACIENTES) {
                    // Captura del nombre del paciente
                    printf("Ingrese el nombre del paciente: ");
                    fgets(pacientes[total_pacientes].nombre, sizeof(pacientes[total_pacientes].nombre), stdin);
                    
                    // Eliminacion del salto de linea al final del nombre
                    pacientes[total_pacientes].nombre[strcspn(pacientes[total_pacientes].nombre, "\n")] = '\0';

                    // Captura del apellido del paciente
                    printf("Ingrese el apellido del paciente: ");
                    fgets(pacientes[total_pacientes].apellido, sizeof(pacientes[total_pacientes].apellido), stdin);
                    
                    // Eliminacion del salto de linea al final del apellido
                    pacientes[total_pacientes].apellido[strcspn(pacientes[total_pacientes].apellido, "\n")] = '\0';

                    // Captura de la direccion del paciente
                    printf("Ingrese la direccion del paciente: ");
                    fgets(pacientes[total_pacientes].direccion, sizeof(pacientes[total_pacientes].direccion), stdin);
                    
                    // Eliminacion del salto de linea al final de la direccion
                    pacientes[total_pacientes].direccion[strcspn(pacientes[total_pacientes].direccion, "\n")] = '\0';

                    // Captura de la edad del paciente con validacion
                    do {
                        printf("Ingrese la edad del paciente: ");
                        scanf("%d", &pacientes[total_pacientes].edad);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].edad <= 0);

                    // Captura del sexo del paciente con validacion
                    do {
                        printf("Ingrese el sexo del paciente (M/F): ");
                        scanf(" %c", &pacientes[total_pacientes].sexo);
                        fflush(stdin);
                    } while (!validarSexo(pacientes[total_pacientes].sexo));

                    // Captura del peso del paciente con validacion
                    do {
                        printf("Ingrese el peso del paciente (kg): ");
                        scanf("%f", &pacientes[total_pacientes].peso);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].peso <= 0);

                    // Captura de la altura del paciente con validacion
                    do {
                        printf("Ingrese la altura del paciente (metros): ");
                        scanf("%f", &pacientes[total_pacientes].altura);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].altura <= 0);

                    // Calculo del indice de masa corporal  del paciente
                    pacientes[total_pacientes].imc = pacientes[total_pacientes].peso / (pacientes[total_pacientes].altura * pacientes[total_pacientes].altura);

                    // Captura de la presion del paciente con validacion
                    do {
                        printf("Ingrese la presion del paciente: ");
                        scanf("%f", &pacientes[total_pacientes].presion);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].presion <= 0);

                    // Captura de la frecuencia cardiaca del paciente con validacion
                    do {
                        printf("Ingrese la frecuencia cardiaca del paciente: ");
                        scanf("%f", &pacientes[total_pacientes].frecuencia_cardiaca);
                        fflush(stdin);
                    } while (pacientes[total_pacientes].frecuencia_cardiaca <= 0);

                    // Seccion para escribir en el archivo
                    char archivo[] = "Historia_clinica.txt";
                    FILE *historia;

                    // Apertura del archivo en modo "a" (agregar al final)
                    historia = fopen(archivo, "a");
                    
                    // Verificacion de errores al abrir o crear el archivo
                    if (historia == NULL)
                    {
                        printf("Error al abrir o crear el archivo\n");
                        return 1;
                    }

                    // Posicionamiento al final del archivo y escritura del encabezado si es necesario
                    fseek(historia, 0, SEEK_END);
                    if (ftell(historia) == 0)
                    {
                        fprintf(historia, "Nombre\tApellido\tEdad\tSexo\t\t\tDireccion\t\t\t\tPeso (kg)\t\tAltura (metros)\t\tPresion\t\tFrecuencia cardiaca\t\tIMC\n");
                    }

                    // Escritura de los datos del paciente en el archivo
                    fprintf(historia, "%s \t%s\t%d\t\t%c\t\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t\t\t\t%.2f\n",
                            pacientes[total_pacientes].nombre, pacientes[total_pacientes].apellido, pacientes[total_pacientes].edad,
                            pacientes[total_pacientes].sexo, pacientes[total_pacientes].direccion, pacientes[total_pacientes].peso,
                            pacientes[total_pacientes].altura, pacientes[total_pacientes].presion, pacientes[total_pacientes].frecuencia_cardiaca,
                            pacientes[total_pacientes].imc);

                    // Cierre del archivo
                    fclose(historia);

                    // Incremento del contador de pacientes
                    total_pacientes++;
                } else {
                    // Mensaje de error cuando se alcanza el limite de pacientes
                    printf("Se ha alcanzado el limite de pacientes. No se pueden ingresar mas.\n");
                }
                break;

            case 2:
                // Ver datos de todos los pacientes
                printf("\n--- Datos de todos los pacientes ---\n");
                for (int i = 0; i < total_pacientes; i++) {
                    printf("Paciente %d:\n", i + 1);
                    printf("Nombre: %s %s\n", pacientes[i].nombre, pacientes[i].apellido);
                    printf("Edad: %d\n", pacientes[i].edad);
                    printf("Sexo: %c\n", pacientes[i].sexo);
                    printf("Direccion: %s\n", pacientes[i].direccion);
                    printf("Peso: %.2f kg\n", pacientes[i].peso);
                    printf("Altura: %.2f metros\n", pacientes[i].altura);
                    printf("Presion: %.2f\n", pacientes[i].presion);
                    printf("Frecuencia Cardiaca: %.2f\n", pacientes[i].frecuencia_cardiaca);
                    printf("IMC: %.2f\n", pacientes[i].imc);
                    printf("-----------------------------\n");
                }
                break;

            case 3:
                // Salir del programa
                printf("Gracias por usar el programa.\n");
                break;

            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}

