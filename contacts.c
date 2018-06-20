#include <stdio.h>
#include "contacts.h"
#include "menu.c"
#include "crud.c"

// Main Function
int main(void) {
  do {
    showMenu();
  } while(userMenuOption() != EXIT_CODE);
}
