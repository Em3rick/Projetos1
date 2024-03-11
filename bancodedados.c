/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <sys/stat.h> /* para usar a fun��o stat */

/* Constantes  */
#define  TAMSTR  	50
#define  ARQUIVO_DE_PRODUTOS 		"ALUNOS.DAT"

/* Tipos de dados pr�-definidos */

/*------------------Lay-out do registro de produtos------------------
+-------------------------------------------------------------------+
|		Codprod					|	Nomeprod  	|	 Custoprod		|
+-------------------------------------------------------------------+
|	C�digo do produto			| 	 Nome do  	|    Valor unit�rio |
| chave prim�ria (autonum�rico)	|    produto  	|	   do produto	|
+-------------------------------------------------------------------+
|		inteiro 				|    string		|		float		|
+-------------------------------------------------------------------+
*/
typedef struct
{
   	int  	Codprod;
   	char 	Nomeprod[TAMSTR];
   	float	Custoprod;
}
registro_produto;

/* Prot�tipos de fun��es */
int 				CalculaRegistrosArq		(void);
registro_produto    captura_produto 		(void);
void  				falha_abrir_arquivo 	(void);
void  				falha_gravar_arquivo 	(void);
void  				falha_ler_arquivo 		(void);
void  				sucesso_gravacao 		(registro_produto R);
void  				descartar 				(registro_produto R);
char  				confirmar 				(registro_produto R);
void  				grava_produto			(registro_produto R);
void 				cadastrar 				(void);
int 				ver_arquivo_existe 		(void);
void  				relatorio_aluno		(void);
int   main ();

/* Fun��es */

int CalculaRegistrosArq(void)
{
	int numero_registros;
	FILE *Arq;
	Arq = fopen (ARQUIVO_DE_PRODUTOS, "r");
	if ( Arq == NULL) /* O arquivo n�o existe */
	   numero_registros = 0;
	else
	{   /* Calcula o tamanho do arquivo */
		if ( fseek (Arq, 0, SEEK_END) ) /* Aqui fseek tenta se posicionar no final do arquivo...*/
		{
           printf("\nERRO ao calcular o tamanho de arquivo!\n");
           getch();
           numero_registros = -1; /* -1 = ERRO GRAV�SSIMO!!!!!!!!!! */
        }
        else
		{   /*...para que ftell 'conte' quantos bytes o arquivo tem */
		    /* Dividindo-se o total de bytes do arquivo pelo tamanho de cada registro */
		    /* tem-se o n�mero de registros do arquivo. */
		    numero_registros =  ftell(Arq) / sizeof (registro_produto);  /* 0 ou mais REGISTROS [OK] */
  	    }
  	    /* Fecha o arquivo */
  	    fclose (Arq);
	}
    /* Para teste: avisa quantos bytes o arquivo tem */
    /*
    printf ("\nO arquivo [%s] tem [%i] registros.", ARQUIVO_DE_PRODUTOS, numero_registros);
    getch();
    */

    /* 'devolve' a quantidade de registros para o programa 'chamador'*/
	return (numero_registros); /* -1, O ou MAIOR QUE ZERO */
}

registro_produto    captura_produto (void)
{
   registro_produto		rprod;
   printf ("\n------------ CADASTRO DE ALUNO -----------------");
   rprod.Codprod = CalculaRegistrosArq() + 1;
   printf ("\n Matr�cula   :  SP000000%i", rprod.Codprod);
   printf ("\n Nome    : "); fflush (stdin); gets(rprod.Nomeprod);
   return (rprod);
}

void  falha_abrir_arquivo (void)
{
	system ("color 4f"); /* Cor do texto branca com fundo vermelho */
	system ("cls");
	printf ("FALHA AO ABRIR [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void  falha_gravar_arquivo (void)
{
	system ("color 4f"); /* Cor do texto branca com fundo vermelho */
	system ("cls");
	printf ("FALHA AO GRAVAR [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void  falha_ler_arquivo (void)
{
	system ("color 4f"); /* Cor do texto branca com fundo vermelho */
	system ("cls");
	printf ("FALHA AO LER [%s]!", ARQUIVO_DE_PRODUTOS);
	getch();
	exit(0);
}

void  falha_falta_produtos (void)
{
	system ("color 4f"); /* Cor do texto branca com fundo vermelho */
	system ("cls");
	printf ("\nFALHA: NAO HA ALUNOS CADASTRADOS EM [%s]!", ARQUIVO_DE_PRODUTOS);
	printf ("\nARQUIVO [%s] INEXISTENTE!", ARQUIVO_DE_PRODUTOS);
	getch();
}

void  sucesso_gravacao (registro_produto R)
{
   system ("color 2f"); /* Cor do texto branca com fundo verde */
   system ("cls");
   printf ("\n\nRegistro [SP00000%d][%s]", R.Codprod, R.Nomeprod);
   printf ("\n gravado com sucesso!\n\n");
   Sleep(200);
}

void  descartar (registro_produto R)
{
   printf ("\n\nRegistro descartado: [SP00000%d][%s]", R.Codprod, R.Nomeprod);
   getch();
}

char  confirmar (registro_produto R)
{
   char opc;
   printf ("\n\n[SP00000%d][%s]", R.Codprod, R.Nomeprod);
   printf ("\n\nConfirma gravacao do registro? [S=sim]");
   fflush (stdin); opc = getche();
   return (opc);
}

void  grava_produto	(registro_produto R)
{
   FILE *A;
   char esc = confirmar(R);
   if ( esc == 'S' || esc == 's')
   {
       A = fopen (ARQUIVO_DE_PRODUTOS, "a");
	   if (A==NULL)
	      falha_abrir_arquivo();
	   else
	   {
	      fwrite (&R, sizeof(R), 1, A);
	      if ( ferror(A) )
	         falha_gravar_arquivo();
	   }
	   fclose(A);
	   sucesso_gravacao(R);
   }
   else
      descartar (R);
}

void cadastrar (void)
{
    char  esc;
    do
	{
        system ("color 70"); /* Cor do texto preta com fundo cinza */
	    system ("cls");
		grava_produto(captura_produto());
		printf ("\nCadastra outro aluno? [S=sim]");
		fflush (stdin); esc = getche();
	}
	while (esc == 'S' || esc == 's');
}

int ver_arquivo_existe (void)
{
  struct stat buffer;
  int exist = stat(ARQUIVO_DE_PRODUTOS, &buffer);
  return exist;
}

void  relatorio_produtos	(void)
{
   FILE *A;
   registro_produto R;

   if (ver_arquivo_existe() == -1)
	   falha_falta_produtos();
   else
   {
		A = fopen (ARQUIVO_DE_PRODUTOS, "r");
   		if (A==NULL)
      		falha_abrir_arquivo();
   		else
   		{
        	system ("color 0e"); /* Cor do texto amarela com fundo preto */
	    	system ("cls");
			printf ("\n-------------------------------------");
        	printf ("\n          ALUNOS CADASTRADOS       ");
        	printf ("\n-------------------------------------");
   	    	while ( !feof(A) )
   	    	{
		    	fread (&R, sizeof(R), 1, A);
            	if ( ferror(A) )
	           		falha_ler_arquivo();
	        	if ( !feof(A) )
	           		printf ("\nSP00000%d %s", R.Codprod, R.Nomeprod);
	   		}
	   	fclose(A);
   		}
   		printf ("\n-------------------------------------\n");
   		printf ("\nPressione qualquer tecla para retornar ao menu principal.");
   		getch();
   }
}

/* Corpo do programa */
int 	main	()
{
  char  opc;
  /* O programa permanece em looping enquanto n�o for selecionada a op��o SAIR */
  do
  {
    /* Mostra o menu de op��es */
    do
	{
        system ("color e0"); /* Cor do texto amarela com fundo preto */
	    system ("cls");
	    printf ("\n------------- CADASTRO DE ALUNO ------------");
	    printf ("\n            c => Cadastrar Alunos                     ");
	    printf ("\n            r => Relatorio de Alunos               ");
	    printf ("\n            s => SAIR                                   ");
	    printf ("\n--------------------------------------------------------");
	    printf ("\n            Selecione a opcao desejada: ");
	    fflush (stdin); opc = getche();
	}
	while (opc != 'S' && opc != 's' &&
	       opc != 'C' && opc != 'c' &&
		   opc != 'R' && opc != 'r' );

	/* Dependendo da op��o, executa o cadastro ou mostra o relat�rio ou encerra o programa */
	switch (opc)
	{
		case 'C': case 'c': cadastrar();			break;
		case 'R': case 'r': relatorio_produtos(); 	break;
		case 'S': case 's': exit(0); 				break;
	}
  }
  while ( opc != 'S' && opc != 's');
  return (0);
}
