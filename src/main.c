/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_LINHAS 30
#define MAX_COLUNAS 60

typedef struct CorpoCobrinha{
    int x, y;
    struct CorpoCobrinha* next;
}CorpoCobrinha;

typedef struct Cobrinha{
    // int comprimento;
    CorpoCobrinha* head;
}Cobrinha;

Cobrinha cobrinha;
int incX, incY;
int gameover;

void iniciar_jogo(){
    cobrinha.head = malloc(sizeof(CorpoCobrinha));
    cobrinha.head->x = 20;
    cobrinha.head->y = 20;
    cobrinha.head->next = NULL;
    // cobrinha.comprimento = 10;
    incX = 1;
    incY = 0;
}


void print_cobrinha(){
    screenSetColor(YELLOW, DARKGRAY);
    CorpoCobrinha* atual = cobrinha.head;
    while (atual != NULL){
        screenGotoxy(atual->x, atual->y);
        printf("˚");
        atual = atual->next;
    }
}

void cobrinha_andar() {
    CorpoCobrinha* newHead = malloc(sizeof(CorpoCobrinha));
    newHead->x = cobrinha.head->x + incX;
    newHead->y = cobrinha.head->y + incY;
    newHead->next = cobrinha.head;
    cobrinha.head = newHead;

    CorpoCobrinha* atual = cobrinha.head;
    while (atual->next->next != NULL) {
        atual = atual->next;
    }
    CorpoCobrinha* temp = malloc(sizeof(CorpoCobrinha));
    temp = newHead->next; 
    newHead->next = newHead->next->next;
    free(temp);
}





int main(){

    int ch = 0;
    screenInit(1);
    keyboardInit();
    timerInit(100);
    iniciar_jogo();
    while (!gameover){
        if(keyhit()){
            ch = readch();
            switch (ch){
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
            }
        }

        if(timerTimeOver() == 1){
            cobrinha_andar();
            screenClear();
            print_cobrinha();
            screenUpdate();

        }
    }
    CorpoCobrinha* atual = cobrinha.head;
    while (atual != NULL){
        CorpoCobrinha* temp = atual;
        atual = atual->next;
        free(temp);
    }
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}