#include <stdio.h>
#include <conio.h>
#include <string.h>

struct Jogo{
       char *palavra;
       char *espelho;
       int *letrasUsadas;
       int vidas;
};

char FIXTURES[5][200] = { "OVERFLOW",
                         "DEU RUIM",
                         "C",
                         "TELEFONE",
                         "MUSICA" };

void opcaoInvalida(){
     printf("Opcao invalida, tente novamente...\n<ENTER>");
     fflush(stdin);
     getchar();
}

void showTelaInicial(){
     printf("\t\t\t\t ------- \n");
     printf("\t\t\t\t| Forca |\n");
     printf("\t\t\t\t ------- \n");
     printf("\n\n\n\nPressione <ENTER> para continuar...");
     getchar();
}

void printBoneco(int n){
     printf("\n  -- \n");
     printf(" |  |\n");
     
     if( n == 0 ){
         printf(" |  O\n");
         printf(" | /|\\ \n");
         printf(" |  |\n");
         printf(" | / \\ \n");
     }
     if( n == 1 ){
         printf(" |  O\n");
         printf(" | /|\\ \n");
         printf(" |  |\n");
         printf(" | /  \n");
     }
     if( n == 2 ){
         printf(" |  O\n");
         printf(" | /|\\\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 3 ){
         printf(" |  O\n");
         printf(" | /|\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 4 ){
         printf(" |  O\n");
         printf(" |  |\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 5 ){
         printf(" |\n");
         printf(" |\n");
         printf(" |\n");
         printf(" |\n");
     }
}

void printLetrasUsadas(struct Jogo *j){
     int i;
     printf("\n\tLetras usadas: [ ");
     for(i = 65; i < 91; i++)
           if(j->letrasUsadas[i]) printf("%c ", i);
           
     printf("]\n");
}

void printEspelho(struct Jogo *j){
     int i;
     printf("\n\t=> ");
     for(i = 0; j->espelho[i]; i++)
           printf("%c ", j->espelho[i]);
           
     printf("<=\n");
}

char chutaLetra(){
     char ch;
     printf("\n\tNova letra: ");
     fflush(stdin);
     scanf("%c", &ch);
     ch = toupper(ch);
     
     if(!(ch >= 'A' && ch <= 'Z')){
             opcaoInvalida();
             chutaLetra();
     }
     return ch;
}

int verificaLetraUsada(struct Jogo *j, int letra){
    if(j->letrasUsadas[letra]) return 1;
    return 0;
}

int chuteCerto(struct Jogo *j, char ch){
    int i;
    int acertou = 0;
    
    for(i = 0; j->palavra[i]; i++)
          if(j->palavra[i] == ch){
             j->espelho[i] = ch;
             acertou = 1;
          }
    return acertou;
}

int terminou(struct Jogo *j){
     int i;
     
     if(j->vidas == 0) return 1;
     for(i = 0; j->palavra[i]; i++)
           if(j->espelho[i] == '-') return 0;
     
     return 1;
}

void preparaEspelho(struct Jogo *j){
      int n = strlen(j->palavra);
      int i;
      j->espelho = (char*) malloc(n);
      
      for(i = 0; i < n; i++){
            if(j->palavra[i] == ' ') j->espelho[i] = ' ';
            else j->espelho[i] = '-';
      }
      j->espelho[i] = 0;
} 

char sorteiaPalavra(struct Jogo *j){
      int index = rand()%5;
      j->palavra = FIXTURES[index];
}

void lePalavraSecreta(struct Jogo *j){
      int i;
      char ch;
      
      printf("\n\nDigite a palavra secreta e de <ENTER>\n");
      printf("OBS: Apenas letras e espacos serao lidos\n");
      printf(" => ");
      for(i = 0; i < 200 - 1; i++){
            ch = getch();
            ch = toupper(ch);
            if(ch == 13) break;
            else if(ch == 8 && i > 0) i -= 2;
            else if((ch >= 'A' && ch <= 'Z') || 
                    (ch == ' ')) j->palavra[i] = ch;
            else i--; //caractere invalido digitado
      }
      j->palavra[i] = 0;
}

void initJogo(struct Jogo *j, int modo){
     j->palavra = (char*) malloc(200*sizeof(char));
     j->letrasUsadas = (int*) malloc(256*sizeof(int));
     
     memset(j->letrasUsadas, 0, 256*sizeof(int));
     
     if(modo == 1) sorteiaPalavra(j);
     else lePalavraSecreta(j);
     
     preparaEspelho(j);
     j->vidas = 5;     
}

void play(int modo){
     struct Jogo j;
     char chute;
     
     initJogo(&j, modo);
     
     while(!terminou(&j)){
          system("cls");
          printf("\n\n");
          
          printLetrasUsadas(&j);
          printBoneco(j.vidas);
          printf("\n\tVidas: %d\n", j.vidas);
          printEspelho(&j);
          
          chute = chutaLetra();
          
          if(!verificaLetraUsada(&j, chute)){
             j.letrasUsadas[chute] = 1;
             if(!chuteCerto(&j, chute)) j.vidas--;
          }
          else{
             printf("\t\t\tLetra ja utilizada... <ENTER>");
             fflush(stdin);
             getchar();
          }
     }
     
     system("cls");
     if(!j.vidas) printf("\n\n\t\t\t\tVoce perdeu...");
     else printf("\n\n\t\t\tParabens, voce ganhou");
     printBoneco(j.vidas);
     printf("\nPalavra secreta: %s", j.palavra);
     printf("\n\nPressione <ENTER> para continuar");
     fflush(stdin);
     getchar();

     free(j.letrasUsadas);
     free(j.espelho);
     free(j.palavra);
}

void menuPrincipal(){
     int modoDeJogo;
     
     while(1){
              system("cls");
              printf("\n\n Menu Principal:\n");
              printf(" 1 - Sortear palavra\n");
              printf(" 2 - Digitar palavra secreta\n");
              printf(" 3 - Sair\n");
              printf("Digite um numero para escolher uma opcao e de <ENTER>: ");
              scanf("%d", &modoDeJogo);
       
              if( modoDeJogo < 1 || modoDeJogo > 3 ) opcaoInvalida();
              else if( modoDeJogo == 3 ) exit(0);
              else play(modoDeJogo);
    }
    
}

int main(){
    srand(time(NULL));
    showTelaInicial();
    menuPrincipal();

    return 0;
}
