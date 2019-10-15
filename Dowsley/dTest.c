#include <stdio.h>  //Para funções de input e output like.
#include <stdlib.h>  // Para funções de gerenciamento de memória.
#include <conio.h>  // Para funções que movem o no console.
#include <windows.h>  // Para funções relacionadas ao OS Windows. Neste caso, só usei para dar "cls" e limpar a tela do console.
#include <string.h>  // Para operações de Strings, muito importante.

// 
typedef struct USER{
	char nome[10];
	struct USER* esquerda;
	struct USER* direita;
}USER;

// <conio.h> :: Variável e função que conseguem mover o cursor de escrita e leitura no console (CMD), com coordenadas X e Y.
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
USER* deletarNo(USER*, char*);

int main()
{
	USER* arvore = NULL;  // Criação da Árvore
	char nome[10], alter[10];   // Nome q entrará na árvore.
	char another, choice;  // Variáveis auxiliares.

    while(1)
    {
        system("cls");  // Limpa a janela do console.
        gotoxy(30,10);  // Põe o cursor na posição 30, 10 a partir do canto superior-esquerdo.
        printf("1. Adicionar Registro"); 
        gotoxy(30,12);
        printf("2. Listar Registros");
        gotoxy(30,14);
        printf("3. Modificar Registros");
        gotoxy(30,16);
        printf("4. Deletar Registros");
        gotoxy(30,18);
        printf("5. Sair");
        gotoxy(30,20);
        printf("Escolha: ");
        
        fflush(stdin);  // Dá flush no input buffer. Apaga qualquer caractér ou string que havia lá antes.
        choice  = getche();  // Recebe entrada do teclado, e como padrão printa na tela.
        switch(choice)
        {
	        case '1':  // Se o usuário pressionar '1': Registra um novo USER na árvore.
	            system("cls");
	            another = 's';
	            while(another == 's')  // Se o usuário quiser outro input.
	            {
	                printf("\nInsira o nome que deseja adicionar: ");
	                scanf("%s",nome);

					inserirNo(&arvore, nome);

	                printf("\nAdicionar outro registro? (s/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '2':  // Exibe todos os USERS da árvore, em todos os 3 tipos de formato de procura.
	            system("cls");

				printf("\nPre.:");
				exibirPre(arvore);

				printf("\nIn..:");
				exibirIn(arvore);

				printf("\nPost:");
				exibirPos(arvore);

	            getch();
	            break;

	        case '3':  // Modifica informações de um USER.
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
	        case '4':  // Deleta um USER da árvore, e a reconstrói.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome que deseja deletar: ");
	                scanf("%s",nome);

	                deletarNo(arvore, nome);

	                printf("\nDeletar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '5':  // 
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

void exibirPre(USER* arvore)  // Função que printa as chaves em Pré-ordem.
{
	if (arvore != NULL)
	{
		printf(" %s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)  // Função que printa as chaves em In-ordem.
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf(" %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)  // Função que printa as chaves em Pós-ordem.
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf(" %s", arvore->nome);
	}
}

USER* buscarNo(USER* raiz, char* nome)  // Função que busca Nós por sua chave e os retorna.
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
    	return raiz; 
     
    // Key is greater than root's key 
    if (strcmp(nome, raiz->nome) > 0) 
       return buscarNo(raiz->direita, nome); 
  
    // Key is smaller than root's key 
    return buscarNo(raiz->esquerda, nome); 
}

USER* deletarNo(USER* raiz, char* nome)  // Função que busca nós pela sua chave, e os apaga da memória.
{
	if (raiz == NULL) return raiz;

	if (strcmp(nome, raiz->nome) < 0)
		raiz->esquerda = deletarNo(raiz->esquerda, nome);
	
	else if (strcmp(nome, raiz->nome) > 0)
		raiz->direita = deletarNo(raiz->direita, nome);

	// Se for igual.
	else 
	{
		// Nó com um filho ou nenhum filho.
		if (raiz->esquerda == NULL)
		{
			USER* temp = raiz->direita;
			free(raiz);
			return temp;
		}
		else if (raiz->direita == NULL)
		{
			USER* temp = raiz->esquerda;
			free(raiz);
			return temp;
		}

		// Nó com 2 filhos: Pegar o sucessor InOrdem. 
		// (o menor na subárvore da direita)
		USER* atual = raiz->direita; 
  
	    /* loop down to find the leftmost leaf */
	    while (atual && atual->esquerda != NULL)
	        atual = atual->esquerda; 
		USER* temp = atual;

		// Copia o valor do sucessor inordem para o Nó.
		strcpy(raiz->nome, temp->nome);

		// Deleta o sucessor inordem
		raiz->direita = deletarNo(raiz->direita, temp->nome);
	}
	return raiz;
}