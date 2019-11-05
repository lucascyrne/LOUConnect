#include <stdio.h>   // Para funções de input e output.
#include <stdlib.h>  // Para funções de gerenciamento de memória.
#include <conio.h>   // Para funções que movem o cursor de escrita, e gerenciam entrada e saída de caracteres.
#include <windows.h> // Para funções relacionadas ao OS Windows. Neste caso, só está sendo usada para dar "cls" e limpar a tela do console.
#include <string.h>  // Para operações de Strings, muito importante.
#define max(a,b) (((a) > (b)) ? (a) : (b))	// Achar maior valor rapidamente.
#define MAX_NOME 50   // Tamanho maximo do stream para nome
#define MAX_OCUP 100  // Tamanho maximo do stream para ocupação

// Struct que guarda uma data. Será usado para aniversário.
typedef struct Data{
	int dia;	
	int mes;
	int ano;
}DATA;

// Struct que guarda informações de um usuário.
typedef struct USER{
	char nome[50], ocupacao[100], senha[50], cpf[15], email[30];
	DATA niver;
	struct USER* esquerda;
	struct USER* direita;
	int altura;
}USER;



/* Prototipos de funcoes */
USER* novoNo(USER*, char*);
USER* inserirNo(USER*, USER*);	
USER* buscarNo(USER*, char*);
USER* deletarNo(USER*, char*);

int alturaNo(USER*);
int fatorNo(USER*);
USER* rotDireita(USER*);
USER* rotEsquerda(USER*);

void serializar(USER*, FILE*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);


// <conio.h> :: Variável e função conseguem mover o cursor de escrita e leitura no console (CMD), com coordenadas X e Y.
COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


// Cria um novo nó caso a primeira entrada seja nula. Caso a entrada seja outro nó, apenas gera um novo e copia as informações para ele.
USER* novoNo(USER* No, char* nome)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));

	if (No != NULL)
	{
		*novoUser = *No;
		novoUser->esquerda = NULL;
		novoUser->direita = NULL;
		novoUser->altura = 1;
		return novoUser;
	}

	novoUser->esquerda = NULL;
	novoUser->direita = NULL;
	novoUser->altura = 1;

	strcpy(novoUser->nome, nome);
    
	char senha[20],c=' ';
	int i=0;
	printf("\nEscreva sua senha com no maximo 20 caracteres: ");
	while (i <= 20){
	    c=getch();
	    if(c == 13 || c== 9)
	    {
	    	senha[i] = '\0';
	    	break;
	    }
	    else if(c == 8)
	    {
	    	if(i > 1)
	    	{
	    		i--;
	    		printf("\b \b");
	    	}
	    }else
	    {
			senha[i++] = c;
	    	printf("* \b");
	    } 
	}
	if ((strlen(senha) > 0) && (senha[strlen(senha) - 1] == '\n'))
		senha[strlen(senha) - 1] = '\0';
	strcpy(novoUser->senha, senha);
	printf("\n");


	char ocupacao[100];
	printf("\nDigite sua ocupacao em no maximo 100 caracteres: ");
	fgets(ocupacao, MAX_OCUP, stdin);
	if ((strlen(ocupacao) > 0) && (ocupacao[strlen(ocupacao) - 1] == '\n'))
		ocupacao[strlen(ocupacao) - 1] = '\0';
	strcpy(novoUser->ocupacao, ocupacao);

	printf("\nDigite sua data de nascimento no formato DD MM AAAA: ");
	scanf("%d", &novoUser->niver.dia);
	scanf("%d", &novoUser->niver.mes);
	scanf("%d", &novoUser->niver.ano);

	char cpf[15];
	printf("\nDigite seu CPF: ");
	scanf("%s", cpf);
	strcpy(novoUser->cpf, cpf);

	char email[30];
	printf("\nDigite seu email: ");
	scanf("%s", email);
	strcpy(novoUser->email, email);

	return novoUser;
}


// Insere um nó na arvore, comparação igual vão para esquerda, maneira clássica. 
USER* inserirNo(USER* raiz, USER* novoUser) 
{
	/******* (PASSO 1) INSERÇÃO BST *******/
	// Caso 1: Nova raiz da sub-árvore.
	if (raiz == NULL)
		return novoUser;
    
	// Caso 2: Chave MENOR que a da raiz.
	if (strcmp(novoUser->nome, raiz->nome) < 0)
        raiz->esquerda = inserirNo(raiz->esquerda, novoUser);
    
	// Caso 3: Chave MAIOR que a da raiz.
	else if (strcmp(novoUser->nome, raiz->nome) > 0)
        raiz->direita = inserirNo(raiz->direita, novoUser);
	
	// Caso 4: Chaves iguais, não permitido em BSTs.
	else
	{
		printf("<< ERRO: Nome em uso, tente outro >>");
		return raiz;
	}

	/****** (PASSO 2) ATUALIZAÇÃO DE ALTURA ******/
	raiz->altura = 1 + max(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

	/* (3) CHECAR FATOR DE BALANCEAMENTO E REALIZAR ROTAÇÕES SE NECESSÁRIO */
	int fator = fatorNo(raiz);
	
	// Caso LL
	if (fator > 1 && strcmp(novoUser->nome, raiz->esquerda->nome) < 0)
		return rotDireita(raiz);
	// Caso RR
	if (fator < -1 && strcmp(novoUser->nome, raiz->direita->nome) > 0)
		return rotEsquerda(raiz);
	// Caso LR
	if (fator > 1 && strcmp(novoUser->nome, raiz->esquerda->nome) > 0)
	{
		raiz->esquerda = rotEsquerda(raiz->esquerda);
		return rotDireita(raiz);
	}
	// Caso RL
	if (fator < -1 && strcmp(novoUser->nome, raiz->direita->nome) < 0)
	{
		raiz->direita = rotDireita(raiz->direita);
		return rotEsquerda(raiz);
	}

	/*** Caso Padrão: Retorna raiz (nó) não alterada ***/
	return raiz;
}


// Função recursiva que busca Nós por sua chave e os retorna. Caso não ache, valor é Nulo.
USER* buscarNo(USER* raiz, char* nome)  
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
    	return raiz; 
     
    //  
    if (strcmp(nome, raiz->nome) > 0) 
       return buscarNo(raiz->direita, nome); 
  
    // Key is smaller than root's key 
    return buscarNo(raiz->esquerda, nome); 
}


// Função recursiva que busca por um nó pelo seu valor e o apaga da memória, após isso é feita uma reconstrução adequada da árvore.
USER* deletarNo(USER* raiz, char* nome)  
{
	/** (PASSO 1) REMOÇÃO PADRÃO DE BST **/
	
	// Não encontrou.
	if (raiz == NULL)
		return raiz;
	// Chave MENOR que a da raiz.
	if (strcmp(nome, raiz->nome) < 0)
		raiz->esquerda = deletarNo(raiz->esquerda, nome);
	// Chave MENOR que a da raiz.
	else if (strcmp(nome, raiz->nome) > 0)
		raiz->direita = deletarNo(raiz->direita, nome);

	// Se for igual --> Encontrou o Nó certo.
	else 
	{
		// Nó com apenas um ou nenhum filho.
		if ( (raiz->esquerda == NULL) || (raiz->direita == NULL) )
		{
			USER* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

			// Caso de nenhum filho
			if (temp == NULL)
			{
				temp = raiz;
				raiz = NULL;
			}
			// Caso de 1 filho
			else *raiz = *temp;
			free(temp);
		}
		// Nó com 2 filhos
		else
		{
			// Acha o sucessor InOrdem
			USER* atual = raiz->direita; 
			while (atual->esquerda != NULL) 
				atual = atual->esquerda;
			// Passa a chave do sucessor para a raiz
			strcpy(raiz->nome, atual->nome);
			// Deleta o sucessor
			raiz->direita = deletarNo(raiz->direita, atual->nome);
		}
	}

	// Se a árvore tinha apenas um nó:
	if (raiz == NULL)
		return raiz;
	
	/*** (PASSO 2) ATUALIZAÇÃO DA ALTURA ***/
	raiz->altura = 1 + max(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

	/* (PASSO 3) CHECAR FATOR DE BALANCEAMENTO E REALIZAR ROTAÇÕES SE NECESSÁRIO */
	int fator = fatorNo(raiz);
	
	// Caso LL
	if (fator > 1 && fatorNo(raiz->esquerda) >= 0)
		return rotDireita(raiz);
	// Caso RR
	if (fator < -1 && fatorNo(raiz->direita) <= 0)
		return rotEsquerda(raiz);
	// Caso LR
	if (fator > 1 && fatorNo(raiz->esquerda) < 0)
	{
		raiz->esquerda = rotEsquerda(raiz->esquerda);
		return rotDireita(raiz);
	}
	// Caso RL
	if (fator < -1 && fatorNo(raiz->direita) > 0)
	{
		raiz->direita = rotDireita(raiz->direita);
		return rotEsquerda(raiz);
	}

	/*** Caso Padrão: Retorna raiz (nó) não alterada ***/
	return raiz;
}


// Retorna a altura de um Nó. Nó não existente tem altura 0.
int alturaNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return No->altura;
}


// Retorna o fator de balanceamento do nó.
int fatorNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return alturaNo(No->esquerda) - alturaNo(No->direita);
}


// Função que printa as chaves em Pré-ordem.
void exibirPre(USER* arvore)
{
	if (arvore != NULL)
	{
		printf("\n%s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}


// Função que printa as chaves em In-ordem.
void exibirIn(USER* arvore)  
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf("\n| %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}


// Função que printa as chaves em Pós-ordem.
void exibirPos(USER* arvore)  
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\n%s", arvore->nome);
	}
}


// Executa a serialização da árvore (Escrita dela num arquivo, para garantir a persistência dos dados)
void serializar(USER* No, FILE* fp)  
{
	if (No != NULL)
	{
		fwrite(No, sizeof(USER), 1, fp);
		serializar(No->esquerda, fp);
		serializar(No->direita, fp);
	}
}


// Realiza rotação da sub-árvore y pra direita, retorna a nova raiz que fica no lugar de y.
USER* rotDireita(USER* y)
{
	USER* x = y->esquerda;
	USER* sub = x->direita;

	// Realiza rotação.
	x->direita = y;
	y->esquerda = sub;

	// Atualiza altura.
	y->altura = max(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;
	x->altura = max(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;

	// Retorna a nova raiz
	return x;
}


// Realiza rotação da sub-árvore x pra esquerda, retorna a nova raiz que fica no lugar de x.
USER* rotEsquerda(USER* x)
{
	USER* y = x->direita;
	USER* sub = y->esquerda;

	// Realiza rotação.
	y->esquerda = x;
	x->direita = sub;

	// Atualiza altura.
	x->altura = max(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;
	y->altura = max(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

	// Retorna a nova raiz
	return y;
}