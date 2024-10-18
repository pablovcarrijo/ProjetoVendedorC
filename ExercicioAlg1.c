#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_VENDEDORES 4

void menu();
void cadastrarVendedor();
void cadastrarVendaVendedor();
void consultarVendasVendedor();
void excluirVendedor();

static char vendedoresNomes[MAX_VENDEDORES][50];
static int codigoVendedores[MAX_VENDEDORES];
static float salarioVendedores[MAX_VENDEDORES];
static float matVendas[4][12];

static int count = 0;

int main(){
    for(int i = 0; i < MAX_VENDEDORES; i++){
        for(int j = 0; j < 12; j++){
            matVendas[i][j] = 0;
        }
    }
    menu();

}

void menu(){
    printf("\n====================MENU====================\n");
    printf("1 - Cadastrar vendedor\n");
    printf("2 - Cadastrar venda de um vendedor\n");
    printf("3 - Consultar vendas de um vendedor\n");
    printf("4 - Excluir vendedor\n");
    printf("5 - Finalizar programa\n");
    int opc;
    scanf("%d%*c", &opc);
    switch(opc){
        case 1:
            cadastrarVendedor();
            break;
        case 2:
            cadastrarVendaVendedor();
            break;
        case 3:
            consultarVendasVendedor();
            break;
        case 4:
            excluirVendedor();
            break;
        case 5:
            printf("Encerrando programa...");
            exit(0);
            sleep(1.2);
            break;
        default:
            printf("Opcao invalida...\n");
            sleep(1.3);
            menu();
            break;
    }
    menu();
}

void cadastrarVendedor(){

    if(count > 4){
        printf("Limite maximo de vendedores atingidos...\n");
        sleep(1.5);
        menu();
    }
    printf("Cadastrando vendedor #%d\n", (count + 1));
    printf("Name:  ");
    gets(vendedoresNomes[count]);

    int flag;
    int cod;
    do{
        flag = 1;
        printf("Codigo do vendedor: ");
        scanf("%d%*c", &cod);
        for(int i = 0; i < MAX_VENDEDORES; i++){
            if(cod == codigoVendedores[i]){
                printf("Codigo de vendedor ja existente, tente novamente...\n");
                sleep(1.5);
                flag = 0;
                break;
            }
        }

    } while(flag == 0);

    if(flag == 1){
        codigoVendedores[count] = cod;
    }

    printf("Salario do vendedor: ");
    scanf("%f", &salarioVendedores[count]);

    count++;
}

void cadastrarVendaVendedor(){

    int flag;
    int codVend;
    do{
        flag = 0;
        printf("Digite o codigo do vendedor: ");
        scanf("%d%*c", &codVend);
        for(int i = 0; i < MAX_VENDEDORES; i++){
            if(codVend == codigoVendedores[i]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            printf("Vendedor nao cadastrado, tente novamente...\n");
            sleep(1.5);
        }
    }while(flag == 0);

    printf("Total de vendas: ");
    float vendasVend;
    scanf("%f", &vendasVend);

    int flag2;
    do{
        flag2 = 0;
        printf("Mes (1-12): ");
        int mes;
        scanf("%d%*c", &mes);

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 12; j++){
                if(codVend == codigoVendedores[i] && matVendas[i][mes-1] == 0){
                    matVendas[i][mes-1] = vendasVend;
                    flag2 = 1;
                    break;
                }
            }
        }
        if(flag2 == 0){
            printf("Vendedor ja possui uma venda nesse mes, tente novamente...\n");
            sleep(1.5);
        }
    }while(flag2 == 0);


    printf("\n=======================ATUALIZACAO DA MATRIZ DE VENDAS=======================\n");
    for(int i = 0; i < 4; i++){
        printf("|Codigo: %d|", codigoVendedores[i]);
        for(int j = 0; j < 12; j++){
            printf("|%.2f|", matVendas[i][j]);
        }
        printf("\n");
    }

}
void consultarVendasVendedor(){

    int flag;
    float soma = 0;
    int codVend;
    do{
        flag = 0;
        printf("Digite o codigo do vendedor: ");
        scanf("%d%*c", &codVend);
        for(int i = 0; i < MAX_VENDEDORES; i++){
            if(codVend == codigoVendedores[i]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            printf("Vendedor nao cadastrado, tente novamente...\n");
            sleep(1.5);
        }
    }while(flag == 0);

    for(int i = 0; i < MAX_VENDEDORES; i++){
        if(codigoVendedores[i] == codVend){
            printf("Nome: %s\n", vendedoresNomes[i]);
            printf("Codigo: %d\n", codigoVendedores[i]);
            printf("Salario base: RS%.2f\n", salarioVendedores[i]);
            for(int j = 0; j < 12; j++){
                soma += matVendas[i][j];
            }
            printf("Total em vendas no ano: RS%.2f", soma);
            break;
        }
    }
}

void excluirVendedor(){

    int flag;
    char name[50];
    int pos = -1;
    do{
        flag = 0;
        printf("Digite o nome do fucionario: ");
        gets(name);
        for(int i = 0; i < MAX_VENDEDORES; i++){
            if(strcmp(vendedoresNomes[i], name) == 0){
                printf("Nome: %s\n", vendedoresNomes[i]);
                printf("Codigo: %d\n", codigoVendedores[i]);
                printf("Salario base: RS%.2f\n", salarioVendedores[i]);
                pos = i;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            printf("Funcionario nao cadastrado, tente novamente...\n");
            sleep(1.5);
        }
    }while(flag == 0);


    printf("Deseja mesmo excluir esse funcionario (s/n)? ");
    char ch;
    scanf("%c%*c", &ch);
    
    do{
        flag = 0;
        switch(ch){
            case 's':
                for(int i = pos; i < MAX_VENDEDORES; i++){
                    strcpy(vendedoresNomes[i], vendedoresNomes[i+1]);
                    codigoVendedores[i] = codigoVendedores[i+1];
                    salarioVendedores[i] = salarioVendedores[i + 1];
                    for(int j = 0; j < 12; j++){
                        matVendas[i][j] = matVendas[i + 1][j];
                    }
                }

                vendedoresNomes[MAX_VENDEDORES - 1][0] = '\0';
                codigoVendedores[MAX_VENDEDORES - 1] = 0;
                salarioVendedores[MAX_VENDEDORES - 1] = 0;
                for(int i = 0; i < MAX_VENDEDORES; i++){
                    for(int j = 0; j < 12; j++){
                        matVendas[MAX_VENDEDORES - 1][j] = 0;
                    }
                } 
                count --;
                printf("Funcionario excluido com sucesso...\n");
                sleep(1.5);
                flag = 1;
                break;
            case 'n':
                printf("Exclusao cancelada...\n");
                sleep(1.5);
                flag = 1;
                break;
            default:
                printf("Opcao invalida, tente novamente...\n");
                sleep(1.5);
                flag = 0;
                break;
        }
    }while(flag == 0);

}