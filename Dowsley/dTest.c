#include <stdio.h>
#include <stdlib.h>   // Para gerenciamento de memória
#include <conio.h>   // para gerenciamento de input e output direto do console.
#include <windows.h> // Para funções relacionadas ao windows
#include <string.h>  // Operações de string
#include <unistd.h>  // Para sleep functions
#define NULO -1  // Valor que sinaliza NULL na des-serialização, e por conveniência fica guardado na idade.

COORD coord = {0,0}; /// top-left corner of window

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

typedef struct USER{
	char nome[10];

	struct USER* esquerda;
	struct USER* direita;
}USER;

void inserirNo(USER**, USER*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);

int main()
{
	FILE *fp, *ft;	// ponteiros pra arquivo
	USER* arvore = NULL;  // Inicia arvore.
	
	USER u;	// Vessel para novo usuário.
	long int recsize = sizeof(u);  // Tamanho de cada struct user.

	char choice, another;


	/******* Criação/Loading do arquivo. *****
    fp = fopen("Users.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("Users.DAT","wb+");
        if(fp == NULL)
        {
            printf("Impossivel abrir arquivo.");
            exit(1);
        }
        printf("Arquivo criado.\n");
    }
    else 
    	printf("Arquivo aberto.\n");*/


    /****** Des-serialização da árvore. *****
    printf("** Carregando árvore... **\n");

	rewind(fp);  // Move o cursor para o começo do arquivo
	while(fread(&e,recsize,1,fp)==1)  // lê o arquivo e resgata record vez por vez, avançando cursor.
    {
    	if (e.idade != NULO)  //  Se a idade for -1 o struct representa o valor nulo.
    	{
    		inserirNo(&arvore, &e);  // Insere na árvore o user carregado
    	}

    	else
    }
    printf("** Árvore carregada. ***");*/

	while(1)
	{
		system("cls");  // Limpa a janela do console
        gotoxy(30,10);
        printf("1. Adicionar Registro");
        gotoxy(30,12);
        printf("2. Listar Registros");
        gotoxy(30,14);
        printf("3. Modificar Registros");
        gotoxy(30,16);
        printf("4. Deletar Registros");
        gotoxy(30,18);
        printf("5. Fechar Programa");  // Serialização acontece no case 5.
        gotoxy(30,20);
        printf("Sua escolha: ");
        fflush(stdin);  // limpa o input buffer
        choice  = getche();  // recebe input do teclado
        
        switch(choice)
        {
	        case '1':
	            system("cls");
	            another = 'y';
	            
	            while(another == 'y')  /// if user want to add another record
	            {
	                printf("\nInsira o nome: ");
	                scanf("%s",u.nome);

	                u.esquerda = NULL;
					u.direita = NULL;

	                inserirNo(&arvore, &u);
	          
	                printf("\nAdd another record(y/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
        

	        case '2':
	            system("cls");
	            exibirIn(arvore);
	            getch();
	            break;
        }
	}

	return 0;
}


void inserirNo(USER** arvore, USER* novoUser)
{
	if (*arvore == NULL)
        *arvore = novoUser;
    else
    {
        if (strcmp(novoUser->nome, (*arvore)->nome) <= 0)
            inserirNo(&(*arvore)->esquerda, novoUser);
        else
        	inserirNo(&(*arvore)->direita, novoUser);
    }
}

void exibirPre(USER* arvore)
{
	if (arvore != NULL)
	{
		printf("\nNome: %s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf("\nNome: %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\nNome: %s", arvore->nome);
	}
}