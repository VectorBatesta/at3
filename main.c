#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arq = fopen("heart_beat.txt", "r");
    FILE *arq_out = fopen("heart_beat.mp3", "w");
    if (arq == NULL){
        printf("erro arquivo entrada");
        return(EXIT_FAILURE);
    }
    if (arq_out == NULL){
        printf("erro arquivo saida");
        return(EXIT_FAILURE);
    }


    int Fs = 44100;

    char *audio_arquivo;

    audio_arquivo = "test";

    fprintf(arq_out, audio_arquivo);

    return EXIT_SUCCESS;
}