// Incluir bibliotecas nativas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Cabeçalhos locais
#include "contacts.h"
#include "screen.c"

int isValidContactID(int id) {
  if (id > 0 && id <= MAX_CONTACTS) {
    return 1;
  } else {
    printf("Voce digitou o ID %d que nao e valido. Precisa ser um numero entre 1 e %d\n", id, MAX_CONTACTS);
    return 0;
  }
}

void waitUserReturnKey() {
  // Flush stdin
  int ch;
  do {
    ch = fgetc(stdin);
  } while (ch != EOF && ch != '\n');
  clearerr(stdin);
  // flush stdout
  fflush(stdout);
  getchar();
}

void crossSleep(int delay){
  #ifdef _WIN32
  Sleep(delay);
  #else
  usleep(delay * 1000);  /* sleep for 100 milliSeconds */
  #endif
}

void clear() {
  #ifdef _WIN32
  system("cls");
  #else
  system("clear");
  #endif
}

int stringToInt(char str[]) {
  int number = 0;
  sscanf(str, "%d", &number);
  return number;
}

int stringLength(char str[]) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

void addContact() {
  Contact contact, existingContact;

  Screen window;
  ScreenPosition pos;
  readScreen("./screens/contact-form.txt", &window);
  showScreen(&window);


  char stringID[2];
  do {
    // Move o cursor para o campo ID:
    pos.x = 7;
    pos.y = 3;
    promptScreen(&window, &pos, stringID);
    contact.id = stringToInt(stringID);
    if (!isValidContactID(contact.id)) {
      updateScreenStr(&window, &pos, "__");
      pos.y = 4;
      updateScreenStr(&window, &pos, "-> ID nao e valido");
    } else {
      pos.y = 4;
      updateScreenStr(&window, &pos, "                  ");
    }
  } while(!isValidContactID(contact.id));

  existingContact = findContactByID(contact.id);
  if (existingContact.id == contact.id) {
    pos.x = 9;
    pos.y = 6;
    updateScreenStr(&window, &pos, existingContact.name);
    pos.x = 13;
    pos.y = 8;
    updateScreenStr(&window, &pos, existingContact.phone);
    pos.x = 13;
    pos.y = 10;
    updateScreenStr(&window, &pos, existingContact.address);
    pos.x = 11;
    pos.y = 12;
    updateScreenStr(&window, &pos, existingContact.email);
  }

  pos.x = 9;
  pos.y = 5;
  promptScreen(&window, &pos, contact.name);

  pos.x = 13;
  pos.y = 7;
  promptScreen(&window, &pos, contact.phone);

  pos.x = 13;
  pos.y = 9;
  promptScreen(&window, &pos, contact.address);

  pos.x = 11;
  pos.y = 11;
  promptScreen(&window, &pos, contact.email);

  showContact(contact);
  contacts[contact.id-1] = contact;
}

// Discarta os char que o usuario digita do buffer. Evita loop infinito
int askContactID() {
  int id;
  char stringID[2];
  Screen window;
  ScreenPosition pos;
  readScreen("./screens/ask-contact-id.txt", &window);
  showScreen(&window);

  do {
    // Move o cursor para o campo ID:
    pos.x = 26;
    pos.y = 7;
    promptScreen(&window, &pos, stringID);
    id = stringToInt(stringID);
    if (!isValidContactID(id)) {
      updateScreenStr(&window, &pos, "__");
      pos.y = 8;
      updateScreenStr(&window, &pos, "-> ID nao e valido");
    } else {
      pos.y = 8;
      updateScreenStr(&window, &pos, "                  ");
    }
  } while(!isValidContactID(id));

  return id;
}

void showContact(Contact contact) {
  Screen window;
  ScreenPosition pos;
  readScreen("./screens/show-contact.txt", &window);
  showScreen(&window);

  pos.x = 7;
  pos.y = 3;
  updateScreenInt(&window, &pos, contact.id);

  pos.x = 9;
  pos.y = 5;
  updateScreenStr(&window, &pos, contact.name);

  pos.x = 13;
  pos.y = 7;
  updateScreenStr(&window, &pos, contact.phone);

  pos.x = 13;
  pos.y = 9;
  updateScreenStr(&window, &pos, contact.address);

  pos.x = 11;
  pos.y = 11;
  updateScreenStr(&window, &pos, contact.email);
  showScreen(&window);
  waitUserReturnKey();
}

Contact findContactByID(int id) {
  Contact fakeContact;
  if (!isValidContactID(id)) {
    fakeContact.id = 0;
    return fakeContact;
  }
  return contacts[id - 1];
}

void showContactByID(int id) {
  Contact contact;
  contact = findContactByID(id);
  if (contact.id == id) {
    showContact(contact);
  }
}

void removeContactByID(int id) {
  if (!isValidContactID(id)) {
    return;
  }
  contacts[id-1].id = 0;
  sprintf(contacts[id-1].name, "");
  sprintf(contacts[id-1].email, "");
  sprintf(contacts[id-1].phone, "");
}

void listContacts() {
  Screen window;
  ScreenPosition pos;
  readScreen("./screens/blank.txt", &window);
  int i = 0, line = 2;
  for(i = 0; i < MAX_CONTACTS; i++) {
    if (contacts[i].id == i+1) {
      pos.y = line;
      pos.x = 6;
      updateScreenStr(&window, &pos, "ID: ");
      pos.x = 10;
      updateScreenInt(&window, &pos, contacts[i].id);
      pos.x = 14;
      updateScreenStr(&window, &pos, "Nome: ");
      pos.x = 20;
      updateScreenStr(&window, &pos, contacts[i].name);
      line ++;
    }
  }
  showScreen(&window);
  waitUserReturnKey();
}

void searchContacts() {
  char term[80];
  int i = 0, found = 0;
  Contact c;

  Screen searchWindow, resultWindow;
  ScreenPosition searchPos, resultPos;
  readScreen("./screens/search.txt", &searchWindow);
  readScreen("./screens/blank.txt", &resultWindow);
  showScreen(&searchWindow);

  searchPos.x = 17;
  searchPos.y = 7;
  promptScreen(&searchWindow, &searchPos, term);

  for(i = 0; i < MAX_CONTACTS; i++) {
    c = contacts[i];
    if (strstr(c.name, term) != NULL) {
      found++;
      resultPos.x = 6;
      resultPos.y = 1 + found;
      updateScreenStr(&resultWindow, &resultPos, "ID: ");
      resultPos.x = 10;
      updateScreenInt(&resultWindow, &resultPos, c.id);
      resultPos.x = 14;
      updateScreenStr(&resultWindow, &resultPos, "Nome: ");
      resultPos.x = 20;
      updateScreenStr(&resultWindow, &resultPos, c.name);
    } else if (strstr(c.phone, term) != NULL) {
      found++;
      resultPos.x = 6;
      resultPos.y = 1 + found;
      updateScreenStr(&resultWindow, &resultPos, "ID: ");
      resultPos.x = 10;
      updateScreenInt(&resultWindow, &resultPos, c.id);
      resultPos.x = 14;
      updateScreenStr(&resultWindow, &resultPos, "Telefone: ");
      resultPos.x = 24;
      updateScreenStr(&resultWindow, &resultPos, c.phone);
    }
  }
  if (found == 0) {
    resultPos.x = 25;
    resultPos.y = 7;
    updateScreenStr(&resultWindow, &resultPos, "Nenhum resultado encontrado");
  }
  showScreen(&resultWindow);
  waitUserReturnKey();
}

void deleteDB() {
  if (remove("contacts.db") != 0) {
    fprintf(stderr, "Erro ao remover o arquivo %s.\n", "contacts.db");
  } else {
    printf("O banco de dados '%s' foi removido com sucesso!\n", "contacts.db");
  }
}

void saveData() {
  FILE *db;
	db = fopen(CONTACTS_DATABASE, "wb");
	fwrite(contacts, sizeof(Contact), MAX_CONTACTS, db);
	fclose(db);
  printf("Alteracoes salvas com sucesso\n");
}

void loadData() {
  FILE *db;
	// int tamanho = 0;
	db = fopen(CONTACTS_DATABASE, "rb");
	if (db != NULL) {
    // printf("Carregando banco de dados..\n");
		// fread(&tamanho, sizeof(int), 1, db);
		fread(contacts, sizeof(Contact), MAX_CONTACTS, db);
		fclose(db);
	} else {
    // printf("Banco de dados nao encontrado. Ignorando..\n");
  }
}

void gotoMenu(char option) {
  int contactID;
  switch(option) {
    case '1':
      addContact();
      break;
    case '2':
      printf("Digite o ID do contato:\n> ");
      contactID = askContactID();
      showContactByID(contactID);
      break;
    case '3':
      listContacts();
      break;
    case '4':
      searchContacts();
      break;
    case '5':
      printf("Digite o ID do contato:\n> ");
      contactID = askContactID();
      removeContactByID(contactID);
      break;
    case '6':
      deleteDB();
      break;
    case '7':
      saveData();
      break;
    case '8':
      loadData();
      break;
    default:
      break;
  }
}

char userMenuOption() {
  char option;
  printf("\n> ");
  scanf(" %c", &option);
  fflush(stdin);

  return option;
}

// Print a simple menu with all options available to the user
void showMenu() {
  clear();
  // Cria a tela para Menu
  Screen menu;
  readScreen("./screens/menu.txt", &menu);
  showScreen(&menu);
}

// Main Function
int main(void) {
  char opt = EXIT_CODE;
  Contact contacts[MAX_CONTACTS];

  loadData();
  clear();

  Screen welcome;
  readScreen("./screens/welcome.txt", &welcome);
  showScreen(&welcome);
  // crossSleep(2000);
  clear();

  do {
    showMenu();
    opt = userMenuOption();
    gotoMenu(opt);
  } while(opt != EXIT_CODE);

  saveData();
}
