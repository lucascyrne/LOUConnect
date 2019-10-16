#include <stdio.h>  //Para funções de input e output like.
#include <stdlib.h>  // Para funções de gerenciamento de memória.
#include <conio.h>  // Para funções que movem o no console.
#include <windows.h>  // Para funções relacionadas ao OS Windows. Neste caso, só usei para dar "cls" e limpar a tela do console.
#include <string.h>  // Para operações de Strings, muito importante.

// Struct que guarda uma data. Será usado para aniversário.
typedef struct Data{
	char ano[4];
	char mes[2];
	char dia[2];
}DATA;

// Struct que guarda informações de um usuário.
typedef struct USER{
	char nome[10];
	DATA* niver;

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

USER* novoNo(void);
void inserirNo(USER**, USER*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);
USER* buscarNo(USER*, char*);
USER* deletarNo(USER*, char*);

int main()
{
	USER* arvore = NULL;  // Criação da Árvore
	char nome[10], alter[10], two[2], four[4];   // Auxiliares de busca e alteração
	char another, choice;  // Auxiliares de escolha na GUI

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
					inserirNo(&arvore, novoNo());

	                printf("\nAdicionar outro registro? (s/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '2':  // Exibe todos os USERS da árvore, em todos os 3 tipos de formato de procura.
	            system("cls");

				//printf("\nPre-Ordem:");
				//exibirPre(arvore);

				//printf("\nPos-Ordem:");
				//exibirPos(arvore);

				printf("\nIn-Ordem:");

			    exibirIn(arvore);

	            getch();
	            break;
	        case '3':  // Modifica informações de um USER.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome que deseja alterar: ");
	                scanf("%s",nome);

	                USER* temp = buscarNo(arvore, nome);
	                if (temp != NULL)  // Encontrou
	                {
		                system("cls");  // Limpa a janela do console.
				        gotoxy(30,10);  // Põe o cursor na posição 30, 10 a partir do canto superior-esquerdo.
				        printf("Usuario %s encontrado. O que deseja alterar?", nome); 
				        gotoxy(30,12);
				        printf("1. Nome");
				        gotoxy(30,14);
				        printf("2. Data de Aniversario");
				        gotoxy(30,16);
				        printf("Escolha: ");

				        fflush(stdin);
        				choice  = getche();
        				switch(choice)
        				{
        					case '1':
        						printf("\nDigite o novo nome: ");
	                			scanf("%s",alter);
	                			strcpy(temp->nome, alter);
	                			printf("\nNome alterado com sucesso!");
        						break;
        					case '2':
        						printf("\nDigite a nova data de nascimento no formato DD MM AAAA: ");
								scanf("%s", two);
								strcpy(temp->niver->dia, two);
								scanf("%s", two);
								strcpy(temp->niver->mes, two);
								scanf("%s", four);
								strcpy(temp->niver->ano, four);
								printf("\n", "Data de nascimento alterado com sucesso!");
								break;
        				}
	                }
	                else printf("%\nERRO: Usuario nao encontrado!");  // Não encontrou usuário sob este nome

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

	                arvore = deletarNo(arvore, nome);

	                printf("\nDeletar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '5':  // Sai do programa. Aqui seria a serialização da árvore?
	            return 0;
        }
	}
}

USER* novoNo(void)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));
	novoUser->esquerda = NULL;
	novoUser->direita = NULL;

	char nome[10];
	char two[2];
	char four[4];
	printf("\nInsira o nome que deseja adicionar: ");
	scanf("%s", nome);
	strcpy(novoUser->nome, nome);

	DATA* niver = (DATA*)malloc(sizeof(DATA));
	printf("\nDigite sua data de nascimento no formato DD MM AAAA: ");
	scanf("%s", two);
	strcpy(niver->dia, two);
	scanf("%s", two);
	strcpy(niver->mes, two);
	scanf("%s", four);
	strcpy(niver->ano, four);
	novoUser->niver = niver;

	return novoUser;
}

void inserirNo(USER** arvore, USER* novoUser)  // Cria novo nó, as informações novas são inseridas dentro da própria função.
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

void exibirPre(USER* arvore)  // Função que printa as chaves em Pré-ordem.
{
	if (arvore != NULL)
	{
		printf("\n\n%s :: ", arvore->nome);
 		printf("%d", arvore->niver->dia);
		printf("/%d", arvore->niver->mes);
		printf("/%d", arvore->niver->ano);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)  // Função que printa as chaves em In-ordem.
{
	if (arvore != NULL)
	{
		/*exibirIn(arvore->esquerda);
		char str_niver[10];
		strcpy(str_niver, arvore->niver->dia);
		strcat(str_niver, "/");
		strcat(str_niver, arvore->niver->mes);
		strcat(str_niver, "/");
		strcat(str_niver, arvore->niver->ano);
		printf("      %-12s\t\t %-10s\n\n", arvore->nome, str_niver);*/
		printf("\n\n%s :: ", arvore->nome);
		printf("%s", arvore->niver->dia);
		printf("/%s", arvore->niver->mes);
		printf("/%s", arvore->niver->ano);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)  // Função que printa as chaves em Pós-ordem.
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\n\n%s :: ", arvore->nome);
		printf("%d", arvore->niver->dia);
		printf("/%d", arvore->niver->mes);
		printf("/%d", arvore->niver->ano);
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