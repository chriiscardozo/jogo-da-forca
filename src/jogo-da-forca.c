#include <stdio.h>
#include <conio.h>
#include <string.h>

int MAXLEN = 20;

char FIXTURES[5][20] = { "OVERFLOW",
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


int chToUpper(char ch){
     return ch & ~32;
}

void strToUpper( char *s ){
     for( ; *s; *s++)
            if(*s >= 'a' && *s <= 'z') *s = chToUpper(*s);
}

void printBoneco(int n){
     if(n == 0 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |  O\n");
         printf(" | /|\\ \n");
         printf(" |  |\n");
         printf(" | / \\ \n");
     }
     if( n == 1 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |  O\n");
         printf(" | /|\\ \n");
         printf(" |  |\n");
         printf(" | /  \n");
     }
     if( n == 2 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |  O\n");
         printf(" | /|\\\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 3 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |  O\n");
         printf(" | /|\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 4 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |  O\n");
         printf(" |  |\n");
         printf(" |  |\n");
         printf(" |\n");
     }
     if( n == 5 ){
         printf("\n  -- \n");
         printf(" |  |\n");
         printf(" |\n");
         printf(" |\n");
         printf(" |\n");
         printf(" |\n");
     }
}

void printLetrasUsadas(int letrasUsadas[]){
     int i;
     printf("\n\tLetras usadas: [ ");
     for(i = 65; i < 91; i++)
           if(letrasUsadas[i]) printf("%c ", i);
     printf("]\n");
}

void printPalavraEspelho(char *palavraEspelho){
     int i;
     printf("\n\t=> ");
     for(i = 0; palavraEspelho[i]; i++)
           printf("%c ", palavraEspelho[i]);
     printf("<=\n");
}

char chutaLetra(){
     char ch;
     printf("\n\tNova letra(apenas letras): ");
     fflush(stdin);
     scanf("%c", &ch);
     ch = chToUpper(ch);
     
     if(!(ch >= 'A' && ch <= 'Z')){
             opcaoInvalida();
             chutaLetra();
     }
     
     return ch;
}

int verificaLetraUsada(int letrasUsadas[], int letra){
    if(letrasUsadas[letra]) return 1;
    return 0;
}

int chuteCerto(char *palavraSecreta, char *palavraEspelho, char ch){
    int i;
    int acertou = 0;
    for(i = 0; palavraSecreta[i]; i++)
          if(palavraSecreta[i] == ch){
             palavraEspelho[i] = ch;
             acertou = 1;
          }
    return acertou;
}

int terminou(char *palavraSecreta, char *palavraEspelho){
     int i;
     for(i = 0; palavraSecreta[i]; i++)
           if(palavraEspelho[i] == '-') return 0;
     
     return 1;
}

char* preparaEspelho(char *palavraSecreta){
      int n = strlen(palavraSecreta);
      char *p = (char*) malloc(n + 1);
      int i;
      
      for(i = 0; i < n; i++){
            if(palavraSecreta[i] == ' ') p[i] = ' ';
            else p[i] = '-';
      }
      p[n] = 0;
      
      return p;
} 

void play( char *palavraSecreta ){
     int vida = 5;
     char chute;
     
     int letrasUsadas[256] = { 0 };
     char *palavraEspelho = preparaEspelho(palavraSecreta);
     
     while(vida){
          system("cls");
          printf("\n\n");
          
          printLetrasUsadas(letrasUsadas);
          printBoneco(vida);
          printf("\n\tVidas: %d\n", vida);
          printPalavraEspelho(palavraEspelho);
          
          chute = chutaLetra();
          
          if(!verificaLetraUsada(letrasUsadas, chute)){
             letrasUsadas[chute] = 1;
             if(!chuteCerto(palavraSecreta, palavraEspelho, chute)) vida--;
             else if(terminou(palavraSecreta, palavraEspelho)) break;
          }
          else{
             printf("\t\t\tLetra ja utilizada... <ENTER>");
             fflush(stdin);
             getchar();
          }
     }
     
     system("cls");
     if(!vida) printf("\n\n\t\t\t\tVoce perdeu...");
     else printf("\n\n\t\t\tParabens, voce ganhou");
     printBoneco(vida);
     printf("\nPalavra secreta: %s", palavraSecreta);
     printf("\n\nPressione <ENTER> para continuar");
     fflush(stdin);
     getchar();

     free(palavraEspelho);
     palavraEspelho = NULL;
     free(palavraSecreta);
     palavraSecreta = NULL;
}


char* sorteiaPalavraSecreta(){
      int index = rand()%5;
      return FIXTURES[index];
}

char* lePalavraSecreta(){
      int i;
      char ch;
      char *str = (char*) malloc(MAXLEN);
      
      printf("\n\nDigite a palavra secreta e de <ENTER> (Max.: 20 caracteres)\n");
      printf("OBS: Apenas letras e espacos serao lidos\n");
      printf(" => ");
      
      for(i = 0; i < MAXLEN - 1; i++){
            ch = getch();
            if(ch == 13) break;
            else if(ch == 8 && i > 0) i -= 2;
            else if((chToUpper(ch) >= 'A' && chToUpper(ch) <= 'Z') ||
                    (ch == ' ')) str[i] = ch;
            else i--; //caractere invalido digitado
      }      
      strToUpper(str);
      str[i] = 0;

      return str;
}

void playModoEscolhido(int modo){
     if(modo == 1) play(sorteiaPalavraSecreta());
     else play(lePalavraSecreta());
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
              else playModoEscolhido(modoDeJogo);
    }
    
}

int main(){
    srand(time(NULL));
    showTelaInicial();
    menuPrincipal();

    return 0;
}
