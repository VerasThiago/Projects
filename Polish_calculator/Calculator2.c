#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

char pilha[1000];
int topo = -1;
int numeros[1000], pos = -1;
char expressao[1000];
char posfixo[1000];
int pilha_r[1000], topo_r = -1;

void push(char num){
    pilha[++topo] = num;
}

char pop(){
    if(topo == -1) return printf("ESTA VAZIA\n");
    return pilha[topo--];
}

char check(){
    return pilha[topo];
}

void esvazia_pilha(){
    topo = -1;
}

void push_r(int num){
    pilha_r[++topo_r] = num;
}

int pop_r(){
    if(topo_r == -1) return -1;
    return pilha_r[topo_r--];
}
int check_r(){
    return pilha_r[topo_r];
}


void ler(){
	expressao[0] = '(';
    scanf(" %[^\n]s", expressao+1);
    int N = strlen(expressao);
    expressao[N] = ')';
}


 bool validar(){ /*((a+b)*c+(d+e)/(f+g)+h)/i*/
    bool aux=true;
    int N = strlen(expressao);
    int i, x=0, y=0;
    for(i=1;i<N-1;i++){
        if(expressao[i]=='('){
            if(expressao[i-1] != '(' && isalnum(expressao[i-1])){
               
                aux = false;
                break;
            }
            x++;
        }    
            
        else if( expressao[i] == ')'){
            if(expressao[i+1] != ')' && isalnum(expressao[i+1])){
              
                aux = false;
                break;
            }
            y++;
        } 
            
        else if(expressao[i]=='+' || expressao[i]=='-' || expressao[i]=='/' || expressao[i] == '*'){
            int s = i+1;
            
            while(expressao[s] == '(' && s != N-1) s++;
               
            if(s == N-1 || !isalnum(expressao[s])){
             
                aux = false;
                break;
            }
            s = i-1;
            while(expressao[s] == ')' && s != 0) s--;
            if(s == -1 || !isalnum(expressao[s])){
               
                aux = false;
                break;
            }
        }  
        else if(!isalnum(expressao[i])){
              
                aux=false;
                break;
        }
    }
    if(y!=x) aux = false;
    
    return aux;
}

void to_numbers(char infixo[]){
	int i, k = -1;
	char aux[1000];
	for( i = 0 ; infixo[i] != '\0'; ++i){
		if(isdigit(infixo[i])){
			aux[++k] = infixo[i];
		}
		else if(k>= 0){
			aux[++k] = '\0';
			numeros[++pos] = atoi(aux);
			k = -1;
		}
	}

}

void in2pos(char infixo[]){
    int i, l = 0;
    char aux;
    bool ok;
    for( i = 0 ; infixo[i] != '\0'; ++i){
        switch(infixo[i]){
            case '(':
                push(infixo[i]);
                break;
            case ')':
                ok = false;
                while( (aux = check()) != '(' ){
                    printf("%c ", aux);
                    posfixo[l++] = aux;
                    pop();
                    ok = true;
                }
                if(ok) pop();
                break;
                
            case '+':
            case '-':
                while( (aux = check()) != '(' ){
                    printf("%c ", aux);
                    posfixo[l++] = aux;
                    pop();
                }    
                push(infixo[i]);
                break;
                
            case '*':
            case '/':
                while( (aux = check()) != '(' && aux != '+' && aux != '-'){
                    printf("%c ", aux);
                    posfixo[l++] = aux;
                    pop();
                } 
                push(infixo[i]);
                break;
                
            default:{
            	if(!isdigit(infixo[i])){
	            	printf("%c ",infixo[i]);
	            	posfixo[l++] = infixo[i];
	            }
	            else{
	            	while(isdigit(infixo[i])){
	            	  printf("%c",infixo[i]);
	            	  posfixo[l++] = infixo[i];
	            	  i++;	            	  
	            	}
	            	printf(" ");
	            	i--; 
	            }
        	}
        }
    }
    printf("\n");
}


void resolve(){
	int i, k = 0;
	char aux[1000];
	for(i = 0 ; posfixo[i] != '\0'; ++i){
		if(isdigit(posfixo[i])){
			push_r(numeros[k++]);
			sprintf(aux,"%d", numeros[k-1]);
			i += strlen(aux) -1;
		}
		else{
			int aux2 = pop_r();
			int aux3 = pop_r();
			switch(posfixo[i]){
			    case '+':
			        aux3 += aux2;
			        push_r(aux3);
			        break;
			    case '-':
			        aux3 -= aux2;
			        push_r(aux3);
			        break;
			    case '*':
			        aux3 *= aux2;
			        push_r(aux3);
			        break;
	            case '/':
			        aux3 /= aux2;
			        push_r(aux3);
			        break;
			}
		}
	}
	printf("RESPOSTA:  %d\n", check_r());

}
void print(char expressao[]){
    
   
    if(!validar()) printf("\n--FUNCAO INVALIDA--\n\n"); 
    else{
        int i;
        to_numbers(expressao);
        bool aux=false;
    	if(pos != -1){	
    		printf("TEMOS OS NUMEROS:  ");
    		aux = true;
    	    for(i = 0 ; i <= pos ; i++)
    	    	printf("%d ",numeros[i]);
        	printf("\n");
        }
        else printf("NAO TEMOS NUMEROS\n");
        printf("INFIXO:  ");
        for(i = 1 ; i < strlen(expressao)-1; i++)
        	printf("%c", expressao[i]);
        printf("\nPOSFIXO:  ");
        in2pos(expressao);
        if(aux) resolve();
    }      

}



int main(){
    printf("Digite uma espressao válida:  -  i.e: (2+3)*5  -\n");
    ler();
    print(expressao);
    return 0;
}


/*
a-b	                    ab-
a-b*c	                abc*-
(a-b)*c	                ab-c*
a*(b+c)*(d-g)*h	        abc+*dg-*h*
*/