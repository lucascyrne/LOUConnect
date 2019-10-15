#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> ///for windows related functions (not important)
#include <string.h>  ///string operations

typedef struct USER{
	char nome[10];
	struct USER* esquerda;
	struct USER* direita;
}USER;

COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void inserirNo(USER**, char*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);
USER* buscarNo(USER*, char*);

int main()
{
	USER* arvore = NULL;  // Criação da Árvore
	char nome[10], alter[10];   // Nome q entrará na árvore.
	char another, choice;

    while(1)
    {
        system("cls"); ///clear the console window
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Adicionar Registro"); /// option for add record
        gotoxy(30,12);
        printf("2. Listar Registros"); /// option for showing existing record
        gotoxy(30,14);
        printf("3. Modificar Registros"); /// option for editing record
        gotoxy(30,16);
        printf("4. Deletar Registros"); /// option for deleting record
        gotoxy(30,18);
        printf("5. Sair"); /// exit from the program
        gotoxy(30,20);
        printf("Escolha: "); /// enter the choice 1, 2, 3, 4, 5
        
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard
        switch(choice)
        {
	        case '1':  // Se o usuário pressionar '1': Adiciona registro.
	            system("cls");
	            another = 's';
	            while(another == 's')  /// if user want to add another record
	            {
	                printf("\nInsira o nome que deseja adicionar: ");
	                scanf("%s",nome);

					inserirNo(&arvore, nome);

	                printf("\nAdicionar outro registro? (s/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '2':  // Exibe Registros
	            system("cls");

				printf("\nPre.:");
				exibirPre(arvore);

				printf("\nIn..:");
				exibirIn(arvore);

				printf("\nPost:");
				exibirPos(arvore);

	            getch();
	            break;

	        case '3':  // Modifica registros existentes
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome que deseja alterar: ");
	                scanf("%s",nome);
	                printf("\nDigite o novo nome: ");
	                scanf("%s",alter);

	                strcpy(buscarNo(arvore, nome)->nome, alter);

	                printf("\nModificar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '4':
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nEm breve...");
	                printf("\nDeletar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '5':
	            return 0; /// exit from the program
        }
	}
}

void inserirNo(USER** arvore, char* nome)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));
	strcpy(novoUser->nome, nome);
	novoUser->esquerda = NULL;
	novoUser->direita = NULL;

	if (*arvore == NULL)
        *arvore = novoUser;
    else
    {
        if (strcmp(novoUser->nome, (*arvore)->nome) <= 0)
            inserirNo(&(*arvore)->esquerda, nome);
        else
        	inserirNo(&(*arvore)->direita, nome);
    }
}

void exibirPre(USER* arvore)
{
	if (arvore != NULL)
	{
		printf(" %s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf(" %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf(" %s", arvore->nome);
	}
}

USER* buscarNo(USER* raiz, char* nome)
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0); 
    	return raiz; 
     
    // Key is greater than root's key 
    if (strcmp(nome, raiz->nome) > 0) 
       return buscarNo(raiz->direita, nome); 
  
    // Key is smaller than root's key 
    return buscarNo(raiz->esquerda, nome); 
}