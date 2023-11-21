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


    long double *valores = (long double*) malloc(quantLinhas * sizeof(long double)); //aloca tamanho de 261488
    long double *valores_out = (long double*) malloc(quantLinhas * sizeof(long double)); //vetor filtrado


    for(int i = 0; fgets(linha, sizeof(linha), arq); i++){ //false se EOF
        valores[i] = strtold(linha, NULL); //atribui para int
    }

    //printa TODOS OS 261488 VALORES! - apenas para teste
    // for(int i = 0; i < quantLinhas; i++){
    //     printf("%i, ", valores[i]);
    // }




    int Fs = 44100; //frequency
    
    //valores em 'b' e 'a'
    //ong double b[7] = {0.0405, -0.1621,  0.2025,        0, -0.2025,  0.1621, -0.0405};
    long double b[7] = {4.05371351613149e-06, -1.6207339707449e-05, 2.02535396456892e-05, 0, -2.02535396456892e-05, 1.6207339707449e-05, -4.05371351613149e-06};
    long double a[7] = {1, -5.99469877066624, 14.9748204222116, -19.9522893252495, 14.9549337304216, -5.97878731959256, 0.996021262959231};

    //pega tamanho de 'b' e 'a'
    int tamB = sizeof(b) / sizeof(b[0]); //7
    int tamA = sizeof(a) / sizeof(a[0]); //7
    printf("\nTamanho de 'b': %i\nTamanho de 'a': %i\n", tamB, tamA);

///////////////////////////////////////////////

    //manipula output:

    //inicializa vetor out em zeros
    for (int i = 0; i < quantLinhas; i++){
        valores_out[i] = 0; 
    }

    printf("\nvalores[0]=%Lf,\n", valores[0]);
    printf("valores[1]=%Lf,\n", valores[1]);

    //filtro
    for (int i = 0; i < quantLinhas; i++){ //percorre todos os valores (até max)

        for(int bi = 0; bi < tamB; bi++){ //percorre todos os valores de 'b'
            if (i - bi >= 0){
                valores_out[i] += valores[i - bi] * b[bi];
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
        fprintf(arq_out, "%Lf\n", valores_out[i]);
    }


    printf("\nvalores_out[0]=%Lf,\n", valores_out[0]);
    printf("valores_out[1]=%Lf,\n", valores_out[1]);

    //termina programa fechando arquivos
    fclose(arq);
    fclose(arq_out);
    return EXIT_SUCCESS;
}
/**/