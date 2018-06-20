#include <stdio.h>
#include "contacts.h"
#include "menu.c"

Contact addContact() {
  Contact contact;
  return contact;
}

void removeContact(Contact* contact) {

}

void showContact(int id) {

}

// Main Function
int main(void) {
  do {
    showMenu();
  } while(userMenuOption() != EXIT_CODE);
}
