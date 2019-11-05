#include "functions.c"	 // Contém todas as funções e definições necessárias para gerenciar os registros armazenados.

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