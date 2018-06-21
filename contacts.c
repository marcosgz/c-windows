/*
  Project structure:

  Main file is the contacts.c(This is the file you must compile & execute)
  --> contacts.h    # All global variables and prototype functions
  --> crud.c        # Functions to deal with Create/Read/Update/Delete Contacts
  --> menu.c        # Functions to show Menu options and grab user response.
*/
#include <stdio.h>
#include "contacts.h"
#include "menu.c"
#include "crud.c"

// Main Function
int main(void) {
  int opt = 0;
  do {
    showMenu();
    opt = userMenuOption();
    gotoMenu(opt);
  } while(opt != EXIT_CODE);
}
