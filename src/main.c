/** 
 * main.h 
 * Criado em 23 de agosto de 2023 
 * Autor: Tiago Barros 
 * Baseado no "Curso de C a C++ - 2002" 
 */ 

#include "keyboard.h" 
#include "screen.h" 
#include "timer.h" 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

int comida_x, comida_y; 
#define MAX_LINHAS 30
#define MAX_COLUNAS 60 

typedef struct CorpoCobrinha { 
    int x, y; 
    char corpo;
    struct CorpoCobrinha *next; 
} CorpoCobrinha; 

typedef struct Cobrinha { 
    int comprimento; 
    CorpoCobrinha *head; 
} Cobrinha; 

Cobrinha cobrinha; 
int incX, incY, pontos; 
int gameover; 



void iniciar_jogo() { 
    cobrinha.head = malloc(sizeof(CorpoCobrinha)); 
    cobrinha.head->x = 20; 
    cobrinha.head->y = 20; 
    cobrinha.head->next = NULL; 
    cobrinha.comprimento = 1; 
    incX = 1; 
    incY = 0; 
    gameover = 0; 
    comida_x = rand() % MAX_COLUNAS;
    comida_y = rand() % MAX_LINHAS;
} 

void print_cobrinha() { 
    screenSetColor(GREEN, DARKGRAY); 
    CorpoCobrinha *atual = cobrinha.head; 
    while (atual != NULL) { 
        screenGotoxy(atual->x, atual->y); 
        printf("■"); 
        atual = atual->next; 
    } 
} 

void cobrinha_andar() { 
    CorpoCobrinha *newHead = malloc(sizeof(CorpoCobrinha)); 
    newHead->x = cobrinha.head->x + incX; 
    newHead->y = cobrinha.head->y + incY; 
    newHead->next = cobrinha.head; 
    cobrinha.head = newHead; 
        CorpoCobrinha *atual = cobrinha.head; 
        while (atual->next->next != NULL) { 
            atual = atual->next; 
        } 
        free(atual->next); 
        atual->next = NULL;  
        cobrinha.comprimento++; 
} 

void mostrar_comida() { 
    screenSetColor(RED, DARKGRAY); 
    screenGotoxy(comida_x, comida_y); 
    printf("x"); 
} 

void checa_colisao() {
    if (cobrinha.head->x >= MAX_COLUNAS || cobrinha.head->x < 0 ||
        cobrinha.head->y >= MAX_LINHAS || cobrinha.head->y < 0) {
        gameover = 1;
        return;
    }

    CorpoCobrinha *atual = cobrinha.head->next;
    while (atual != NULL) {
        if (cobrinha.head->x == atual->x && cobrinha.head->y == atual->y) {
            gameover = 1;
            return;
        }
        atual = atual->next;
    }

  if (cobrinha.head->x == comida_x && cobrinha.head->y == comida_y) {
      pontos++;
      comida_x = rand() % MAX_COLUNAS - 1;
      comida_y = rand() % MAX_LINHAS - 1;
      CorpoCobrinha *novo_segmento = malloc(sizeof(CorpoCobrinha));
      novo_segmento->x = cobrinha.head->x;
      novo_segmento->y = cobrinha.head->y;
      CorpoCobrinha *ultimo_segmento = cobrinha.head;

      while (ultimo_segmento->next != NULL) {
          ultimo_segmento = ultimo_segmento->next;
      }
      ultimo_segmento->next = novo_segmento;
      cobrinha.comprimento++;
      cobrinha.head->x += incX; 
      cobrinha.head->y += incY;
      print_cobrinha();
  } 
}

void print_borda(){
  screenSetColor(WHITE, DARKGRAY);
  int i;
  for(i=0 ; i<MAX_COLUNAS +1; i++){
    screenGotoxy(i, 0);
    printf("-");
  }
  for(i=0 ; i<MAX_COLUNAS +1; i++){
    screenGotoxy(i, MAX_LINHAS);
    printf("-");
  }
  for(i=0 ; i<MAX_LINHAS +1; i++){
    screenGotoxy(0, i);
    printf("|");
  }
  for(i=0 ; i<MAX_LINHAS +1; i++){
    screenGotoxy(MAX_COLUNAS, i);
    printf("|");
  }
}

void print_game_over(){
  screenSetColor(WHITE, DARKGRAY);
  screenGotoxy(2, 11);
  printf("------------------------------------------------------------------");
  screenGotoxy(2, 12);
  printf("┇                                                                ┇");
  screenGotoxy(2, 13);
  printf("┇    ■■■    ■■■   ■   ■   ■■■■       ■■■   ■   ■  ■■■■   ■■■■    ┇");
  screenGotoxy(2, 14);
  printf("┇   ■      ■   ■  ■■ ■■   ■         ■   ■  ■   ■  ■      ■   ■   ┇");
  screenGotoxy(2, 15);
  printf("┇   ■  ■■  ■ ■ ■  ■ ■ ■   ■■■■      ■   ■  ■   ■  ■■■■   ■■■■    ┇");
  screenGotoxy(2, 16);
  printf("┇   ■   ■  ■   ■  ■   ■   ■         ■   ■   ■ ■   ■      ■  ■    ┇");
  screenGotoxy(2, 17);
  printf("┇    ■■■   ■   ■  ■   ■   ■■■■       ■■■     ■    ■■■■   ■   ■   ┇");
  screenGotoxy(2, 18);
  printf("┇                                                                ┇");
  screenGotoxy(2, 19);
  if((pontos / 10) < 1){
    printf("┇                 Sua Pontuação foi de %d pontos                  ┇", pontos);
  }else if((pontos / 10) > 1 && (pontos / 10) <10){
    printf("┇                 Sua Pontuação foi de %d pontos                 ┇", pontos);
  }else{
    printf("┇                Sua Pontuação foi de %d pontos                 ┇", pontos);
  }
  screenGotoxy(2, 20);
  printf("┇            >> Pressione qualquer tecla para sair <<            ┇");
  screenGotoxy(2, 21);
  printf("┇                                                                ┇");
  screenGotoxy(2, 22);
  printf("------------------------------------------------------------------");
  getchar();
}

int main() { 
    int ch = 0; 
    screenInit(1); 
    keyboardInit(); 
    timerInit(100); 
    iniciar_jogo(); 
  

    while (!gameover) { 
      screenClear(); 
        if (keyhit()) { 
            ch = readch(); 
            switch (ch) { 
                case 'i': 
                    incX = 0; 
                    incY = -1; 
                    break; 
                case 'j': 
                    incX = -1; 
                    incY = 0; 
                    break; 
                case 'k': 
                    incX = 0; 
                    incY = 1; 
                    break; 
                case 'l': 
                    incX = 1; 
                    incY = 0; 
                    break; 
                case 'b': 
                    gameover = 1; 
                    break; 
            } 
        } 

        if (timerTimeOver() == 1) { 
            cobrinha_andar(); 
            checa_colisao();
            print_borda();
            mostrar_comida();
            print_cobrinha(); 
            screenUpdate(); 
            usleep(100000); 
        } 
    } 
    screenClear();
    print_game_over();
    CorpoCobrinha *atual = cobrinha.head; 
    while (atual != NULL) { 
        CorpoCobrinha *temp = atual; 
        atual = atual->next; 
        free(temp); 
    } 

    keyboardDestroy(); 
    screenDestroy(); 
    timerDestroy(); 

    return 0; 
}


/* 

  ■■■    ■■■   ■   ■   ■■■■       ■■■   ■   ■  ■■■■   ■■■■
 ■      ■   ■  ■■ ■■   ■         ■   ■  ■   ■  ■      ■   ■
 ■  ■■  ■ ■ ■  ■ ■ ■   ■■■■      ■   ■  ■   ■  ■■■■   ■■■■
 ■   ■  ■   ■  ■   ■   ■         ■   ■   ■ ■   ■      ■  ■
  ■■■   ■   ■  ■   ■   ■■■■       ■■■     ■    ■■■■   ■   ■

  ▪■⬛
*/