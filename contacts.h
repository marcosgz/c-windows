#ifndef _CONTACTS_H_
#define _CONTACTS_H_

// Variáveis globais
#define EXIT_CODE '9'
#define INPUT_CHAR '>'
// #define clear() puts("\x1B[2J") // Limpa tela multiplataforma
#define MAX_CONTACTS 100
#define CONTACTS_DATABASE "contacts.db"

typedef struct {
  int id;
  char name[50];
  char address[60];
  char phone[13];
  char email[30];
}Contact;

Contact contacts[MAX_CONTACTS];

// Protótipo das funçoes
void waitUserReturnKey();
void crossSleep(int delay);
void clear();
int stringToInt(char str[]);
int stringLength(char str[]);
int askContactID();
char userMenuOption();
void showMenu();
void gotoMenu(char option);
void addContact();
void showContact(Contact contact);
void removeContactByID(int id);
void listContacts();
void searchContacts();
void deleteDB();
void saveData();
void loadData();
int isValidContactID(int id);
Contact findContactByID(int id);

#endif
