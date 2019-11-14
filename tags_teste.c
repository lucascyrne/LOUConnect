# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct possuidores{
	char nome[50];
	struct possuidores* proxUser = NULL;
}uSER

typedef struct tags{
	char nome[15], descricao[100];
	user* user;
	struct tags* prox;
}tag;

tag* pesquisarTag(tag* primeira, char* nomeTag)
{
	if (strcmp(primeira -> nome, nomeTag) == 0) return primeira;

	else if(primeira -> prox == NULL) return NULL;

	else pesquisarTag(primeira -> prox, nomeTag);
}

void addTag(tag* tagAgr, tag* tagCriar)
{
	if (tagAgr -> prox == NULL) tagAgr -> prox = tagCriar;

	else addtag(tagAgr -> prox, tagCriar);
}

tag* criarTag(char* nome, char* criador, char* descricao)
{
	tag* novaTag = (tag*)malloc(sizeof(tag));
	
	novaTag -> nome = nome;
	novaTag -> descricao = descricao
	novaTag -> user = NULL
	addUSer(criador, novaTag, novaTag -> user);
	novaTag -> prox = NULL;

	return novaTag;
}

void addUSer(char* nome, tag* atual, uSER* agra)
{	
	if (atual -> user == NULL)
	{
		uSER* novoUser = (uSER*)malloc(sizeof(uSER));

		novoUser -> nome = nome;
		novoUser -> proxUser = NULL;
		
		atual -> user = novoUser;		
	}
	
	else if(agra -> proxUser = NULL) 
	{
		uSER* novoUser = (uSER*)malloc(sizeof(uSER));

		novoUser -> nome = nome;
		novoUser -> proxUser = NULL;
		
		agra -> proxUser = novoUser;
	}
		
	else addUSer(nome, atual, agra -> proxUser);
}

char* showUsers(uSER* atual, char* all)
{	
	char* a11 = strncat(all, atual -> nome;, strlen(agra));
	
	if (atual -> proxUser == NULL) return a11;
	else showUsers(atual -> proxUser, a11);
}


int main()
{

	{
		printf("\nTag %s encontrada!\n", primeira -> nome);
		printf("Descricao: %s\nPossuintes: ", primeira -> descricao);
		showUsers(primeira);
	}	
}