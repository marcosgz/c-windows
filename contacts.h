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
int userMenuOption();
void showMenu();
void removeContact(Contact* contact);
void showContact(int id);
Contact addContact();
