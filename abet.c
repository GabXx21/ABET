#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define FILAS 25
#define COLUMNAS 2
#define USUARIO "user"
#define CONTRASENA "password"


int menu();
void ingresarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void eliminarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void editarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void mostrarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void calcularVentas(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);

int validar_credenciales(char *nombre_usuario, char *contraseña);
int iniciar_sesion(char *nombre_usuario, char *contraseña);

int menuprincipal();

int leerEntero(char *);
int leerEnteroPositivo(char *);
int leerEnteroEntre(char *, int, int);

float leerFlotante(char *);
float leerFlotantePositivo(char *);
float leerFlotanteEntre(char *, float, float);

char leerCaracter(char *);

int main(void) {
  int opc, filas;
  int cantidad[FILAS];
  float precio[FILAS];
  char producto[FILAS][COLUMNAS];
  char nombre_usuario[100];
  char contraseña[100];
  int intentos = 0;
  int respuesta;

   while (intentos < 3) {
      printf("Intento %d\n", intentos + 1);

      printf("Ingrese su nombre de usuario: ");
      fgets(nombre_usuario, sizeof(nombre_usuario), stdin);
      nombre_usuario[strcspn(nombre_usuario, "\n")] = 0;

      printf("Ingrese su contraseña: ");
      fgets(contraseña, sizeof(contraseña), stdin);
      contraseña[strcspn(contraseña, "\n")] = 0;

      respuesta = validar_credenciales(nombre_usuario, contraseña);

      if (respuesta == 1) {
        printf("Inicio de sesión exitoso.\n");
        break;
      } else {
        printf("Error en el inicio de sesión. Intentos restantes: %d\n",
               3 - intentos - 1);
        intentos++;
      }
   }

   if (intentos == 3) {
      printf("Ha superado el número de intentos permitidos.\n");
      exit(0);
   }
  
  do {
    opc = menuprincipal();
    switch (opc) {
    case 1:
      printf("1.- Ingresar producto\n");
      do {
        printf("Ingrese cuantos producto va ingresar: ");
        scanf("%d", &filas);
        if (filas > FILAS) {
          printf("El numero de productos es mayor a los disponibles\n");
          printf("Ingrese otro numero\n");
        } else if (filas < 0) {
          printf("No se acpeta numeros negativos\n");
          printf("Ingrese otro numero\n");
        }
      } while (filas > FILAS || filas < 0);
        ingresarProductos(producto, cantidad, precio, filas);
      break;
    case 2:
      printf("2.- Mostrar productos\n");
      mostrarProductos(producto, cantidad, precio, filas);
      break;
    case 3:
      printf("3.- Informe rapido.\n");
      calcularVentas(producto, cantidad, precio, filas);
      break;
    case 4:
      printf("4.- Modificar producto\n");
      editarProductos(producto, cantidad, precio, filas);
      break;
    case 5:
      printf("5.- Eliminar producto\n");
      eliminarProductos(producto, cantidad, precio, filas);
      break;
    case 6:
      printf("Gracias por usar \n");
      break;
    default:
      printf("Opcion no valida");
      break;
    }
  } while (opc != 6);
  return 0;
}


void ingresarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  char nombre[filas][50];
  for(int i=0; i<filas; i++){
    do {
        printf("Ingrese el nombre del producto %d: \n", i + 1);
        scanf("%s", nombre[i]);
        strcpy(productos[i], nombre[i]);
    } while (!isalpha(nombre[i][0]));

    do {
        printf("Ingrese la cantidad del producto %d: \n", i + 1);
        scanf("%d", &cantidad[i]);
    } while (cantidad[i] <= 0);

    do {
        printf("Ingrese el precio del producto %d: \n", i + 1);
        scanf("%f", &precio[i]);
    } while (precio[i] <= 0);
  }
}

void eliminarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  char eliminar[50];
  printf("Ingrese el nombre del producto a eliminar: ");
  scanf("%s", eliminar);
  for(int i=0; i<filas; i++){
    if(strcmp(eliminar, productos[i])==0){
      productos[i][0] = '\0';
      precio[i] = '\0';
      cantidad[i] = '\0';
      printf("El producto %s fue eliminado.\n", eliminar);
      break;
    }
  }
}

void editarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  char editar[50];
  printf("Ingrese el nombre del producto a editar: ");
  scanf("%s", editar);
  for(int i=0; i<filas; i++){
    if(strcmp(editar, productos[i])==0){
      printf("Producto encontrado.\n");
      printf("Ingrese la cantidad del producto %d: \n", i+1);
      scanf("%d", &cantidad[i]);
      printf("Ingrese el precio del producto %d: \n", i+1);
      scanf("%f", &precio[i]);
      printf("Producto editado.\n");
    }
  }
}

void mostrarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  printf("Producto\tCantidad\tPrecio\n");
  for(int i=0; i<filas; i++){
      printf("%s\t\t%d\t\t\t%.2f\n", productos[i], cantidad[i], precio[i]);
  }
  printf("\n");
}

void calcularVentas(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  int ventas[filas];
  float ventasTotales = 0;
  for(int i=0; i<filas; i++){
    ventas[i] = cantidad[i] * precio[i];
    ventasTotales += ventas[i];
    printf("Del producto '%s' se tiene %d unidades a un precio de %.2f.\n", productos[i], cantidad[i], precio[i]);
  }
  printf("Se espera una ganacia total de: %.2f.\n", ventasTotales);
}

int validar_credenciales(char *nombre_usuario, char *contraseña) {
 if (strcmp(nombre_usuario, USUARIO) != 0 ||
      strcmp(contraseña, CONTRASENA) != 0) {
    printf("Error: El nombre de usuario o la contraseña equivocada.\n");
    return 0;
 } else {
    return 1;
 }
}

int iniciar_sesion(char *nombre_usuario, char *contraseña) {
 return validar_credenciales(nombre_usuario, contraseña);
}

int menuprincipal (){
  printf("1.- Ingresar producto\n");
  printf("2.-  Mostrar productos\n");
  printf("3.- Informe rapido.\n");
  printf("4.- Modificar producto\n");
  printf("5.-  Eliminar producto\n");
  printf("6.- Salir\n");
  return leerEnteroEntre("Escoga una opcion\n", 1, 6);

}

int leerEntero(char* mensaje){
  int valor;

    printf("%s",mensaje);
    scanf("%d",&valor);

  return valor;

}
int leerEnteroPositivo(char* mensaje){
  int valor;
  do{
     printf("%s",mensaje);
      scanf("%d",&valor);

  }while(valor<=0);
  return valor;

}

int leerEnteroEntre(char* mensaje, int min, int max){
  int valor;
  do{
    printf("%s", mensaje);
    scanf ("%d", &valor);
  }while (valor < min || valor > max);
  return valor;
}

float leerFlotantePositivo(char* mensaje){
  float valor;
  do{
    printf("%s",mensaje);
    scanf("%f",&valor);

  }while(valor<=0);
  return valor;
}

float leerFlotante(char* mensaje){
  float valor;

  printf("%s",mensaje);
    scanf("%f",&valor);
  return valor;

}

float leerFlotanteEntre(char* mensaje, float minimo, float maximo){
  int valor;
  do{
     printf("%s",mensaje);
      scanf("%d",&valor);

  }while(valor < minimo || valor > maximo);
  return valor;
}	

char leerCaracter (char* mensaje){
  char valor;
  printf("%s",mensaje);
  return valor;
}