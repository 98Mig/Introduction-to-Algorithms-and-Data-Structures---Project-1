//86399 - Daniel Alexandre Cacho Marques Goncalves //
//86482 - Miguel Antonio Oliveira Rocha//

//Bibliotecas//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Constantes//

#define PARTICIPANTS 1000 //Tamanho maximo da lista de participantes//
#define MESSAGES 10000 //Numero de mensagens que o forum permite//
#define TAMANHO 140 //Tamanho maximo de cada mensagem//

//Estruturas//

typedef struct{ //Define a estrutura mensagem, que e constituida por um numero de utilizador - registry_number - e pela mensagem inserida pelo utilizador.//
   int registry_number;
   char mensagem[TAMANHO+1];
}Mensagem;

//Variaveis Globais//

Mensagem Forum[MESSAGES]; //Corresponde ao forum, constituido por todas as mensangens enviadas pelos utilizadores// 
int conta_msg=0; //Indica o numero total de mensagens//
int user_mais_ativo[PARTICIPANTS]; 
int pos=0; 
int sort[MESSAGES]; 
int aux_sort[MESSAGES];
  
//Funcoes//

Mensagem nova_msg(){ //Funcao que permite ao utilizador escrever a nova mensagem//
    Mensagem aux; //Define uma mensagem auxiliar que serve para guardar cada mensagem antes de inseri-la no forum//
    int i = 0;
    char c;
    scanf("%d", &aux.registry_number);

    getchar(); //Serve para remover o espaco presente na string antes da mensagem//
    
    while((c=getchar()) != '\n' && c!=EOF){ 
	 aux.mensagem[i++]=c;
    }

    aux.mensagem[i] = '\0'; //Adiciona o caracter '\0' no fim da string//

    conta_msg++;
    
    user_mais_ativo[aux.registry_number]++; //Incrementa, na tabela onde sao guardadas o numero de mensagens de cada utilizador, o numero de mensagens correspondente a cada utilizador//

    return aux; //Devolve a mensagem auxiliar que sera usada no main//
}

void lista_mensagens(){ //Funcao que permite ao utilizador visualizar todas as mensagens escritas no seu forum//
     int i=0;

     printf("*TOTAL MESSAGES:%d\n",conta_msg); 

     while(i<conta_msg){ 
          printf("%d:%s\n", Forum[i].registry_number, Forum[i].mensagem);
          i++;
     }
}

void lista_mensagens_user(){ //Funcao que permite ao administrador do forum listar todas as mensagens de um determinado utilizador//
     int i=0;
     int user_number;

     scanf("%d", &user_number); 

     getchar();

     printf("*MESSAGES FROM USER:%d\n",user_number); 
     while(i<conta_msg){ 
          if(Forum[i].registry_number==user_number){  //Verifica se o user fornecido pelo utilizador esta presente no forum//
            printf("%s\n", Forum[i].mensagem); 
          }
          i++;
     }
}

void verifica_frase_mais_longa(){ //Verifica qual a frase mais longa introduzida por todos os utilizadores//
     int i;
     int size=0;
     int fml=0;
     for(i=0; i<conta_msg; i++){ //Este ciclo verifica qual o maior tamanho das mensagens presente no forum//
        size=strlen(Forum[i].mensagem);
        if(size>fml) 
           fml=strlen(Forum[i].mensagem);
     }
     for(i=0; i<conta_msg; i++){ 
        if(fml==strlen(Forum[i].mensagem)) //Verifica quais as mensagens com tamanho maximo no forum//
          printf("*LONGEST SENTENCE:%d:%s\n", Forum[i].registry_number, Forum[i].mensagem);
     }
}

void verifica_user_mais_ativo(){ //Verifica qual o user com mais mensagens no forum//
     int i;
     int maior_uma=0;
     for(i=0; i<PARTICIPANTS; i++){ //Faz o ciclo que percorre a tabela uma, definida como a tabela que guarda o numero de mensagens de cada utilizador//
        if(user_mais_ativo[i]>maior_uma)
           maior_uma=user_mais_ativo[i];
     }
     for(i=0; i<PARTICIPANTS; i++){ //Este ciclo percorre a tabela uma e verifica quais os uers com o mesmo numero de mensagens que o maior numero de mensagens de um user no forum//
        if(maior_uma==(user_mais_ativo[i]))
          printf("*MOST ACTIVE USER:%d:%d\n", i, maior_uma); //Devolve o user mais ativo e o seu numero de mensagens//
     }
}

int less(int a, int b){ //Faz parte do merge sort e verifica se uma mensagem e "menor" que outra, e se forem iguais, verifica se o user e menor//
    if((strcmp(Forum[a].mensagem, Forum[b].mensagem))<0 || ((strcmp(Forum[a].mensagem, Forum[b].mensagem))==0 && (Forum[a].registry_number < Forum[b].registry_number)))
       return 1;
    else
       return 0;
}

void merge(int a[], int l, int m, int r){ 
     int i,j,k;
     for(i=m+1; i>l; i--)
        aux_sort[i-1]=a[i-1];
     for(j=m; j<r; j++)
        aux_sort[r+m-j]=a[j+1];
     for(k=l; k<=r; k++){
        if(less(aux_sort[j], aux_sort[i]))
          a[k]=aux_sort[j--];
        else
          a[k]=aux_sort[i++];
     }
}

void mergesort(int a[], int l, int r){
     int m=(r+l)/2;
     if(r<=l) 
       return;
     mergesort(a,l,m);
     mergesort(a,m+1,r);
     merge(a,l,m,r);
}

void sort_palavras(int a[]){ //Funcao que da print das frases ordenadas e do numero total de mensagens ordenadas//
     int i;
     for(i=0; i<conta_msg; i++){
        sort[i]=i;
     }
     mergesort(sort, 0, conta_msg-1);

     printf("*SORTED MESSAGES:%d\n",conta_msg);

     for(i=0; i<conta_msg; i++){
        printf("%d:%s\n", Forum[sort[i]].registry_number, Forum[sort[i]].mensagem);
     }
}
               
void conta_palavras(){ //Apos o utilizador introduzir uma dava palavra, devolve quantas vezes foi inserida essa palavra no forum//
     int i,j,k=0;
     char palavra[TAMANHO+1]; //Corresponde a string onde vai ser inseriada a palavra escrita pelo utlizador//
     int cont=0;
     char palavra_aux[TAMANHO+1]; //Corresponde ao vetor auxiliar onde sera guardada cada palavra das mensagens//
     int tamanho_mensagem;

     scanf("%s", palavra); 
     
     getchar(); //Serve para remover o espaco presente na string antes da mensagem//

     for(i=0; i<conta_msg; i++){ //Verifica se a string dada pelo utilizador e igual as palavras existentes em cada mensagem do forum//
        tamanho_mensagem=strlen(Forum[i].mensagem);
        for(j=0; j<=tamanho_mensagem; j++){ //Percorre cada mensagem do forum//
           if(Forum[i].mensagem[j] != ';' && Forum[i].mensagem[j] != ',' && Forum[i].mensagem[j] != '\t' && Forum[i].mensagem[j] != ' ' && Forum[i].mensagem[j] != '.' && Forum[i].mensagem[j] != '\n' && Forum[i].mensagem[j] != '\0'){ //Verifica se a palavra ja terminou//
             palavra_aux[k]=Forum[i].mensagem[j]; 
             k++;
           }
           else{
             palavra_aux[k]='\0'; 
             if((strcmp(palavra, palavra_aux))==0)
               cont++;
               k=0; //Reinicia a palavra_aux, de modo a permitir escrever em palavra_aux de novo//
           }  
         }
      }
     printf("*WORD %s:%d\n", palavra, cont);
}

//Funcao Principal//

int main()
{
    char command; //Corresponde a variavel que esta relacionada com o comando escrito pelo utilizador//

    while((command=getchar()) != 'X'){ //Se o comando inserido for X, o program termina//

         getchar(); //Serve para remover o espaco presente na string antes da mensagem//

         switch(command){   
               case 'A':  //Corresponde ao comando A - funcao nova_msg -  ou seja, adicionar uma nova mensagem//
               Forum[pos++]=nova_msg(); 
               break;

               case 'L':  //Corresponde ao comando L - lista_mensagens - , ou seja, listar todas as mensagens//
               lista_mensagens();
               break; 

               case 'U':  //Corresponde ao comando U - lista_mensagens_user - , que lista todas as mensagens introduzidas por um dado utilizador//
               lista_mensagens_user();
               break;

               case 'O': //Corresponde ao comando O - verifica_frase_mais_longa - , que lista a frase mais longa escrita pelo utilizador//
               verifica_frase_mais_longa();
               break;

               case 'T':  //Corresponde ao comando T - verifica_user_mais_ativo - , que devolve o utilizador mais ativo na escrita de mensagens//
               verifica_user_mais_ativo();
               break;

               case 'S':  //Corresponde ao comando S - sort_palavras - , que lista todas as mensagens por ordem alfabetica//
               sort_palavras(sort);
               break;

               case 'C':  //Corresponde ao comando C - conta_palavras - , que devolve a ocorrencia de uma palavra dada//
               conta_palavras();
               break;
         }
   }

   if(command=='X'){ //Se o comando for X, vai dar print ao numero total de mensagens introduzidas pelo utilizador//
     printf("%d\n",conta_msg);
     }
    
   return 0; //O return 0 garante que o programa corre bem//
}
