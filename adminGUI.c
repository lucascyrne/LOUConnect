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
	char nome[50], cpf[15], email[30], ocupacao[100];
	DATA niver;
	struct USER* esquerda;
	struct USER* direita;
	int altura;
}USER;

// <conio.h> :: Variável e função que conseguem mover o cursor de escrita e leitura no console (CMD), com coordenadas X e Y.
COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

USER* novoNo(USER*, char*); 
USER* inserirNo(USER*, USER*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);
void serializar(USER*, FILE*);
USER* buscarNo(USER*, char*);
USER* deletarNo(USER*, char*);
int alturaNo(USER*);
USER* rotDireita(USER*);
USER* rotEsquerda(USER*);
int fatorNo(USER*);

int main()
{
	FILE* fp;  				// Ponteiros de arquivo
	USER* arvore = NULL;  	// Criação da Árvore
	USER* temp;  			// Auxiliar para alteçao
	USER u;  				// Auxiliar para des-serializar arvore
	char another, choice;	// Auxiliares de escolha na GUI
	char var_nome[50], alter_cpf[15], alter_email[30], alter_ocupacao[100];   // Auxiliares de busca e alteração

  	// Criação ou reload de árvore.
	fp = fopen("USER.DAT", "rb+");
  	if (fp == NULL) // Criar arquivo
    {
		fp = fopen("USER.DAT", "wb+");  // Cria arquivo vazio
		if (fp == NULL)  // Se ainda não existe arquivo...
        {
          printf("Impossivel abrir/criar arquivo.");
          exit(1);  // Deu erro, sai do programa.
        }
    }
	else
    {
		system("cls");  // Limpa a janela do console.
		gotoxy(28,10);
		printf("CARREGANDO REGISTROS...");

		int count = 0;
		while(fread(&u, sizeof(u), 1, fp)==1)  // Des-serialização a partir do arquivo.
		{		
			arvore = inserirNo(arvore, novoNo(&u, NULL));
			count++;
		}

        gotoxy(28,12);
		printf("%d REGISTROS CARREGADOS COM SUCESSO!", count);
		gotoxy(28,14);
		printf("Aperte qualquer tecla para iniciar o LOUConnect!");

		fflush(stdin);
		getch();  // Continua o programa
    }

  while(1)
    {
        system("cls");  // Limpa a janela do console.
        gotoxy(30,10);  // Põe o cursor na posição 30, 10 a partir do canto superior-esquerdo.
        printf("1. Cadastrar Usuario"); 
        gotoxy(30,12);
        printf("2. Listar Usuarios");
        gotoxy(30,14);
		printf("3. Buscar um Usuario");
        gotoxy(30,16);
        printf("4. Modificar Info. de Usuario");
        gotoxy(30,18);
        printf("5. Deletar Usuario");
        gotoxy(30,20);
        printf("6. Sair");
        gotoxy(30,22);
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
					fgets(var_nome, MAX_NOME, stdin);
					if ((strlen(var_nome) > 0) && (var_nome[strlen(var_nome) - 1] == '\n'))
						var_nome[strlen (var_nome) - 1] = '\0';  // tirar o \n no final da string que entrou por conta do fgets()

					if (buscarNo(arvore, var_nome))  // Não é permitido chaves iguais em uma BST
						printf("\n<< ERRO: NOME JA EXISTE, TENTE UM DIFERENTE >>");
					else
						arvore = inserirNo(arvore, novoNo(NULL, var_nome));

	                printf("\n\nAdicionar outro Usuario? (s/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '2':  // Exibe o nome de todos os USERS da árvore In-Ordem (Ordem Alfabética)
	            system("cls");

				printf("\n================");
			    exibirIn(arvore);
				printf("\n================");

	            getch();
	            break;
			case '3':  // Busca um usuário pelo seu nome, e devolve todas as informações dele na tela.
				system("cls");
				another = 's';
				while(another == 's')
				{
					printf("\nInsira o nome do usuario que deseja buscar: ");
					fgets(var_nome, MAX_NOME, stdin);	
					if ((strlen(var_nome) > 0) && (var_nome[strlen(var_nome) - 1] == '\n'))
  				    	var_nome[strlen (var_nome) - 1] = '\0';
					
					temp = buscarNo(arvore, var_nome);
					if (temp != NULL)
					{
						printf("\nNome: %s", temp->nome);
						printf("\nData de Nascimento: %d/%d/%d", temp->niver.dia, temp->niver.mes, temp->niver.ano);
                      	printf("\nCPF: %s", temp->cpf);
                      	printf("\nEmail: %s", temp->email);
                      	printf("\nOcupacao: %s", temp->ocupacao);
					}
					else
						printf("\n<< ERRO: Usuario nao encontrado. >>");

					printf("\n\nBuscar outro Usuario? (s/n) ");
					fflush(stdin);
					another = getche();
				}
				break;
	        case '4':  // Modifica informações de um USER.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome do usuario que deseja alterar: ");
	                fgets(var_nome, MAX_NOME, stdin);
					if ((strlen(var_nome) > 0) && (var_nome[strlen(var_nome) - 1] == '\n'))
        				var_nome[strlen(var_nome) - 1] = '\0';
	                temp = buscarNo(arvore, var_nome);
	                if (temp != NULL)  // Encontrou
	                {
		                system("cls");
				        gotoxy(30,10);
				        printf("Usuario %s encontrado. O que deseja alterar?", var_nome); 
				        gotoxy(30,12);
				        printf("1. Nome");
				        gotoxy(30,14);
				        printf("2. Data de Aniversario");
				        gotoxy(30,16);
						printf("3. CPF");
						gotoxy(30,18);
						printf("4. Email");
						gotoxy(30,20);
						printf("5. Ocupacao");
						gotoxy(30,22);
				        printf("Escolha: ");

				        fflush(stdin);
        				choice  = getche();
        				switch(choice)
        				{
        					case '1':
        						printf("\nDigite o novo nome: ");
	                			fgets(var_nome, MAX_NOME, stdin);
								if ((strlen(var_nome) > 0) && (var_nome[strlen(var_nome) - 1] == '\n'))
        							var_nome[strlen (var_nome) - 1] = '\0';
								if (buscarNo(arvore, var_nome))
									printf("<< ERRO: NOME JA EXISTE, TENTE UM DIFERENTE >>");
								else
								{
	                				strcpy(temp->nome, var_nome);
	                				printf("\nNome alterado com sucesso!");
								}
        						break;
        					case '2':
        						printf("\nDigite a nova data de nascimento no formato DD MM AAAA: ");
								scanf("%d", &temp->niver.dia);
								scanf("%d", &temp->niver.mes);
								scanf("%d", &temp->niver.ano);
								printf("\nData de nascimento alterado com sucesso!");
								break;
							case '3':
								printf("\nDigite o novo CPF: ");
								scanf("%s", alter_cpf);
                            	strcpy(temp->cpf, alter_cpf);
                            	printf("\nCPF alterado com sucesso!");
								break;
							case '4':
								printf("\nDigite o novo email: ");
								scanf("%s", alter_email);
                            	strcpy(temp->email, alter_email);
                            	printf("\nEmail alterado com sucesso!");
								break;
							case '5':
								printf("\nDigite a nova ocupacao: ");
								fgets(alter_ocupacao, MAX_OCUP, stdin);
								if ((strlen(alter_ocupacao) > 0) && (alter_ocupacao[strlen(alter_ocupacao) - 1] == '\n'))
        							alter_ocupacao[strlen(alter_ocupacao) - 1] = '\0';
								strcpy(temp->ocupacao, alter_ocupacao);
								printf("\nOcupacao alterada com sucesso!");
								break;
        				}
	                }
	                else printf("\n<< ERRO: Usuario nao encontrado. >>");  // Não encontrou usuário sob este nome

	                printf("\n\nModificar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '5':  // Deleta um USER da árvore.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome que deseja deletar: ");
	                fgets(var_nome, 50, stdin);
					if ((strlen(var_nome) > 0) && (var_nome[strlen(var_nome) - 1] == '\n'))
        				var_nome[strlen(var_nome) - 1] = '\0';

					if (buscarNo(arvore, var_nome))  // Existe
					{
						arvore = deletarNo(arvore, var_nome);
						printf("\nRegistro de Usuario deletado com sucesso!\n");
					}
					else
						printf("\n<< ERRO: Usuario nao encontrado >>\n");

	                printf("\nDeletar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '6':  // Encerra o programa, e inicia a serialização de dados para garantir persistência.
				fp = freopen("USER.DAT", "wb+", fp);

				system("cls");  // Limpa a janela do console.
				gotoxy(28,10);
				printf("SALVANDO REGISTROS...");

                serializar(arvore, fp);  // Serializa a árvore.
				fclose(fp);

				gotoxy(28,12);
				printf("REGISTROS SALVOS COM SUCESSO!");
				gotoxy(28,14);
				printf("Aperte qualquer tecla para encerrar o programa.");

				fflush(stdin);
				getch();
	            exit(0);  // Encerra programa com sucesso.
        }
	}
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

USER* inserirNo(USER* raiz, USER* novoUser)  // Insere um nó na arvore, comparação igual vão para esquerda, maneira clássica. 
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

void exibirPre(USER* arvore)  // Função que printa as chaves em Pré-ordem.
{
	if (arvore != NULL)
	{
		printf("\n%s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)  // Função que printa as chaves em In-ordem.
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf("\n| %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)  // Função que printa as chaves em Pós-ordem.
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\n%s", arvore->nome);
	}
}

void serializar(USER* No, FILE* fp)  // Executa a serialização da árvore (Escrita dela num arquivo, para garantir a persistência dos dados)
{
	if (No != NULL)
	{
		fwrite(No, sizeof(USER), 1, fp);
		serializar(No->esquerda, fp);
		serializar(No->direita, fp);
	}
}

USER* buscarNo(USER* raiz, char* nome)  // Função recursiva que busca Nós por sua chave e os retorna. Caso não ache, valor é Nulo.
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
    	return raiz; 
     
    //  
    if (strcmp(nome, raiz->nome) > 0) 
       return buscarNo(raiz->direita, nome); 
  
    // Key is smaller than root's key 
    return buscarNo(raiz->esquerda, nome); 
}

USER* deletarNo(USER* raiz, char* nome)  // Função recursiva que busca por um nó pelo seu valor e o apaga da memória, após isso é feita uma reconstrução adequada da árvore.
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

int alturaNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return No->altura;
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

// Retorna o fator de balanceamento do nó.
int fatorNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return alturaNo(No->esquerda) - alturaNo(No->direita);
}