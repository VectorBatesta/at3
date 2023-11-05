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
    int *valores_out = (int*) malloc(quantLinhas * sizeof(int)); //vetor filtrado
   
    for(int i = 0; fgets(linha, sizeof(linha), arq); i++){ //false se EOF
        valores[i] = atoi(linha); //atribui para int
    }

    //printa TODOS OS 261488 VALORES! - apenas para teste
    // for(int i = 0; i < quantLinhas; i++){
    //     printf("%i, ", valores[i]);
    // }




    //ver SDL





    int Fs = 44100; //frequency
    double G[11] = {0.9552, 0.9552, 0.9445, 0.9445, 0.9143, 0.9143, 0.8212, 0.8212, 0.4440, 0.4440, 1.0000};
    double SOS[6][11] ={{1.0000, -1.9999, 1.0000, 1.0000, -1.9967, 0.9982},
                        {1.0000, -1.9985, 1.0000, 1.0000, -1.9993, 0.9994},
                        {1.0000, -1.9999, 1.0000, 1.0000, -1.9919, 0.9934},
                        {1.0000, -1.9983, 1.0000, 1.0000, -1.9980, 0.9982},
                        {1.0000, -1.9999, 1.0000, 1.0000, -1.9821, 0.9841},
                        {1.0000, -1.9977, 1.0000, 1.0000, -1.9963, 0.9964},
                        {1.0000, -2.0000, 1.0000, 1.0000, -1.9551, 0.9581},
                        {1.0000, -1.9956, 1.0000, 1.0000, -1.9937, 0.9938},
                        {1.0000, -2.0000, 1.0000, 1.0000, -1.9903, 0.9904},
                        {1.0000, -1.9694, 1.0000, 1.0000, -1.8731, 0.8786}};



    valores_out[0] = 0;
    for (int i = 1; i < quantLinhas; i++){
        for (int j = 0; j < 11; j++){
            valores_out[i + j] = valores[i]*G[j] + valores_out[i-1];
        }
    }






    for (int i = 0; i < quantLinhas; i++){
        fprintf(arq_out, "%i\n", valores_out[i]); //teste print para escrever string em mp3
    }






    //termina programa fechando arquivos
    fclose(arq);
    fclose(arq_out);
    return EXIT_SUCCESS;
}