#include <stdio.h>

void addContact() {
  Contact contact;

  printf("Digite o nome:\n> ");
  gets(contact.name);
  fflush(stdin);

  printf("Digite o endereco:\n> ");
  gets(contact.address);
  fflush(stdin);

  printf("Digite o telefone:\n> ");
  gets(contact.phone);
  fflush(stdin);

  printf("Digite o e-mail:\n> ");
  gets(contact.email);
  fflush(stdin);

  showContact(contact);

  char save;
  printf("Deseja salvar o contato no banco de dados [S/N]?\n");
  scanf("%c", &save);
  if (save == 's' || save == 'S') {
    latestContactID += 1; // Increment contact ID before save
    contact.id = latestContactID;
    saveContact(contact);
  }
}

void saveContact(Contact contact) {
  printf("\tNome\tEndereco\tTelefone\tEmail");
}

void showContact(Contact contact) {
  printf("ID\tNome\tEndereco\tTelefone\tEmail\tDetails\n");
  printf(
    "%i\t%s\t%s\t%s\t%s\t%s\n\n",
    contact.id,
    contact.name,
    contact.address,
    contact.phone,
    contact.email,
    contact.details
  );
}

void listContacts() {

}

void searchContacts() {

}

void removeContact(int id) {

}

void deleteDB() {

}

int askContactID(){
  int id;
  printf("Digite o ID do contato:\n> ");
  scanf("%d", &id);
  return id;
}
