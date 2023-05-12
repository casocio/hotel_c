#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

#define LUNGHEZZA_USERNAME 25
#define LUNGHEZZA_PASSWORD 50
#define N_UTENTI 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_LINE_LENGTH 100

void loginUser(void);
void registerUser(void);
void changePassword(void);
void richiesta_accesso(void);

// Set colori
/*
0 - Nero
1 - Blu scuro
2 - Verde scuro
3 - Verde acqua scuro
4 - Rosso scuro
5 - Viola scuro
6 - Giallo scuro
7 - Grigio chiaro
8 - Grigio scuro
9 - Blu chiaro
10 - Verde chiaro
11 - Verde acqua chiaro
12 - Rosso chiaro
13 - Rosa
14 - Giallo chiaro
15 - Bianco
*/

void SetColor(short Color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // oppure system("COLOR E9"); 
	SetConsoleTextAttribute(hCon,Color); 
}

void welcomeScreen(void)
{
	system("cls");
	SetColor(6);
	printf("Ti diamo il benvenuto nel negozio di abbigliamento: ");
	SetColor(12);
	printf("Bella Moda\n");
	
	SetColor(4);
	printf("ATTENZIONE: ");
	SetColor(15);
	printf("Per poter proseguire, bisogna accedere o registrarsi.\n"
	"\n1.Registrati\n2.Accedi\n3.Cambia password\n0.Esci dal programma\n"
	"\nInserisci il numero in base alla tua scelta: ");
}

// Struttura per rappresentare un utente
typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void optionAccess(void)
{
	char choice;
	do
	{
  		welcomeScreen();
        choice = getchar();
		fflush(stdin);  // Pulisce il buffer di input
        if(choice == '\n')
		{
			SetColor(4);
			printf("ERRORE: Nessuna scelta inserita. Riprova.\n\n");
			SetColor(15);
			system("pause");
		}else
		{
			switch (choice)
			{
	        	case '0':
	        		system("cls");
	        		puts("Sei uscito dal programma.");
					exit(1);
	        		break;
	            
				case '1':
	                registerUser();
	                break;
	            
				case '2':
	                loginUser();
	                break;
	            
				case '3':
	                changePassword();
	                break;
	            
				default:
					SetColor(4);
	                printf("ERRORE: Scelta non valida. Riprova.\n\n");
	                SetColor(15);
	                system("pause");
	                system("cls");
					break;
	        }
	        printf("\n");
    	}
    }while(choice >= 3);
}

// Funzione per registrare un nuovo utente
void registerUser(void)
{
	system("cls");
	SetColor(2);
	printf("Registrazione\n");
	SetColor(15);
    User newUser;
    printf("\nUsername: ");
    scanf("%s", newUser.username);
    printf("Password: ");
    scanf("%s", newUser.password);
    fflush(stdin);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
	{
        printf("Impossibile aprire il file.");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int userExists = 0;

    // Verifica se l'utente esiste già
    while (fgets(line, sizeof(line), file) != NULL)
	{
        char savedUsername[MAX_USERNAME_LENGTH];
        sscanf(line, "%s", savedUsername);

        if (strcmp(savedUsername, newUser.username) == 0)
		{
            userExists = 1;
            break;
        }
    }

    fclose(file);

    if (userExists)
	{
        printf("\nL'utente esiste già. Si prega di scegliere un altro nome utente.\n");
        system("pause");
        return;
    }

    file = fopen("users.txt", "a");
    if (file == NULL)
	{
        printf("Impossibile aprire il file.");
        return;
    }

    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    fclose(file);

    printf("Registrazione completata.\n");
}

// Funzione per effettuare il login
void loginUser(void)
{
	system("cls");
	SetColor(2);
	printf("Login\n");
	SetColor(15);
    
	char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
	printf("\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
	{
        printf("Impossibile aprire il file.");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int loggedIn = 0;

    while (fgets(line, sizeof(line), file) != NULL)
	{
        char savedUsername[MAX_USERNAME_LENGTH];
        char savedPassword[MAX_PASSWORD_LENGTH];
        sscanf(line, "%s %s", savedUsername, savedPassword);

        if (strcmp(savedUsername, username) == 0 && strcmp(savedPassword, password) == 0)
		{
            loggedIn = 1;
            break;
        }
    }

    fclose(file);

    if (loggedIn)
	{
        printf("Accesso effettuato.\n");
    }else
	{
        printf("Credenziali errate.\n");
    }
}

// Funzione per modificare la password di un utente
void changePassword(void)
{
	system("cls");
	SetColor(2);
	printf("Cambio Password\n");
	SetColor(15);
    
	char username[MAX_USERNAME_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    
	printf("\nUsername: ");
    scanf("%s", username);
    printf("Nuova password: ");
    scanf("%s", newPassword);
    puts("\nLa password e' stata modificata con successo");
    system("pause");
    
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL)
	{
        printf("Impossibile aprire il file.");
        return;
    }

    char line[MAX_LINE_LENGTH];
    long int currentPosition = ftell(file);
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
	{
        char savedUsername[MAX_USERNAME_LENGTH];
        char savedPassword[MAX_PASSWORD_LENGTH];
        sscanf(line, "%s %s", savedUsername, savedPassword);

        if (strcmp(savedUsername, username) == 0)
		{
            found = 1;
            fseek(file, currentPosition, SEEK_SET);
            fprintf(file, "%s %s\n", savedUsername, newPassword);
            break;
        }
        currentPosition = ftell(file);
    }

    fclose(file);

    if (found)
	{
        printf("Password modificata.\n");
    }else
	{
        printf("Utente non trovato.\n");
    }
}

int main(void)
{
    int choice;
    welcomeScreen();
    optionAccess();
    system("pause");
    system("cls");
	printf("ciao");
    return 0;
}
