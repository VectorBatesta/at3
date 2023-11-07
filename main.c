#include <stdio.h>
#include <stdlib.h>

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

    //variaveis do matlab, G e SOS do FilterDesigner
    //double G[11] = {0.9552, 0.9552, 0.9445, 0.9445, 0.9143, 0.9143, 0.8212, 0.8212, 0.4440, 0.4440, 1.0000};
    /*double SOS[6][11] ={{1.0000, -1.9999, 1.0000, 1.0000, -1.9967, 0.9982},
                        {1.0000, -1.9985, 1.0000, 1.0000, -1.9993, 0.9994},
                        {1.0000, -1.9999, 1.0000, 1.0000, -1.9919, 0.9934},
                        {1.0000, -1.9983, 1.0000, 1.0000, -1.9980, 0.9982},
                        {1.0000, -1.9999, 1.0000, 1.0000, -1.9821, 0.9841},
                        {1.0000, -1.9977, 1.0000, 1.0000, -1.9963, 0.9964},
                        {1.0000, -2.0000, 1.0000, 1.0000, -1.9551, 0.9581},
                        {1.0000, -1.9956, 1.0000, 1.0000, -1.9937, 0.9938},
                        {1.0000, -2.0000, 1.0000, 1.0000, -1.9903, 0.9904},
                        {1.0000, -1.9694, 1.0000, 1.0000, -1.8731, 0.8786}};*/
    
    //valores em 'b' e 'a'
    double b[20] = {0.0000, -0.0002, 0.0019, -0.0110, 0.0463, -0.1466, 0.3625, -0.7171, 1.1525, -1.5198, 1.6536, -1.4869, 1.1031, -0.6715, 0.3321, -0.1314, 0.0406, -0.0095, 0.0016, -0.0002, 0.0000};
    double a[20] = {0.0000, -0.0002, 0.0017, -0.0103, 0.0435, -0.1391, 0.3475, -0.6944, 1.1278, -1.5032, 1.6533, -1.5032, 1.1278, -0.6944, 0.3475, -0.1391, 0.0435, -0.0103, 0.0017, -0.0002, 0.0000};
        

///////////////////////////////////////////////

    //manipula output:

    //inicializa vetor out em zeros
    for (int i = 0; i < quantLinhas; i++){
        valores_out[i] = 0; 
    }

    [todo: arrumar o filtro e usar ordem correta]

    //filtro
    for (int i = 1; i < quantLinhas; i++){ //percorre todos os valores (até max)
        for(int ai = 0; ai < 21; ai++){ //percorre todos os valores de 'a'
            valores_out[i] += valores[i - 1] * a[ai];
        }
        
        for(int bi = 0; bi < 21; bi++){ //percorre todos os valores de 'b'
            valores_out[i] -= valores[i - 1] * b[bi];
        }
    }

    //imprime os valores manipulados para output, botar no matlab para ouvir depois
    for (int i = 0; i < quantLinhas; i++){
        fprintf(arq_out, "%i\n", valores_out[i]);
    }



    //termina programa fechando arquivos
    fclose(arq);
    fclose(arq_out);
    return EXIT_SUCCESS;
}