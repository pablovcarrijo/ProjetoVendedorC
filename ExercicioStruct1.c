#include <stdio.h>
#include <stdlib.h>

#define QUANT_VEI 5

struct Informacoes;

typedef struct{
    int codCid;
    int numVei;
    int numAci;
} Informacoes;

static Informacoes informacoes[QUANT_VEI];

int main(){

    int maior, maiorId, soma = 0, soma2000 = 0, qnt2000 = 0, media = 0, media2000 = 0;

    for(int i = 0; i < QUANT_VEI; i++){
        printf("Cidade numero #%d\n", (i+1));
        printf("Digite o codigo: ");
        scanf("%d%*c", &informacoes[i].codCid);
        printf("Digite quantidade de veiculos: ");
        scanf("%d%*c", &informacoes[i].numVei);
        printf("Digite a quantidade de acidentes: ");
        scanf("%d%*c", &informacoes[i].numAci);
    }

    for(int i = 0; i < QUANT_VEI; i++){
        printf("Codigo da cidade: %d\n", informacoes[i].codCid);
        printf("Quantidade de veiculos: %d\n", informacoes[i].numVei);
        printf("Quantidade de acidentes: %d\n", informacoes[i].numAci);
        printf("\n");
    }

    for(int i = 0; i < QUANT_VEI; i++){
        if(i == 0){
            maior = informacoes[i].numAci;
            maiorId = informacoes[i].codCid;
        }
        else{
            if(informacoes[i].numAci > maior){
                maior = informacoes[i].numAci;
                maiorId = informacoes[i].codCid;
            }
        }
        soma += informacoes[i].numVei;
        if(informacoes[i].numVei <= 2000){
            soma2000 += informacoes[i].numAci;
            qnt2000++;
        }
    }

    media = soma / QUANT_VEI;
    media2000 = soma2000 / qnt2000;

    printf("Cidade com o maior indice de acidentes: %d\n", maiorId);
    printf("Media de veiculos nas 5 cidades: %d\n", media);
    printf("Media acidentes cidade com menos de 2000 veiculos: %d\n", media2000);

    return 0;

}