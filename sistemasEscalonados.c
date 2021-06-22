/*  Autor: Laura Ferreira Rocha
    Data: 04/12/2020
*/

#include <stdio.h>
#include <stdlib.h>

float ** leMatriz(int);
float * leVetor(int);
float * calculaX(int, float **, float *);
void escreveX(int, float *);
void desaloca(int, float **, float *, float *);

int main(){
    float **coeficientes, *termosIndependentes, *X;
    int N, i, j, tamanho = 1;

    printf("=======Solucionador de sistemas escalonados=======\n\n");
    printf("Insira o numero de expressoes presentes no sistema: ");
    scanf("%d", &N);
    printf("Resolvendo o sistema com %d equacoes...\n", N);

    coeficientes = leMatriz(N);
    termosIndependentes = leVetor(N);

    printf("\nMatriz de coeficientes: \n");
    for (i = 0; i < N; i++){
        for (j = 0; j < tamanho; j++)
            printf("%f ", *(*(coeficientes+i)+j));
        tamanho++;
        printf("\n");
    }
    printf("\nTermos independentes: \n");
    for (i = 0; i < N; i++)
        printf("%f ", *(termosIndependentes + i));
    printf("\n");

    X = calculaX(N, coeficientes, termosIndependentes);
    escreveX(N, X);
    desaloca(N, coeficientes, termosIndependentes, X);

    return 0;
}

float ** leMatriz(int n){
    FILE *termosA;
    float **coef;
    int i, j, tamanho = 1;

    termosA = fopen("coeficientes.txt", "r");
    if(termosA == NULL)
        printf("Erro na abertura do arquivo!");
    else{
        coef = (float**) malloc(n * sizeof(float *));
        for(i = 0; i < n; i++)
            coef[i] = (float*) malloc(n * sizeof(float));
        for (i = 0; i < n; i++){
            for (j = 0; j < tamanho; j++)
                fscanf(termosA, "%f", (*(coef+i)+j));
            tamanho++;
        }
        fclose(termosA);
    }

    return coef;
}

float * leVetor(int n){
    FILE *termosB;
    float *vetor;
    int i;

    termosB = fopen("termosIndependentes.txt", "r");
    if(termosB == NULL)
        printf("Erro na leitura do arquivo!");
    else{
        vetor = (float *) malloc(n * sizeof(float));
        for(i = 0; i < n; i++)
            fscanf(termosB, "%f", (vetor+i));
        fclose(termosB);
    }
    return vetor;
}

float * calculaX(int n, float **a, float *b){
    int i, j;
    float *x, soma = 0;

    x = (float *) malloc(n * sizeof(float));
    x[0] = (float) b[0] / a[0][0];
    for(i = 1; i < n; i++){
        for(j = 0; j < i; j++){
            soma += a[i][j] * x[j];
        }
        x[i] = ( b[i] - soma) / a[i][i];
        soma = 0;
    }

    return x;
}

void escreveX(int n, float *x){
    int i;

    printf("\n================Resultados================\n");
    for(i = 0; i < n; i++)
        printf("X%d = %f\n", i, *(x + i));
    printf("\n");
}

void desaloca(int n, float **a, float *b, float *x){
    int i;

    for(i = 0; i < n; i++)
        free(a[i]);
    free(a);
    free(b);
    free(x);
}
