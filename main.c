#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
    //inicializa arquivos
    FILE *arq;
    FILE *arq_out;

    //seta o input com o primeiro FILE
    if (argc > 1){ //se foi passado por argc e argv[]
        char const* const nomeArq = argv[1];
        arq = fopen(nomeArq, "r");
    }
    else{ //se nao, apenas abrir
        arq = fopen("heart_beat.txt", "r");
    }

    //seta o output com o outro FILE
    arq_out = fopen("heart_beat_out.txt", "w");

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
    double *valores_out = (double*) malloc(quantLinhas * sizeof(double)); //vetor filtrado


    for(int i = 0; fgets(linha, sizeof(linha), arq); i++){ //false se EOF
        valores[i] = atoi(linha); //atribui para int
    }

    //printa TODOS OS 261488 VALORES! - apenas para teste
    // for(int i = 0; i < quantLinhas; i++){
    //     printf("%i, ", valores[i]);
    // }




    int Fs = 44100; //frequency
    
    //valores em 'b' e 'a'
    double b[7] = {0.0405, -0.1621,  0.2025,        0, -0.2025,  0.1621, -0.0405};
    double a[7] = {1.0000, -5.9947, 14.9748, -19.9523, 14.9549, -5.9788,  0.9960};

    //pega tamanho de 'b' e 'a'
    int tamB = sizeof(b) / sizeof(b[0]);
    int tamA = sizeof(a) / sizeof(a[0]);
    printf("\nTamanho de 'b': %i\nTamanho de 'a': %i\n", tamB, tamA);

///////////////////////////////////////////////

    //manipula output:

    //inicializa vetor out em zeros
    for (int i = 0; i < quantLinhas; i++){
        valores_out[i] = 0; 
    }

    printf("t=%i,\n", valores[0]);
    printf("t=%i,\n", valores[1]);

    //filtro
    for (int i = 0; i < quantLinhas; i++){ //percorre todos os valores (até max)

        for(int bi = 0; bi < tamB; bi++){ //percorre todos os valores de 'b'
            if (i - bi >= 0){
                valores_out[i] += valores[i - bi] * b[bi] * 0.0001;
            }
        }
        
        for(int ai = 1; ai < tamA; ai++){ //percorre todos os valores de 'a'
            if (i - ai >= 0){
                valores_out[i] -= valores_out[i - ai] * a[ai];
            }
        }
    }

    //imprime os valores manipulados para output, botar no matlab para ouvir depois
    for (int i = 0; i < quantLinhas; i++){
        fprintf(arq_out, "%f\n", valores_out[i]);
    }



    //termina programa fechando arquivos
    fclose(arq);
    fclose(arq_out);
    return EXIT_SUCCESS;
}
/**/