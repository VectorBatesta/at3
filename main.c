#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    //inicializa arquivos
    FILE *arq;
    FILE *arq_out;

    if (argc > 1){ //se foi passado por argc e argv[]
        char const* const nomeArq = argv[1];
        arq = fopen(nomeArq, "r");
    }
    else{ //se nao, apenas abrir
        arq = fopen("heart_beat.txt", "r");
    }

    arq_out = fopen("heart_beat.mp3", "w");

    //teste se o arquivo está na pasta do projeto
    if (arq == NULL){
        printf("erro arquivo entrada");
        return(EXIT_FAILURE);
    }
    if (arq_out == NULL){
        printf("erro arquivo saida");
        return(EXIT_FAILURE);
    }
    

    //atribuiçao da linha de leitura do arquivo
    char linha[999];

    int quantLinhas = 0;
    //pega quantidade de valores (no heart_beat.txt há 261488)
    while(fgets(linha, sizeof(linha), arq)){ //false se EOF
        quantLinhas++;
    }
    printf("Quantidade de linhas no arquivo: %i\n", quantLinhas); //deve printar 261488
    rewind(arq); //volta pro começo do arq


    int *valores = (int*) malloc(quantLinhas * sizeof(int)); //aloca tamanho de 261488
   
    for(int i = 0; fgets(linha, sizeof(linha), arq); i++){ //false se EOF
        valores[i] = atoi(linha); //atribui para int
    }

    //printa TODOS OS 261488 VALORES! - apenas para teste
    // for(int i = 0; i < quantLinhas; i++){
    //     printf("%i, ", valores[i]);
    // }










    int Fs = 44100; //frequency

    char *audio_arquivo;
    audio_arquivo = "test"; //teste

    fprintf(arq_out, audio_arquivo); //teste print para escrever string em mp3







    //termina programa fechando arquivos
    fclose(arq);
    fclose(arq_out);
    return EXIT_SUCCESS;
}