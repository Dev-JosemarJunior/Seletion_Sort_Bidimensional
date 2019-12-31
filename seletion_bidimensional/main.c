#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include "main.h"




int main (){

    int i, qtd, botao, opcao, passos1=0, passos2=0, resultadodepassos=0, trocasbubble1=0, trocasbubble2=0;
    double percentual;

    setlocale(LC_ALL,"");

    printf("Insira a quantidade de posições do vetor: ");
    scanf("%d", &qtd);

    do {
        printf("\nGostaria de um vetor (digite a opção desejada): \n(1) Decrescente - PIOR CASO\n(2) Aleatório - MÉDIO CASO\n(3) Crescente - MELHOR CASO \n");
        scanf("%d", &opcao);
    } while (opcao != 1 && opcao !=2 && opcao !=3);

    printf("\n****************************************************************\n\n\n");

    int array[qtd], arraycopy[qtd];

    switch(opcao){
        case 1:
            preencheVetor(array, qtd);
            botao=0;
            break;

        case 2:
            preencheVetorAleatorio(array, qtd);

            for (i = 0; i < qtd; i++){
                arraycopy[i] = array[i];
            }

            botao=1;

            break;
        case 3:
            preencheVetorCrescente (array, qtd);
            botao=2;
            break;
        default: break;
    }

    printVetor(array, qtd);

    passos1 = bubbleSort(array, qtd, &trocasbubble1);

    printf("\n\n\n############# VAMOS REPREENCHER O VETOR E RECOMEÇAR O PROCESSO #############\n\n\n");

    if (botao == 0){

        preencheVetor(array, qtd);
        printVetor(array, qtd);
        passos2 = bubbleSortMelhorado(array, qtd, &trocasbubble2);

    } else if(botao == 1) {

        printVetor(arraycopy, qtd);
        passos2 = bubbleSortMelhorado(array, qtd, &trocasbubble2);

    } else if(botao == 2){
        preencheVetorCrescente (array, qtd);
        printVetor(array, qtd);
        passos2 = bubbleSortMelhorado(array, qtd, &trocasbubble2);

    }

    resultadodepassos = passos1 - passos2;

    float passos1float = passos1, passos2float = passos2, resultadodepassosfloat = resultadodepassos;
    percentual = ((resultadodepassosfloat / passos1float) * 100);

    float trocasb1=trocasbubble1, trocasb2=trocasbubble2, percentualtrocas=(((trocasb1-trocasb2)/trocasb1)*100);

    if (percentualtrocas>0)
        printf("\n\n\n             ALGORITMO MELHORADO MAIS EFICIENTE QUE O ORIGINAL:\n             %d PASSOS MENOS\n             %.2f%% DE MELHORIA NA QTD DE PASSOS\n             %d TROCAS MENOS\n             %.2f%% DE MELHORIA NA QTD DE TROCAS\n\n\n", resultadodepassos, percentual, (trocasbubble1-trocasbubble2), percentualtrocas);
    else
        printf("\n\n\n             ALGORITMO MELHORADO MENOS EFICIENTE QUE O ORIGINAL:\n             %d PASSOS MAIS\n             %.2f%% DE PIORA NA QTD DE PASSOS\n             %d TROCAS MAIS\n             %.2f%% DE PIORA NA QTD DE TROCAS\n\n\n", -resultadodepassos, -percentual, -(trocasbubble1-trocasbubble2), percentualtrocas);

    return 0;
}

int bubbleSort (int vetor[], int N, int *trocasb1){
    int i, j, temp, count, trocas=0;

    for (i = 0; i<N-1; i++){
        count++;
        for(j = i+1; j<N; j++){
            count++;
            if (vetor[i]>vetor[j]){
                temp = vetor[i]; count++;
                vetor[i] = vetor[j]; count++;
                vetor[j] = temp; count++;
                trocas++;
            }
       }
    }

    printf("\n\n\n********************************\n");

    printf("Agora após o Primeiro Bubble\n");

    printf("\n------Numero de passos: %d e %d trocas.------\n", count, trocas);

    printVetor(vetor, N);

    printf("\n\n********************************\n");

    *trocasb1 = trocas;

    return count;
}

void printVetor(int vetor[], int N){

    int i, botao=0;

    printf("\nIMPRIMINDO VETOR:\n");

    for (i = 0; i<N; i++){

            if (N >20){

                if (i >10 && botao==0){
                    i = N-10;
                    botao++;
                    printf(" ... ");
                }
            }

            if (N > 20){
                if (i==0) printf("%d", vetor[i]);
                else if (i==N-1) printf(", %d.", vetor[i]);
                else  printf(", %d", vetor[i]);
            }
            else {
                if (i==0) printf("%d", vetor[i]);
                else if (i==N) printf(", %d.", vetor[i]);
                else  printf(", %d", vetor[i]);
            }
    }
}

void preencheVetor (int vetor[], int N){

    int i, j=N;

    for (i=0; i<N; i++){
        vetor[i] = j;
        j--;
    }
}

void preencheVetorAleatorio (int vetor[], int N){

    int i;

    for (i=0; i<N; i++){
        vetor[i] = rand() % N;
    }
}

void preencheVetorCrescente (int vetor[], int N){

    int i, j=1;

    for (i=0; i<N; i++){
        vetor[i] = j;
        j++;
    }
}

int bubbleSortMelhorado (int vetor[], int N, int *trocasb2){

    int i, j, temp=0, count=0, maior, menor, aux=N-1, trocas=0;

    for (i = 0; i < aux; i++){
        count++;

        maior = i; count++;
        menor = i; count++;

        for (j = aux; j > i; j--){

            if (vetor[j]>vetor[maior])
                maior = j; count++;
            if (vetor[j]<vetor[menor])
                menor = j; count++;
        }

        if (maior != i){
            temp = vetor[aux]; count++;
            vetor[aux] = vetor[maior]; count++;
            vetor[maior] = temp; count++;
            trocas++;
        }

        if (menor != i){
            temp = vetor[i]; count++;
            vetor[i] = vetor[menor]; count++;
            vetor[menor] = temp; count++;
            trocas++;
        }

    aux--;
    }

    printf("\n\n\n********************************\n");

    printf("Agora após o Bubble Melhorado\n");

    printf("\n------Numero de passos: %d e %d trocas.------\n", count, trocas);

    printVetor(vetor, N);

    printf("\n\n********************************\n");

    *trocasb2 = trocas;

    return count;

}
