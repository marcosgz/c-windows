#include <stdio.h>
#include "contacts.h"

#define OPTIONS_LENGHT 6

int userMenuOption() {
  int option = -1;
  printf("\n> ");
  scanf("%d", &option);

  if (option > 6 || option < 1) {
    printf("Opcao nao e valida. Precisa ser um numero de 1 a 6\n");
  }

  return option;
}

// Print a simple menu with all options available to the user
void showMenu() {
  char options[OPTIONS_LENGHT][50];
  sprintf(options[0], "[1] Cadastrar Contato");
  sprintf(options[1], "[2] Listar contatos");
  sprintf(options[2], "[3] Procurar contato");
  sprintf(options[3], "[4] Eliminar contato");
  sprintf(options[4], "[5] Eliminar banco de dados");
  sprintf(options[5], "[6] Sair do sistema");

  int i;
  for(i=0; i < OPTIONS_LENGHT; i ++) {
    printf("%s\n", options[i]);
  }
}

// Global Variables
typedef struct contact {
  char name[50];
  char address[100];
  char phoneArea[3];
  char phone[13];
  char email[30];
  char details[255];
}Contact;

// Main Function
int main(void) {
  do {
    showMenu();
  } while(userMenuOption() != 6);
}
