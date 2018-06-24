// Incluir bibliotecas nativas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // tolower
#include <stdio.h>

// Variáveis globais
#define EXIT_CODE '9'
#define clear() puts("\x1B[2J") // Limpa tela multiplataforma
#define MAX_CONTACTS 100
#define CONTACTS_DATABASE "contacts.db"

typedef struct {
  int id;
  char name[50];
  char address[100];
  char phone[13];
  char email[30];
}Contact;

Contact contacts[MAX_CONTACTS];

// Protótipo das funçoes

// -> utils
int askForPositiveInt();
// -> menu.c
char userMenuOption();
void showMenu();
void gotoMenu(char option);
// -> crud.c
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
// int contactsLength();
// const char * contactRow(Contact contact);

// int contactsLength() {
//   size_t len = sizeof(contacts) / sizeof(Contact);
//   return len;
// }

int isValidContactID(int id) {
  if (id > 0 && id <= MAX_CONTACTS) {
    return 1;
  } else {
    printf("Voce digitou o ID %d que nao e valido. Precisa ser um numero entre 1 e %d\n", id, MAX_CONTACTS);
    return 0;
  }
}

void addContact() {
  Contact contact, existingContact;

  do {
    printf("Digite um ID: ");
    contact.id = askForPositiveInt();
  } while(isValidContactID(contact.id) == 0); // Força o usuário a digitar um ID valido

  existingContact = findContactByID(contact.id);
  printf("Digite o nome");
  if (existingContact.id > 0) {
    printf("(Valor atual: '%s')", existingContact.name);
  }
  printf(": ");
  scanf(" %[^\n]s", contact.name);    // gets(contact.name);
  fflush(stdin);

  printf("Digite o endereco");
    if (existingContact.id > 0) {
    printf("(Valor atual: '%s')", existingContact.address);
  }
  printf(": ");
  scanf(" %[^\n]s", contact.address); // gets(contact.address);
  fflush(stdin);

  printf("Digite o telefone");
  if (existingContact.id > 0) {
    printf("(Valor atual: '%s')", existingContact.phone);
  }
  printf(": ");
  scanf(" %[^\n]s", contact.phone);   // gets(contact.phone);
  fflush(stdin);

  printf("Digite o e-mail");
    if (existingContact.id > 0) {
    printf("(Valor atual: '%s')", existingContact.email);
  }
  printf(": ");
  scanf(" %[^\n]s", contact.email);   // gets(contact.email);
  fflush(stdin);

  showContact(contact);
  contacts[contact.id-1] = contact;
  printf("Contato salvo com sucesso!\n");
}

// Discarta os char que o usuario digita do buffer. Evita loop infinito
int askForPositiveInt() {
  int input = 0;

  do {
    scanf("%d", &input);
    while(getchar() != '\n');
  } while (input < 1);
  fflush(stdin);
  return input;
}

void showContact(Contact contact) {
  // clear();
  printf("ID\tNome\tEndereco\tTelefone\tEmail\n");
  printf(
    "%d\t%s\t%s\t%s\t%s\n\n",
    contact.id,
    contact.name,
    contact.address,
    contact.phone,
    contact.email
  );
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
  int i = 0;
  for(i = 0; i < MAX_CONTACTS; i++) {
    showContactByID(i+1);
  }
}

void searchContacts() {
  char term[255];
  int i = 0;
  Contact c;

  printf("Digite o termo da busca\n> ");
  scanf(" %[^\n]s", term);
  for(i = 0; i < MAX_CONTACTS; i++) {
    c = contacts[i];
    if (
        strstr(c.name, term) != NULL ||
        strstr(c.address, term) != NULL ||
        strstr(c.phone, term) != NULL
      ) {
      showContact(c);
    }
  }
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
    printf("Carregando banco de dados..\n");
		// fread(&tamanho, sizeof(int), 1, db);
		fread(contacts, sizeof(Contact), MAX_CONTACTS, db);
		fclose(db);
	} else {
    printf("Banco de dados nao encontrado. Ignorando..\n");
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
      contactID = askForPositiveInt();
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
      contactID = askForPositiveInt();
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
  // clear();

  int len = 9;
  char options[len][50];
  sprintf(options[0], "[1] Cadastrar/Atualizar contato");
  sprintf(options[1], "[2] Exibir contato");
  sprintf(options[2], "[3] Listar todos contatos");
  sprintf(options[3], "[4] Procurar contato");
  sprintf(options[4], "[5] Apagar contato");
  sprintf(options[5], "[6] Eliminar banco de dados");
  sprintf(options[6], "[7] Salvar alteracoes no banco de dados");
  sprintf(options[7], "[8] Discartar alteracoes");
  sprintf(options[8], "[%c] Salvar & Sair do sistema", EXIT_CODE);

  int i;
  for(i=0; i < len; i ++) {
    printf("%s\n", options[i]);
  }
}

// Main Function
int main(void) {
  char opt = EXIT_CODE;
  Contact contacts[MAX_CONTACTS];

  loadData();

  do {
    showMenu();
    opt = userMenuOption();
    gotoMenu(opt);
  } while(opt != EXIT_CODE);

  saveData();
}
