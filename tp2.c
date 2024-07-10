#include <stdio.h>
#include <string.h>
#define N 60
#define N_ERROS 3
#define PAR 100
#define N_COMANDOS	5
#define	N_PARAMETROS_MAXIMOS 5

typedef struct 
{
	char comando[N];
	int n_parametros; 
	int tipo_parametros[N_PARAMETROS_MAXIMOS];	
}	COMANDO;

typedef struct 
{
	int operacoes_sem_erro;	
	int operacoes_erros[3];
	int n_com_parametros_opc;
	int usos[N];
}	HISTORICOS;

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int inserir(COMANDO *cm)
{
	system("cls");
	int i,std;
	printf("Inserir o nome do comando:\n");
	fgets(cm->comando,N,stdin); 
	cm->comando[strlen(cm->comando)-1] = '\0'; 	
	printf("Inserir o numero de parametros obrigatorios:\n");
	fscanf(stdin,"%d",&cm->n_parametros);	
	if (cm->n_parametros> 5)
	{
		printf("Numero maximo de parametros excedido\n");
		strcpy(cm->comando,"");
		std = 0;
	}else{
		std = 1;
	}
	for (i = 0; i < cm->n_parametros; ++i)
	{
		printf("Qual o tipo do %d parametro:\n", i+1);
		printf("0 - int / 1 - float / 2 - string\n");
		fscanf(stdin,"%d", &cm->tipo_parametros[i]);
		if (cm->tipo_parametros[i] < 0 || cm->tipo_parametros[i]>5)
		{
			printf("Erro\n");
			std = 0;
		}
	}

	return std;
}

void	lista(COMANDO *cm, int i_n)
{
	int i;
	if (strlen(cm->comando)>0)
	{
		printf("%dÂº. %s, com %d parametros obrigatorios.\n",i_n+1, cm->comando, cm->n_parametros);
		printf("Tipos de parametros:	");
		for (i = 0; i < cm->n_parametros; ++i)
		{
			printf("%d ", cm->tipo_parametros[i]);
		}
		printf("(0 - int / 1 - float / 2 - string)\n\n");
	}else if (strlen(cm->comando)<=0 && i_n == 0)
	{
		printf("Ainda nao foi inserido nenhum comando\n");
	}
}


int dell_comando(COMANDO cm[],HISTORICOS *hs, int i_n, int *cmd)	//	i_n => posiÃ§Ã£o a ser excluida
{
	int i,m,std;
	printf("Apagar o comando %s?...(S=1;N=0)\n", cm[i_n].comando);
	fscanf(stdin,"%d",&m);
	switch(m)
	{
		case 1:		//	Exclui comandos
			hs->usos[i_n] = 0;
			for (i = i_n; i < *cmd; ++i)
			{
				strcpy(cm[i_n].comando,cm[i_n +1].comando);
				cm[i_n].n_parametros = cm[i_n +1].n_parametros;
			}
			strcpy(cm[i].comando,"");
			cm[i].n_parametros = 0;
			printf("Apagado\n");
			std = 1;
		break;
		case 0:
			printf("Cancelado\n");
			std = 0;
		break;
		default:
			printf("Erro\n");
			std = 0;
		break;
	}
	return std;
}
void	executar(COMANDO cm[],	HISTORICOS *hs)
{
	int i,i_s,i_c,i_n,i_e;
	int e, r, n;
	double dbl;
	int ok = 0;
	int zeros[N_COMANDOS];
	char par[PAR];
	char c[N];	
	char p[N_PARAMETROS_MAXIMOS][N];	
	strcpy(c,"");	
	strcpy(par,"");	
	for (i = 0; i < N_PARAMETROS_MAXIMOS; ++i)
	{
		strcpy(p[i],"");
	}
	printf("Qual o comando a executar?\n");
	clean_stdin();
	fgets(par,N,stdin);	
	par[strlen(par)-1] = '\0'; 	
	for (i = 0, i_s = 0, i_n = 0,i_e = 0,i_c = 0, ok = 0; i < PAR; ++i) 
	{
		if (ok == 1)
		{
			p[i_e][i_c] = par[i];
			
			i_c++;
			if (par[i + 1] == ' ')
			{
				ok = 0;
				p[i_e][i_c] = '\0';
				i_e++;
				i_c = 0;
			}
		}else
		{
		
		}
		if (par[i] == ' ')
		{
			i_s++;
			zeros[i_n] = i;
			i_n++;
			if (i_s == 1)
			{
				c[i] = '\0';
			}
			ok = 1;
		}
		if (i_s == 0)
		{
			c[i] = par[i];	
		}
		if (par[i] == '\0')
		{
			c[i] = '\0';
			zeros[i_n] = i;
			p[i_e][i_c+1] = '\0';
			break;
		}
	}

	for (i = 0; i < N_COMANDOS; ++i)
	{
		if (strcmp(c,cm[i].comando)== 0)
		{
			hs->usos[i]++;
			break;
		}else
		{
			if (i == N_COMANDOS-1)
			{
				printf("Erro\n");
				hs->operacoes_erros[0]++;
				return;
			}
		}
	}

	if (i_s < cm[i].n_parametros)
	{
		printf("Erro\n");
		hs->operacoes_erros[1]++;
		return;
	}
																//verificação dos parâmetros
	for (i_n = 0,i_e = 0; i_n < cm[i].n_parametros; ++i_n)
	{
		r = sscanf(p[i_n], "%d%n", &e, &n);
		if(r == 1 && n == strlen(p[i_n])) {
		    r = 0;
		}else
		{
			r = sscanf(p[i_n], "%lf", &dbl);
			if(r == 1) {
				r = 1;
			}else
			{
				r = 2;
			}
		}
		
		
		switch(cm[i].tipo_parametros[i_n])
		{
			case 0:
				if (r == 0)
				{
				}else
				{
					printf("Erro\n");
					i_n = cm[i].n_parametros;
					hs->operacoes_erros[2]++;
					break;
				}
			break;
			case 1:
				if (r == 1)
				{
				}else
				{
					printf("Erro\n");
					i_n = cm[i].n_parametros;
					hs->operacoes_erros[2]++;
					break;
				}		

			break;
			case 2:
				if (r == 2)
				{
				}else
				{
					printf("Erro\n");
					i_n = cm[i].n_parametros;
					hs->operacoes_erros[2]++;
					break;
				}	
			break;
		}
		if (i_n == cm[i].n_parametros - 1)
		{
			printf("Comando %s executado com sucesso\n", par);
			hs->operacoes_sem_erro++;
			if (cm->n_parametros < i_s)
			{
				hs->n_com_parametros_opc++;
			}
		}
	}
	if (cm[i].n_parametros == 0)	
		{
			printf("Comando %s executado com sucesso\n", par);
			hs->operacoes_sem_erro++;
			if (cm->n_parametros < i_s)
			{
				hs->n_com_parametros_opc++;
			}
		}
}

void	estatisticas(COMANDO cm[],HISTORICOS *hs, int cmd)
{
	int i;
	printf("Comandos executados sem erro: %d\n", hs->operacoes_sem_erro);
	printf("Comandos executados com erro total: %d\n",hs->operacoes_erros[0]);
	printf("Comandos executados com erro no numero incorreto de paramentros obrigatorios: %d\n",hs->operacoes_erros[1]);
	printf("Comandos executados com erro de tipo de parametro: %d\n",hs->operacoes_erros[2]);
	printf("UltilizaÃ§Ã£o dos comandos:\n");
	for (i = 0; i < cmd; ++i)
	{
		printf("	%s, Usada %d vezes.\n", cm[i].comando,hs->usos[i]);
	}
	printf("\n");
}

void	carregar(char nome[], COMANDO cm[],HISTORICOS *hs, int *cmd)
{
	FILE *fp;
	fp = fopen(nome,"rb");

	fread(cmd,sizeof(int),1,fp);
	fread(cm,sizeof(COMANDO),*cmd,fp);
	fread(hs,sizeof(HISTORICOS),1,fp);
	fclose(fp);
}

void	guardar(char nome[], COMANDO cm[],HISTORICOS *hs, int cmd)
{
	int i;
	FILE *fp;
	fp = fopen(nome,"wb");
	fwrite(&cmd,sizeof(int),1,fp);
	fwrite(cm,sizeof(COMANDO),cmd,fp);
	fwrite(hs,sizeof(HISTORICOS),1,fp);
	fclose(fp);
	printf("%d\n", cmd);
}

int main(int argc, char const *argv[])
{
	int exit = 0;
	int std = 0;
	int menu = 1; 
	int cmd = 0;	
	int m;
	int ok; 
	int i; 
	char nome_ficheiro[N];
	strcpy(nome_ficheiro,"TP2.txt");
	COMANDO comandos[N_COMANDOS];	
	HISTORICOS historico;
	historico.operacoes_sem_erro = 0;
	historico.n_com_parametros_opc = 0;
	for (i = 0; i < N_COMANDOS; ++i) 
	{
		strcpy(comandos[i].comando,"");
		comandos[i].n_parametros = 0;
		historico.usos[i]=0;
	}
	for (i = 0; i < N_ERROS; ++i)
	{
		historico.operacoes_erros[i] = 0;
	}
	carregar (nome_ficheiro,comandos,&historico, &cmd);
	do
	{
		switch(menu)
		{
			case 1: 
			printf("Editar\n|");
			printf("1. Executar Comandos\n|");
			printf("2. Criar/Apagar Comandos\n|");
			printf("3. Ver Comandos\n|");
			printf("0. Sair\n");
			scanf("%d", &m);
			switch(m)
			{
				system("cls");
				case 1:
				menu = 2;
				break;
				case 2:
				menu = 3;
				break;
				case 3:
				menu = 4;
				break;
				case 0:
				menu = 0;
				break;
				default:
				printf("Erro\n");
			}
			break; 	
			case 2:
			system("cls");
			printf("Executar\n");
			printf("1 - Executar.\n");
			printf("2 - Estatisticas\n");
			printf("0 - Voltar.\n");
			scanf("%d", &m);
			switch(m)
			{
				case 1: 
				
				printf("Lista de comandos inseridos:\n\n");
				for (i = 0; i < cmd; ++i)	
				{
					lista(&comandos[i],i);	
				}
				executar(comandos,&historico);
				break;
				
				case 2:
				
				printf("Historial de comandos \n\n");

				estatisticas(comandos,&historico,cmd);
				system("pause");
				break;

				case 0:
				system("cls");
				menu = 1;
				break;
				default:
				printf("O comando %d ainda nao foi inserido.\n", m);
			}
			break;
			case 3: 
			system("cls");
			printf("Editar comandos\n");
			printf("1 - Novo comando\n");
			printf("2 - Apagar comando\n");
			printf("0 - Voltar.\n");	
			scanf("%d", &m);
			switch(m)
			{
				case 1: 
				clean_stdin();
					for (i = 0; i < N_COMANDOS; ++i)
					{
						if (strlen(comandos[i].comando)==0)
						{
							std = inserir(&comandos[i]); 
							if ( std == 1)
							{
								printf("Comando %s inserido\n", comandos[i].comando);
								cmd++;
								;
							}else if (std == 0)
							{
								printf("Erro\n");
								--i; 
							}
						}
					}
				break;
				
				case 2: 
				clean_stdin();
				int e;
				if (cmd > 0 )
				{
					for (i = 0; i < cmd; ++i)	
					{
						lista(&comandos[i],i);	
					}
					if (cmd != 0)
					{
						printf("\nQual o numero do comando deseja excluir?\n");
						fscanf(stdin,"%d",&e);
						std = dell_comando(comandos,&historico,e-1,&cmd);
						if (std == 1)	
						{
							cmd--;
						}
					}			
				}else
				{
					printf("Ainda nao foi inserido nenhum comando\n");
				}
					
				break;
				
				case 0:
					system("cls");
					menu = 1;
				break;
			}
			break;
			case 4:
			system("cls");
			printf("Estatistica\n\n");	
			printf("Comandos inseridos:\n\n");
			for (i = 0; i < cmd; ++i)	
			{
				lista(&comandos[i],i);	
			}
			scanf("%d", &m);
			switch(m)
			{
				case 0:
				system("cls");
				menu = 1;
				break;
				default:
				printf("Erro\n");
			}
			break;

			case 5: 
			while(ok = 0);
			break;
			case 0:
			guardar(nome_ficheiro,comandos,&historico,cmd);
			exit = 1;
			break;
		}
	}
	while(exit == 0);
}

