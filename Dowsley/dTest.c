#include <stdio.h>
#include <stdlib.h>   // Para gerenciamento de memória
#include <conio.h>   // para gerenciamento de input e output direto do console.
#include <windows.h> // Para funções relacionadas ao windows
#include <string.h>  // Operações de string
#include <unistd.h>  // Para sleep functions


/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

typedef struct user{
	char nome[50];
	char email[40];
	char cargo[40];
	char cpf[11];
	char telefone[11];
	char tags[100];
	int idade;

	struct user* esquerda;
	struct user* direita;
}USER;

void inserirNo(USER**);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);

int main()
{
	long int recsize = sizeof(e);	// Tamanho de cada struct user.
	FILE *fp, *ft;	// ponteiros pra arquivo
	
	USER* arvore = NULL;	// Inicia arvore.

    fp = fopen("Users.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("Users.DAT","wb+");
        if(fp == NULL)
        {
            printf("Impossivel abrir arquivo.");
            exit(1);
        }
    }






	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &n);
		inserirNo(&arvore, n);
	}

	return 0;
}

void inserirNo(USER** arvore)
{
	USER* novo_user = (USER*)malloc(sizeof(USER));
	novo_user->valor = n;
	novo_user->esquerda = NULL;
	novo_user->direita = NULL;

	if (*arvore == NULL)
        *arvore = novo_user;
    else
    {
        if (n <= (*arvore)->valor)
            inserirNo(&(*arvore)->esquerda, n);
        else
        	inserirNo(&(*arvore)->direita, n);
    }
}

void exibirPre(USER* arvore)
{
	if (arvore != NULL)
	{
		printf(" %d", arvore->valor);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf(" %d", arvore->valor);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf(" %d", arvore->valor);
	}
}