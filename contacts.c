#include <stdio.h>
#include "contacts.h"

int userMenuOption() {
  int option = -1;
  printf("\n> ");
  scanf("%d", &option);

  if (option > 7 || option < 1) {
    printf("Opcao nao e valida. Precisa ser um numero de 1 a 6\n");
  }

  return option;
}

Contact addContact() {
  Contact contact;
  return contact;
}

void removeContact(Contact* contact) {

}

void showContact(int id) {

}

// Print a simple menu with all options available to the user
void showMenu() {
  int len = 7;
  char options[len][50];
  sprintf(options[0], "[1] Cadastrar novo contato");
  sprintf(options[1], "[2] Exibir contato");
  sprintf(options[2], "[3] Listar todos contatos");
  sprintf(options[3], "[4] Procurar contato");
  sprintf(options[4], "[5] Apagar contato");
  sprintf(options[5], "[6] Eliminar banco de dados");
  sprintf(options[6], "[%d] Sair do sistema", EXIT_CODE);

  int i;
  for(i=0; i < len; i ++) {
    printf("%s\n", options[i]);
  }
}

// Main Function
int main(void) {
  do {
    showMenu();
  } while(userMenuOption() != EXIT_CODE);
}
