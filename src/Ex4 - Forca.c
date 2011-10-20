#include <stdio.h>

char palavraSecreta[] = "OVERFLOW";
int letrasUsadas[256] = { 0 };
char palavraDescoberta[] = "--------";
int vida = 5;

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

void printLetrasUsadas(){
     int i;
     printf("\t\t\tLetras usadas: [ ");
     for(i = 65; i < 91; i++)
           if(letrasUsadas[i]) printf("%c ", i);
     printf("]\n");
}

void printPalavraDescoberta(){
     int i;
     printf("\n\t\t\t=> ");
     for(i = 0; palavraSecreta[i]; i++)
           printf("%c ", palavraDescoberta[i]);
     printf("<=\n");
}

char chutaLetra(){
     char ch;
     printf("\t\t\tNova letra: ");
     fflush(stdin);
     scanf("%c", &ch);
     return chToUpper(ch);
}

int verificaLetraUsada(int letra){
    if(letrasUsadas[letra]) return 1;
    return 0;
}

int chuteCerto(char ch){
    int i;
    int acertou = 0;
    for(i = 0; palavraSecreta[i]; i++)
          if(palavraSecreta[i] == ch){
             palavraDescoberta[i] = ch;
             acertou = 1;
          }
    return acertou;
}

int terminou(){
     int i;
     for(i = 0; palavraSecreta[i]; i++)
           if(palavraDescoberta[i] == '-') return 0;
     
     return 1;
}

void play(){
     char chute;
     while(vida){
          system("cls");
          printf("\n\n");
          
          printLetrasUsadas();
          printf("\t\t\tVidas: %d\n", vida);
          printPalavraDescoberta();
          chute = chutaLetra();
          
          if(!verificaLetraUsada(chute)){
             letrasUsadas[chute] = 1;
             if(!chuteCerto(chute)) vida--;
             else if(terminou()) break;
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
     fflush(stdin);
     getchar();
}

int main(){
    showTelaInicial();
    play();

    return 0;
}
