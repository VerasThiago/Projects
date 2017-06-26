/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 2/2016
Aluno(a): < Thiago Veras Machado   >
Matricula: < 16/0146682 >
Turma: A
Versão do compilador: <5.4.0>
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define ANIMACAO_DELAY 86
#define MEDIA_TEMPO 60
#define ERRO_TEMPO 20
#define RAND(M, E) (M + (rand()%(2*E + 1) - E))
#define MAX 10000000000000
#define BOLD		"\x1b[1m"
#define VERMELHO	"\x1B[31m"
#define NORMAL 		"\x1B[0m"
#define AZUL		"\x1B[34m"
#define AMARELO		"\x1B[33m"


char restaurante[17][41];

int  Cont_Salao = 0, Cont_Varanda = 0,Mesa_Salao[13], Mesa_Varanda[5],  NumMesa;
long long int tempo_estadia[16];

void Sleep(int ms) {
	clock_t limit = clock() + ms*(CLOCKS_PER_SEC/1000);
	while (limit > clock()) {}
}
void Clear(){

    system("clear");
}
void Ler_arquivo(){/*Le aqrquivo  da matriz*/
    int i;
    FILE *fp;
    fp = fopen("restaurante.txt", "r");
    for(i=0;i<17;i++){
        fscanf(fp, "%[^\n]%*c", &restaurante[i][0]);
    }
    fclose(fp);

}
void Mostrar_arquivo(){/*Printa a matriz*/
    int i, j;
    printf("\t\t\t%s%sTHIAGO'S SERVE YOUR SELF SELF SERVICE\n\n%s",BOLD,AMARELO, NORMAL);
    for(i=0;i<17;i++){
        for(j=0;j<41;j++){
            printf("%c", restaurante[i][j]);
        if(j==40){
                printf("\n");
            }
       }
    }
   	CheckLotado();

}


void Mostrar_arquivoAnimacao(){

	/*Printar as animacoes sem printar se esta lotado ou nao,
	       						pois estava aparecendo 2 vezes a msg de lotado*/
    int i, j;
     printf("\t\t\t%s%sTHIAGO'S SERVE YOUR SELF SELF SERVICE\n\n%s",BOLD,AMARELO, NORMAL);
    for(i=0;i<17;i++){
        for(j=0;j<41;j++){
            printf("%c", restaurante[i][j]);
        if(j==40){
                printf("\n");
            }
       }
    }
}

int EscolherMSalao(char Continuar2, int Client){/*Atribui automaticamente a primeira mesa que esta desocupada*/
	int i, value = -1;
	if(Continuar2 == 'N'){
		for(i = 0; i < 12; i++){

			if(Mesa_Salao[i] == 0){
				Mesa_Salao[i] = Client;
				NumMesa = i;
				Cont_Salao++;
				break;
			}
		}
	}
	else{
		/*Nao precisa dar um NumMesa-- pois a funcao checkmesa ok ja deu para mim*/
		Mesa_Salao[NumMesa] = Client;
		Cont_Salao++;
	}
}

int EscolherMVaranda(char Continuar2, int Client){/* Igual o de cima so que para varanda*/
	int i, value = -1;
	if(Continuar2 == 'N'){
		for(i = 0; i < 4; i++)
			if(Mesa_Varanda[i] == 0){
				Mesa_Varanda[i] = Client;
				NumMesa = i;
				Cont_Varanda++;
				break;
			}
	}
	else{
		Mesa_Varanda[NumMesa] = Client;
		Cont_Varanda++;
	}
}
void Animacao_desfilar(){
int flag = 1;
 	/*O boneco anda para frente e para de frente para a parede,
 	pois indendente de qual mesa e qual corredor que ele va, ele deve andar para frente primeiramente*/

    int i, n=36;

    for(i=0;i<7;i++){

        if(flag == 1){
        	restaurante[9][n] = 'O';
    		flag = 2;
    	}
    	else{
    		restaurante[9][n] = '0';
    		flag = 1;
    	}
        if(i > 0){
            restaurante[9][n+1] = ' ';
        }
       	Clear();
        Mostrar_arquivoAnimacao();
		Sleep(ANIMACAO_DELAY);
        n--;
    }
    restaurante[9][n+1] = ' ';

}

void Animacao_mesa_varanda(){
	/*Boneco anda para baixo e para na
	porta do corredor da varanda*/
	int i , n = 10, flag = 1;


	for(i=0;i<6;i++){
        if(flag == 1){
        	restaurante[n][30] = 'O';
    		flag = 2;
    	}
    	else{
    		restaurante[n][30] = '0';
    		flag = 1;
    	}
        if(i > 0){
            restaurante[n-1][30] = ' ';
        }
       	Clear();
        Mostrar_arquivoAnimacao();
		Sleep(ANIMACAO_DELAY);
	        n++;
    }
     restaurante[n-1][30] = ' ';

}
void Animacao_mesa_salao (int mesa){
	int i , n = 9, j = 6, flag = 1;

	if(mesa > 7){ /*Como a mesa e maior que 7, ele deve descer ate o corredor de baixo*/

		n++;/*Comeca na linha de baixo, pois o boneco ira descer*/
		for(i=0;i<2;i++){
	         	if(flag == 1){
		        	restaurante[n][30] = 'O';
		    		flag = 2;
		    	}
		    	else{
		    		restaurante[n][30] = '0';
		    		flag = 1;
		    	}

	        if(i > 0){
	            restaurante[n-1][30] = ' ';
	        }
	       	Clear();
	        Mostrar_arquivoAnimacao();
			Sleep(ANIMACAO_DELAY);
	        n++;

    	}
     		restaurante[n-1][30] = ' ';
	}
	else{/*O boneco sobe*/
		n--;/*Comeca na linha de cima, pois o boneco ira subir*/
		if(mesa > 3)
			j = 2; /*So precisa subir 2 vezes para chegar no corredor de mesas > 3*/
		for(i=0;i<j;i++){


			if(flag == 1){
	        	restaurante[n][30] = 'O';
	    		flag = 2;
	    	}
	    	else{
	    		restaurante[n][30] = '0';
	    		flag = 1;
	    	}

	        if(i > 0){/*Comeca apagar depois que andou uma vez, se nao apaga a porta*/
	            restaurante[n+1][30] = ' ';
	        }
	       	Clear();
	        Mostrar_arquivoAnimacao();
			Sleep(ANIMACAO_DELAY);
	        n--;

    	}
     		restaurante[n+1][30] = ' '; /*Limpa o boneco depois da animacao*/
	}

}
void Animacao_mesa_varanda_corredor(int mesa){ /*Boneco entra no carredor da varanda*/
	int i, n = 30, flag = 1;
	for(i=0;i<13;i++){

         if(flag == 1){
        	restaurante[15][n] = 'O';
    		flag = 2;
    	}
    	else{
    		restaurante[15][n] = '0';
    		flag = 1;
    	}
        if(i > 0){
            restaurante[15][n+1] = ' ';
        }
       	Clear();
        Mostrar_arquivoAnimacao();
		Sleep(ANIMACAO_DELAY);
        n--;
        if( i == 12 - (mesa * 3) ) /*Formula que deduzi para descobrir se o boneco
                                   esta em frente a mesa desejada, ai ele para de animar*/
        	break;
    }
    restaurante[15][n+1] = ' '; /*Limpa o boneco*/

}
void Animacao_mesa_salao_corredor(int mesa){/*Mesmo esquema da varanda*/
	int i, n = 30, k = 3, flag = 1;

	if(mesa > 7){
		k = 11;
		mesa -= 8;
		for(i=0;i<13;i++){

	         if(flag == 1){
	        	restaurante[k][n] = 'O';
	    		flag = 2;
	    	}
	    	else{
	    		restaurante[k][n] = '0';
	    		flag = 1;
	    	}
	        if(i > 0){
	            restaurante[k][n+1] = ' ';
	        }
	       	Clear();
	        Mostrar_arquivoAnimacao();
			Sleep(ANIMACAO_DELAY);
	        n--;
	        if( i == 12 - (mesa * 3) )
	        	break;
	    }
	    restaurante[k][n+1] = ' ';
	}
	else{
		if (mesa > 3){
			k =  7;
			mesa -=4;
		}

		for(i=0;i<13;i++){

	        if(flag == 1){
	        	restaurante[k][n] = 'O';
	    		flag = 2;
	    	}
	    	else{
	    		restaurante[k][n] = '0';
	    		flag = 1;
	    	}
	        if(i > 0){
	            restaurante[k][n+1] = ' ';
	        }
	       	Clear();
	        Mostrar_arquivoAnimacao();
			Sleep(ANIMACAO_DELAY);
	        n--;
	        if( i == 12 - (mesa * 3) )
	        	break;
	    }
	    restaurante[k][n+1] = ' ';
	}

}
int CheckLotado(){
	int checkS, checkV;
	checkS = checkV = 0;
	if(Cont_Salao == 12) /*Se ha 12 pessoas no salao, CheckS (CheckSalao) eh true*/
		checkS = 1;
	if(Cont_Varanda == 4)/*Mesmo para varanda*/
		checkV = 1;

	if(checkS == 1 && checkV == 1){/*Ambos full*/
		printf("%s\n\n\n\t----------------------TUDO LOTADO----------------------%s", VERMELHO, NORMAL);
		return 1;
	}
	else if (checkS == 1 && checkV == 0){
		printf("%s\n\n\n\t----------------------O SALAO ESTA LOTADO----------------------%s", VERMELHO, NORMAL);
		return 2;
	}
	else if (checkS == 0 && checkV == 1){
		printf("%s\n\n\n\t----------------------A VARANDA ESTA LOTADA----------------------%s", VERMELHO, NORMAL);
		return 3;
	}
	 return -1;

}

int ValidarTipoMesa(int checkM, int local){
	/*Precisa do retorno da funcao de cima,
    no qual 2 significa que Salao esta cheio e 3 que a Varanda esta cheia*/

	if(checkM == 2 && local == 1)/*Salao esta cheio e o cliente escolheu Salao*/
		return 1;
	else if(checkM == 3 && local == 2)/*Analogo para Varanda*/
		return 2;

}
int ZerarMesas(int Mesa_Salao[],int Mesa_Varanda[]){/*Todas as mesas comecas com 0 pessoas*/
	int i;
	for(i = 0 ; i < 12 ; i++){
		Mesa_Salao[i] = 0;
			if(i < 4)
				Mesa_Varanda[i] = 0;
	}

	for(i=0;i<20;i++){
        tempo_estadia[i] = MAX;
    }
	Mesa_Varanda[4] = 1;/*Esse trecho esta relacionado ao checkar se a mesa escolinha esta vazia*/
	Mesa_Salao[12] = 1;/*Explicacão melhor na funcao*/

}
char CompContinuar(char Continuar){/*While enquanto nao digitar s ou n*/
    while(Continuar != 'S' && Continuar != 's' && Continuar != 'N' && Continuar != 'n'){
        Clear();
        Mostrar_arquivo();
        printf("\n\n\n\tCARACTER INVALIDO, DIGITE NOVAMENTE (S/N) : ");
        scanf(" %c", &Continuar);
    }
    return toupper(Continuar);

}
int CompLocal(int Local){/*While enquanto nao digitar os 2 locais possiveis*/
	while(Local != 1 && Local != 2 ){
        Clear();
        Mostrar_arquivo();
        printf("\n\n\n\tLOCAL INVALIDO, DIGITE NOVAMENTE (1/2) : ");
        scanf("%d", &Local);
    }
    return Local;

}
int CompClient(int Client){
	/*While enquanto o numero de pessoas que vao sentar
    nao estao no intervalo corretor*/
	while(Client<1 || Client>4){
	 	Clear();
		Mostrar_arquivo();
        printf("\n\n\n\tNUMERO INVALIDO, DIGITE NOVAMENTE (1 ~ 4) : ");
        scanf("%d", &Client);
    }
	return Client;

}
int CompMesa(int NumMesa , int Local){
	if(Local == 2){/*Cliente escolheu uma mesa na varanda mas nao escolheu
						um numero de mesa existente*/
		while(NumMesa<1 || NumMesa>4){
		 	Clear();
			Mostrar_arquivo();
	        printf("\n\n\n\tMESA INEXISTENTE, DIGITE NOVAMENTE (1 ~ 4) : ");
	        scanf("%d", &NumMesa);
	    }
    	return NumMesa;
	}
	else{
		while(NumMesa<1 || NumMesa>12){/*Analogo para as mesas do salao*/
		 	Clear();
			Mostrar_arquivo();
	        printf("\n\n\n\tMESA INEXISTENTE, DIGITE NOVAMENTE (1 ~ 12) : ");
	        scanf("%d", &NumMesa);
	    }
    	return NumMesa;
	}

}
int Menu(){/*Printa o menu*/
	Clear();
	Mostrar_arquivo();
	printf("\n\n\n\tDESEJA EDITAR O CONTROLE DO RESTURANTE (S/N) ?: ");

}
int Chamadamesa(){
	Clear();
	Mostrar_arquivo();
	printf("\n\n\n\tSO POSSUIMOS MESA PARA ATE 4 PESSOAS\n\n\n\tDIGITE O NRO DE PESSOAS: ");

}
int Chamadalocal(){
	Clear();
	Mostrar_arquivo();
	printf("\n\n\n\tDESEJA MESA NA AREA DO SALAO OU VARANDA  (1/2) ?: ");

}
void ColocarmesaS(int mesa , int pessoas){
	int i = 1, aux = mesa;

	if(mesa >= 4 && mesa <= 7)
		mesa -=4;
	else if ( mesa > 7)
		mesa -=8;

    restaurante[i + (4 * (aux / 4)) ][17 + (mesa * 3)] = '*';
    restaurante[i + (4 * (aux / 4)) ][18 + (mesa * 3)] = '-';
    restaurante[i + 1 + (4 * (aux / 4)) ][17 + (mesa * 3)] = '-';
    restaurante[i + 1 + (4 * (aux / 4)) ][18 + (mesa * 3)] = '-';

    if(pessoas>1)
        restaurante[i + (4 * (aux / 4)) ][18 + (mesa * 3)] = '*';

    if(pessoas>2)
        restaurante[i + 1 + (4 * (aux / 4)) ][17 + (mesa * 3)] = '*';

    if(pessoas>3)
        restaurante[i + 1 + (4 * (aux / 4)) ][18 + (mesa * 3)] = '*';
}

void ColocarmesaV(int mesa, int pessoas){
    restaurante[13][17 + (mesa * 3)] = '*';
    restaurante[13][18 + (mesa * 3)] = '-';
    restaurante[14][17 + (mesa * 3)] = '-';
    restaurante[14][18 + (mesa * 3)] = '-';

	if(pessoas >1)
	    restaurante[13][18 + (mesa * 3)] = '*';

	if(pessoas>2)
	    restaurante[14][17 + (mesa * 3)] = '*';

	if(pessoas>3)
	    restaurante[14][18 + (mesa * 3)] = '*';

}
void Salaocheio(){
	Clear();
	Mostrar_arquivoAnimacao();
	printf("\n\n\n\tSALAO ESTA CHEIO, DESEJA MUDAR DE LOCAL PARA VARANDA (S/N) ?: ");

}
void Varandacheia(){
	Clear();
	Mostrar_arquivoAnimacao();
	printf("\n\n\n\tVARANDA ESTA CHEIA, DESEJA MUDAR DE LOCAL PARA O SALAO (S/N) ?: ");

}
int MenuEscolhaMesa_Varanda(){
	/*Substitui os espacos para enumerar as mesas da Varanda,facilitando a escolha do cliente*/
	restaurante[15][17] = restaurante[15][20] = restaurante[15][23] = restaurante[15][26] ='0';
	restaurante[15][18] = '1';
	restaurante[15][21] = '2';
	restaurante[15][24] = '3';
	restaurante[15][27] = '4';
	Clear();
	Mostrar_arquivo();
	printf("\n\n\n\tDIGITE O NUMERO DA MESA QUE DESEJA SENTAR: ");

}
int MenuEscolhaMesa_Salao(){
	/*Analogo para as mesas do Salao*/
	restaurante[3][17] = restaurante[3][20] = restaurante[3][23] = restaurante[3][26] = restaurante[7][17] = restaurante[7][20] = restaurante[7][23] = restaurante[7][26] = restaurante[11][17] = restaurante[11][21] = '0';
	restaurante[3][18] = restaurante[11][20] = restaurante[11][23] = restaurante[11][24] = restaurante[11][26] = '1';
	restaurante[3][21] = restaurante[11][27] = '2';
	restaurante[3][24] = '3';
	restaurante[3][27] = '4';
	restaurante[7][18] = '5';
	restaurante[7][21] = '6';
	restaurante[7][24] = '7';
	restaurante[7][27] = '8';
	restaurante[11][18] = '9';
	Clear();
	Mostrar_arquivo();
	printf("\n\n\n\tDIGITE O NUMERO DA MESA QUE DESEJA SENTAR: ");

}
int LimparMenuEscola(){
	/*Apos enumerar as mesas, limpar os numeros para a animacão*/
	int i , j;
	for(i = 3; i <= 15 ; i = i + 4){
		for( j = 17; j <= 27; j++){
			restaurante[i][j] = ' ';
		}
	}
}
int Chamadaopcaomesa(){
	Clear();
	Mostrar_arquivoAnimacao();
	printf("\n\n\n\tDESEJA ESCOLHER QUAL MESA SENTAR (S/N) ?: ");

}
int Checkmesaok(int NumMesa, int Local){/*Parte mais abstrata do programa*/
/*Checa se a mesa escolhida esta dentro do intervalo de mesas existentes e
	se a mesa escolhida esta ocupada ou nao*/
	int flag1 = 1;
	NumMesa--;/*O numero da mesa esta de 1 ~ 12 e como o vetor vai de 0 a 11,
	diminuí uma posicão para realizar as operacoes corretamente*/
	if(Local == 1){
		if (Mesa_Salao[NumMesa] != 0){/*Checa se esta vazio*/
			while(Mesa_Salao[NumMesa] != 0){/*Enquanto a mesa escolhida nao estiver vazia*/
				if(flag1 == 1){/*Comeca printando que esta ocupada pois essa funcao foi Chamada depois que foi corrigido
				                pela primeira vez se o numero estava dentro do intervalo (funcao "CompMesa"*/
					Clear();
					Mostrar_arquivo();
					printf("\n\n\n\tESTA MESA ESTA OCUPADA, DIGITE O NUMERO DE UMA MESA QUE ESTEJA VAZIA: ");
				}
				flag1 = 1;/*Reseta a flag para printar que esta ocupada caso necessario*/
				scanf("%d", &NumMesa);
				if(NumMesa > 12 || NumMesa < 1){/*Caso de mesa inexistente*/
					Clear();
					Mostrar_arquivo();
	        		printf("\n\n\n\tMESA INEXISTENTE, DIGITE NOVAMENTE (1 ~ 12) : ");
	        		flag1 = 0;/*Seta ambos para zero, a primeira flag para nao printar que esta ocupada, pois é inexistente e a segundo para nao deixar a posicão da mesa */
	        		/*,para evitar isso, declarei as mesas com uma unidade a mais (Mesa_Salao[13])e na posicão a mais  eu setei como 1 para nao pegar lixo de memoria e nao sair do while*/
	        		NumMesa = 13; /*Mesa sera decrementada e na posicão 12 vale 1, logo nao sai do while*/
				}
				NumMesa--;
			}
		}
		return NumMesa;

	}
	else{/*Analogo para parte de cima*/
		if (Mesa_Varanda[NumMesa] != 0){
			while(Mesa_Varanda[NumMesa] != 0){
				if(flag1 == 1){
					Clear();
					Mostrar_arquivo();
					printf("\n\n\n\tESTA MESA ESTA OCUPADA, DIGITE O NUMERO DE UMA MESA QUE ESTEJA VAZIA: ");
				}

				flag1 = 1;

				scanf("%d", &NumMesa);

				if(NumMesa > 4 || NumMesa < 1){
					Clear();
					Mostrar_arquivo();
	        		printf("\n\n\n\tMESA INEXISTENTE, DIGITE NOVAMENTE (1 ~ 4) : ");
	        		flag1 = 0;
	        		NumMesa = 5;
				}
					NumMesa--;
			}
		}
		return NumMesa;
	}

}

void Desocupar(int NumMesa, int Local){ /*verifica se o tempo de estadia foi alcancado e libera os lugares */

    int i = 1, aux, j;
    if(Local == 1){
        tempo_estadia[NumMesa] = time(0) + RAND(MEDIA_TEMPO, ERRO_TEMPO);
    }
    if(Local == 2){
        tempo_estadia[NumMesa+12] = time(0) + RAND(MEDIA_TEMPO, ERRO_TEMPO);
    }
    for(j=0; j <= 16; j++){
        if(time(0) >= tempo_estadia[j]){
        	tempo_estadia[j] = MAX;
        	if(j <= 12){
	            printf("\n\n\n\tA %d MESA DO SALAO FOI DESOCUPADA\n\n", j);
	        	j--;
	           	Mesa_Salao[j] = 0;
	        	aux = j;
	            Sleep(3000);
	           	if(j >= 4 && j <= 7)
					j -=4;
				else if ( j > 7)
					j -=8;

	            restaurante[i + (4 * (aux / 4))][17 + (j * 3)] = '/';
	            restaurante[i + (4 * (aux / 4))][18 + (j * 3)] = '\\';
	            restaurante[i + 1 + (4 * (aux / 4))][17 + (j * 3)] = '\\';
	            restaurante[i + 1 +(4 * (aux / 4))][18 + (j * 3)] = '/';
	           	Cont_Salao --;
	           	Clear();
	            Mostrar_arquivo();
	        }
	        else{
	            tempo_estadia[j] = MAX;
	            printf("\n\n\n\tA %d MESA DA VARANDA FOI DESOCUPADA\n\n", j-12);
	            j-=13;
	            Sleep(3000);
	            restaurante[13][17+( j * 3 )] = '/';
	            restaurante[13][18+( j * 3 )] = '\\';
	            restaurante[14][17+( j * 3 )] = '\\';
	            restaurante[14][18+( j * 3 )] = '/';
	           	Mesa_Varanda[j] = 0;
	           	Cont_Varanda--;
	           	Clear();
	            Mostrar_arquivo();
	        }
        }
    }
}

int main(){

	int checkL, checkM, i, Client, end = 1, stop =1, Local;
	char Continuar, Continuar2;

		srand(time(0));
		ZerarMesas(Mesa_Salao, Mesa_Varanda);
		Ler_arquivo();
		Clear();
		Mostrar_arquivo();

		while(end == 1){/*Esse whule serve para o break do while de dentro nao sair do while de dentro e,
		se acabar o programa( pois como end é sempre 1) ele volta ao comeco do while de dentro,
		a nao ser que ele queira sair, setando end como 0*/

			while( Menu() ){

				scanf(" %c", &Continuar);
				Continuar = CompContinuar(Continuar);

				if(CompContinuar(Continuar) == 'N'){
					end = 0;
					break;
				}

				NumMesa++;
				Desocupar(NumMesa, Local);

				Chamadamesa();
				scanf("%d", &Client);
				Client = CompClient(Client);

				Chamadalocal();
				scanf(" %d", &Local);
				Local = CompLocal(Local);

				Chamadaopcaomesa();
				scanf(" %c", &Continuar2);
				Continuar2 = CompContinuar(Continuar2);

				checkM = CheckLotado();

				if(ValidarTipoMesa(checkM, Local) == 1){
					Clear();
					Salaocheio();
					scanf(" %c", &Continuar);
					Continuar = CompContinuar(Continuar);

					if(CompContinuar(Continuar) == 'N')
						break;
					else
						Local = 2;
				}
				else if(ValidarTipoMesa(checkM, Local) == 2){
					Clear();
					Varandacheia();
					scanf(" %c", &Continuar);
					Continuar = CompContinuar(Continuar);
					if(CompContinuar(Continuar) == 'N')
						break;
					else
						Local = 1;
				}
				if(Local == 1){
					if(Continuar2 == 'N'){
						EscolherMSalao(Continuar2, Client);
						Animacao_desfilar(NumMesa);
						Animacao_mesa_salao(NumMesa);
						Animacao_mesa_salao_corredor(NumMesa);
						Clear();
						ColocarmesaS(NumMesa,Client);
					}
					else{
						MenuEscolhaMesa_Salao();
						scanf("%d", &NumMesa);
						NumMesa = CompMesa(NumMesa, Local);
						NumMesa = Checkmesaok(NumMesa,Local);
						EscolherMSalao(Continuar2, Client);
						LimparMenuEscola();
						Animacao_desfilar(NumMesa);
						Animacao_mesa_salao(NumMesa);
						Animacao_mesa_salao_corredor(NumMesa);
						Clear();
						ColocarmesaS(NumMesa,Client);
					}
				}
				else{
					if(Continuar2 == 'N'){
						EscolherMVaranda(Continuar2, Client);
						Animacao_desfilar(NumMesa);
						Animacao_mesa_varanda(NumMesa);
						Animacao_mesa_varanda_corredor(NumMesa);
						Clear();
						ColocarmesaV(NumMesa,Client);
					}
					else{
						MenuEscolhaMesa_Varanda();
						scanf("%d", &NumMesa);
						NumMesa = CompMesa(NumMesa, Local);
						NumMesa = Checkmesaok(NumMesa,Local);
						LimparMenuEscola();
						EscolherMVaranda(Continuar2, Client);
						Animacao_desfilar(NumMesa);
						Animacao_mesa_varanda(NumMesa);
						Animacao_mesa_varanda_corredor(NumMesa);
						Clear();
						ColocarmesaV(NumMesa,Client);
					}
				}
			}
		}
		Clear();
		printf("\n\n\n\tOBRIGADO E VOLTE SEMPRE!\n\n\n");
		return 0;
}

/*s 1 2 n s 2 2 n s 3 2 n s 4 2 n*/ /*LOTAR TODA VARANDA (SÓ COPIAR E COLAR TUDO DE UMA VEZ)*/
/*s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n s 1 1 n*//*LOTAR TODO SALÃO*/
