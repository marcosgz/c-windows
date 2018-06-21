#include <stdio.h>

void gotoMenu(int option) {
  int contactID;
  switch(option) {
    case 1:
      addContact();
      break;
    case 2:
      contactID = askContactID();
      // showContactByID(contactID); ## Define this function
      break;
    case 3:
      listContacts();
      break;
    case 4:
      searchContacts();
      break;
    case 5:
      contactID = askContactID();
      // removeContactByID(contactID) ## define this function
      break;
    case 6:
      deleteDB();
      break;
    default:
      break;
  }
}

int userMenuOption() {
  int option = -1;
  printf("\n> ");
  scanf("%d", &option);

  if (option > 7 || option < 1) {
    printf("Opcao nao e valida. Precisa ser um numero de 1 a 6\n");
  }

  return option;
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
