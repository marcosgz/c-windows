// Global Variables
#define EXIT_CODE 7
int latestContactID = 0; // Using this variable as our Contact AUTO_INCREMENT ID

typedef struct contact {
  int id;
  char name[50];
  char address[100];
  char phoneArea[3];
  char phone[13];
  char email[30];
  char details[255];
}Contact;

// Functions Prototypes

// -> menu.c
int userMenuOption();
void showMenu();
// -> crud.c
void showContact(int id);
void listContacts();
void searchContacts();
void removeContact(int id);
void deleteDB();
