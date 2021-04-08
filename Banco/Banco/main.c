#include <stdio.h>

#include <stdlib.h>

#include <curses.h>

#include<string.h>

#include <math.h>

#include <stdbool.h>

#define MAX 5

    
int monto_total_depositos, monto_total_retiros = 0;
bool active = false;
int cb50, cb20, cb10, cb5, cb2, cb1, contador_usuarios, op2, i, fondos, cantidad_depositos, cantidad_retiros, monto_total_retiros, result;

int denominaciones[6] = {
  50000,
  20000,
  10000,
  5000,
  2000,
  1000
};

int cantidad_billetes[6];

struct Usuario {
  char nombre[20];
  int numero_cuenta;
  int fondos;
};

struct Usuario arr_usuario[MAX];

//funciones administrador
void llenarCajero(void) {
  while (active == false) {
    printf("Llene unicamente 10 billetes de 50 mil colones: ");
    scanf("%d", & cb50);
    cantidad_billetes[0] = cb50;

    printf("Llene unicamente 25 billetes de 20 mil colones: ");
    scanf("%d", & cb20);
    cantidad_billetes[1] = cb20;

    printf("Llene unicamente entre 40 y 50 billetes de 10 mil colones: ");
    scanf("%d", & cb10);
    cantidad_billetes[2] = cb10;

    printf("Llene unicamente entre 50 y 100 billetes de 5 mil colones: ");
    scanf("%d", & cb5);
    cantidad_billetes[3] = cb5;

    printf("Llene unicamente 100 billetes de 2 mil colones: ");
    scanf("%d", & cb2);
    cantidad_billetes[4] = cb2;

    printf("Llene unicamente 100 billetes de mil colones: ");
    scanf("%d", & cb1);
    cantidad_billetes[5] = cb1;

    if (cb50 == 10 && cb20 == 25 && (cb10 >= 40 && cb10 <= 50) && (cb5 >= 50 && cb5 <= 100) && cb2 == 100 && cb1 == 100) {
      printf("\n********************************\n");
      printf("BILLETES RELLENADOS CON EXITO");
      printf("\n********************************\n");
      active = true;
    } else {
      printf("\n//////////////////////////////////////////////////\n");
      printf("ERROR AL RELLENAR LOS BILLETES. INTENTELO DE NUEVO");
      printf("\n//////////////////////////////////////////////////\n");
    }
  }
  printf("\n ANTERIORMENTE SE LLENO EL BANCO \n");
}

void agregarUsuarios(void) {
  bool validated = false;
  while (contador_usuarios < MAX) {
    for (i = 0; i < MAX; i++) {
      printf("\n Clientes Agregados: %d\n\n", i + 1);
      printf("Nombre: ");
      scanf("%s", arr_usuario[i].nombre);
      printf("Numero de Cuenta: ");
      scanf("%d", & arr_usuario[i].numero_cuenta);
      do {
        printf("Ingrese los fondos iniciales para la cuenta: ");
        scanf("%d", & fondos);
        if (fondos >= 30000 && fondos <= 250000) {
          arr_usuario[i].fondos = fondos;
          validated = true;
          contador_usuarios++;
          printf("\n********************************\n");
          printf("CLIENTES AGREGADOS CON EXITO");
          printf("\n********************************\n");
        } else {
          printf("\n//////////////////////////////////////////////////\n");
          printf("VUELVA A INGRESAS LOS FONDOS EN UN RANGO DE 30000 Y 250000");
          printf("\n//////////////////////////////////////////////////\n");
        }
      } while (validated == false);
    }
  }
}

void esperar(void) {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
  printf("\n Presione ENTER para continuar \n");
  while ((ch = getchar()) != '\n' && ch != EOF);
}

//funciones de reportes
void reporteBilletes(void) {
  int cant_billetes[6] = {
    cb50,
    cb20,
    cb10,
    cb5,
    cb2,
    cb1
  };
  printf("REPORTE DE BILLETES \n");
  for (i = 0; i <= 5; i++) {
    printf("La cantidad de billetes de %d colones son %d  \n", denominaciones[i], cant_billetes[i]);
  }
}

void reporteUsuarios(void) {
  printf("\n");
  printf("Nombre\tN.Cuenta\tFondos Disponibles\n");
  for (i = 0; i < MAX; i++) {
    printf("%s \t %d  \t\t\t %d  \n",
      arr_usuario[i].nombre, arr_usuario[i].numero_cuenta, arr_usuario[i].fondos);
  }
}

void reporteTotales(void) {
  printf("Cantidad de Retiros: %d \n", cantidad_retiros);
  printf("Cantidad de Depositos: %d \n", cantidad_depositos);
  printf("Promedio de Retiros: %lf\n", round((double) cantidad_retiros / monto_total_retiros));
  printf("Promedio de Depositos: %lf\n", round((double) cantidad_depositos / monto_total_depositos));
  printf("Monto total por Depositos: %d \n", monto_total_depositos);
  printf("Monto total por Retiros: %d", monto_total_retiros);
}

// funciones de transacciones

int capitalCajero() {
  for (i = 0; i < 6; i++) {
    result += cantidad_billetes[i] * denominaciones[i];
  }
  return result;
}

void retiros_depositos(int accion) {
  int cuenta_digitada, verificado, monto_retiro, res, d50, d20, d10, d5, d2, d1, j;
  int monto_deposito = 0;
  int dinero_cajero = capitalCajero();
  switch (accion) {
    //retiros
  case 1:
    printf("Digite el numero de cuenta para realizar el retiro: ");
    scanf("%d", & cuenta_digitada);
    for (i = 0; i < MAX; i++) {
      if (cuenta_digitada == arr_usuario[i].numero_cuenta) {
        int fondos_usuario = arr_usuario[i].fondos;
        printf("\n--------------------------------------------\n");
        printf("Fondos disponibles en la cuenta: %d", arr_usuario[i].fondos);
        printf("\n--------------------------------------------\n");
        printf("Digite el monto a retirar: ");
        scanf("%d", & monto_retiro);
        if (monto_retiro > dinero_cajero) {
          printf("\n//////////////////////////////////////////////////\n");
          printf("EL CAJERO NO DISPONE DE ESA CANTIDAD DE DINERO");
          printf("\n//////////////////////////////////////////////////\n");
        } else if (monto_retiro > fondos_usuario) {
          printf("\n//////////////////////////////////////////////////\n");
          printf("USTED NO CUENTA CON SUFICIENTES FONDOS PARA REALIZAR EL RETIRO");
          printf("\n//////////////////////////////////////////////////\n");
        } else {
          int cant_billetes;
          monto_total_retiros += monto_retiro;
          arr_usuario[i].fondos = arr_usuario[i].fondos - monto_retiro;
          for (j = 0; j < 6; j++) {
            cant_billetes = floor(monto_retiro / denominaciones[j]);
            res = monto_retiro % denominaciones[j];
            monto_retiro = res;
              printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            if (cant_billetes != 0) {
              printf("Cantidad de billetes de %d mil: %d \n", denominaciones[j], cant_billetes);
            }
              printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
          }
          cantidad_retiros++;
          printf("\n********************************\n");
          printf("RETIRO REALIZADO CON EXITO");
          printf("\n--------------------------------------------\n");
          printf("Fondos disponibles en la cuenta: %d", arr_usuario[i].fondos);
          printf("\n********************************\n");

        }
      } else {
        printf("\n//////////////////////////////////////////////////\n");
        printf("ESA CUENTA NO EXISTE. POR FAVOR INTENTE CON UNA CUENTA EXISTENTE");
        printf("\n//////////////////////////////////////////////////\n");
      }
    }
    break;

    //depositos
  case 2:
    printf("\n Digite el numero de cuenta para realizar el deposito: ");
    scanf("%d", & cuenta_digitada);
    for (i = 0; i < MAX; i++) {
      if (cuenta_digitada == arr_usuario[i].numero_cuenta) {
        printf("\n--------------------------------------------\n");
        printf("Fondos disponibles en la cuenta: %d", arr_usuario[i].fondos);
        printf("\n--------------------------------------------\n");
        do {
          printf("\nIndique la cantidad de billetes de 50 mil colones para ingresar: ");
          scanf("%d", & d50);
          printf("\nIndique la cantidad de billetes de 20 mil colones para ingresar: ");
          scanf("%d", & d20);
          printf("\nIndique la cantidad de billetes de 10 mil colones para ingresar: ");
          scanf("%d", & d10);
          printf("\nIndique la cantidad de billetes de 5 mil colones para ingresar: ");
          scanf("%d", & d5);
          printf("\nIndique la cantidad de billetes de 2 mil colones para ingresar: ");
          scanf("%d", & d2);
          printf("\nIndique la cantidad de billetes de  mil colones para ingresar:");
          scanf("%d", & d1);

          int cant_billetes_depositados[6] = {
            d50,
            d20,
            d10,
            d5,
            d2,
            d1
          };

          monto_deposito = 0;
          for (j = 0; j < 6; j++) {
            monto_deposito += cant_billetes_depositados[j] * denominaciones[j];
          }

          printf("\n --------------------------------------------------------\n");
          printf("EL MONTO TOTAL A DEPOSITAR ES: %d \n", monto_deposito);
          printf("Digite (1) para continuar o (0) para vover a intenarlo: ");
          printf("\n -------------------------------------------------------- \n");
          scanf("%d", & verificado);
          if (verificado == 1) {
            //añadiendo las denominaciones depositadas
            cb50 += d50;
            cb20 += d20;
            cb10 += d10;
            cb5 += d5;
            cb2 += d2;
            cb1 += d1;

            //agregando los fondos a la cuenta
            arr_usuario[i].fondos += monto_deposito;
            cantidad_depositos++;
            monto_total_depositos += monto_deposito;
            verificado = 1;
            printf("\n********************************\n");
            printf("DEPOSITO REALIZADO CON EXITO");
            printf("\n--------------------------------------------\n");
            printf("Fondos disponibles en la cuenta: %d", arr_usuario[i].fondos);
            printf("\n********************************\n");
          }
        } while (verificado != 1);
      } else {
        printf("\n//////////////////////////////////////////////////\n");
        printf("ESA CUENTA NO EXISTE. POR FAVOR INTENTE CON UNA CUENTA EXISTENTE");
        printf("\n//////////////////////////////////////////////////\n");
      }
    }
    break;
  default:
    break;
  }
}

int main() {
  int op;
  do {
    menu_principal:
    system("cls");
    printf("Cajero automatico \n");
    printf("1. Administracion \n");
    printf("2. Trasacciones\n");
    printf("3. Salir\n");
    scanf("%d", & op);
    switch (op) {
    case 1:
      do {
        administracion:
        system("cls");
        printf("Cajero automatico (Administracion) \n");
        printf("1. Llenar Cajero \n");
        printf("2. Agregar clientes \n");
        printf("3. Reportes \n");
        printf("4. Menu Principal \n");
        scanf("%d", & op);
        switch (op) {
        case 1:
          system("cls");
          llenarCajero();
          esperar();
          break;
        case 2:
          system("cls");
          if (contador_usuarios < MAX) {
            agregarUsuarios();
            esperar();
            break;
          } else {
            system("cls");
            printf("NO SE PUEDEN INGRESAR MAS USUARIOS. LIMITE EXCEDIDO\n ");
            esperar();
            break;
          }
          case 3:
            do {
              system("cls");
              printf("Reportes \n");
              printf("1. Detalle Billetes \n");
              printf("2. Detalle Clientes \n");
              printf("3. Totales \n");
              printf("4. Regresar al Menu Anterior \n");
              scanf("%d", & op);
              switch (op) {
              case 1:
                system("cls");
                reporteBilletes();
                printf("El dinero total del cajero es: %d \n", capitalCajero());
                esperar();
                break;
              case 2:
                system("cls");
                reporteUsuarios();
                esperar();
                break;
              case 3:
                system("cls");
                reporteTotales();
                esperar();
                break;
              default:
                goto administracion;
                break;
              }
            } while (op != 4);
          default:
            goto menu_principal;
            break;
        }
      } while (op != 4);
    case 2:
      do {
        system("cls");
        printf(" CAJERO AUTOMÁTICO (TRANSACCIONES) \n");
        printf("1. Retiros \n");
        printf("2. Deposito \n");
        printf("3. Menu Principal \n");
        scanf("%d", & op2);
        switch (op2) {
        case 1:
          system("cls");
          retiros_depositos(1);
          esperar();
          break;
        case 2:
          system("cls");
          retiros_depositos(2);
          esperar();
          break;
        default:
          goto menu_principal;
          break;
        }
      } while (op2 != 3);
    default:
      goto menu_principal;
      break;
    }

  } while (op != 3);
  return 0;
}

