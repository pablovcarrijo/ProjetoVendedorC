#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[50];
    int cod;
    float salary;
} Vendedor;

static Vendedor vendedor[4];
static float vendas[4][12];
static int n = 0;
int flag;

void menu();
void cadastrarVendedor();
void cadastrarVenda();
void consultarVenda();
void excluirVendedor();

int main() {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            vendas[i][j] = 0;
        }
    }

    menu();

    return 0;
}

void menu() {
    printf("==================MENU==================\n");
    printf("1 - Cadastrar um vendedor\n");
    printf("2 - Cadastrar vendas do vendedor\n");
    printf("3 - Consultar total de vendas do vendedor\n");
    printf("4 - Excluir um vendedor\n");
    printf("0 - Encerrar programa\n");

    int opc;
    scanf("%d%*c", &opc);  // O %*c consome o caractere de nova linha deixado no buffer
    switch (opc) {
        case 1:
            cadastrarVendedor();
            break;
        case 2:
            cadastrarVenda();
            break;
        case 3:
            consultarVenda();
            break;
        case 4:
            excluirVendedor();
            break;
        case 0:
            printf("Encerrando programa...\n");
            sleep(1);
            exit(0);
            break;
        default:
            printf("Opção inválida, tente novamente!\n");
            sleep(1);
            break;
    }

    menu();
}

void cadastrarVendedor() {
    int cod;

    if (n == 4) {
        printf("Quantidade máxima de funcionários atingida\n");
        sleep(1);
        return;
    }

    printf("Digite o código do vendedor: ");
    scanf("%d%*c", &cod);

    flag = 1;
    for (int i = 0; i < n; i++) {
        if (vendedor[i].cod == cod) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) {
        printf("Código de vendedor já existente, tente novamente!\n");
        return;
    }

    printf("Digite o nome do vendedor: ");
    fgets(vendedor[n].name, 50, stdin);
    vendedor[n].name[strcspn(vendedor[n].name, "\n")] = '\0';  // Remove a nova linha

    printf("Digite o salário base: ");
    scanf("%f%*c", &vendedor[n].salary);

    vendedor[n].cod = cod;
    n++;

    printf("Vendedor cadastrado com sucesso!\n");
    for (int i = 0; i < n; i++) {
        printf("Vendedor do código %d\n", vendedor[i].cod);
        printf("Nome: %s\n", vendedor[i].name);
        printf("Salário base: R$%.2f\n\n", vendedor[i].salary);
    }
}

void cadastrarVenda() {
    int codVend;
    int x = -1;
    printf("==============CADASTRO DE VENDA==============\n");

    do {
        flag = 0;
        printf("Digite o código do vendedor: ");
        scanf("%d%*c", &codVend);

        for (int i = 0; i < n; i++) {
            if (codVend == vendedor[i].cod) {
                flag = 1;
                x = i;
                break;
            }
        }
        if (flag == 0) {
            printf("Vendedor não encontrado, tente novamente...\n");
            sleep(1);
        }
    } while (flag == 0);

    int mes;
    printf("Digite o mês (1-12): ");
    scanf("%d%*c", &mes);

    if (mes < 1 || mes > 12) {
        printf("Mês inválido. Tente novamente.\n");
        return;
    }

    if (vendas[x][mes - 1] != 0) {
        printf("Já existe uma venda registrada para esse mês. Tente outro mês.\n");
        return;
    }

    float vendasMes;
    printf("Digite o total de vendas: ");
    scanf("%f%*c", &vendasMes);

    vendas[x][mes - 1] = vendasMes;

    printf("Venda cadastrada com sucesso!\n");

    printf("==============ATUALIZAÇÃO VENDAS==============\n");
    for (int i = 0; i < n; i++) {
        printf("|Código: %d|", vendedor[i].cod);
        for (int j = 0; j < 12; j++) {
            printf("|%.2f|", vendas[i][j]);
        }
        printf("\n");
    }
}

void consultarVenda() {
    printf("===================CONSULTANDO TOTAL DE VENDAS===================\n");

    int codVend;
    do {
        flag = 0;
        printf("Digite o código do vendedor: ");
        scanf("%d%*c", &codVend);

        for (int i = 0; i < n; i++) {
            if (codVend == vendedor[i].cod) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("Vendedor não encontrado, tente novamente...\n");
            sleep(1);
        }
    } while (flag == 0);

    float sum = 0;
    for (int i = 0; i < n; i++) {
        if (codVend == vendedor[i].cod) {
            for (int j = 0; j < 12; j++) {
                sum += vendas[i][j];
            }
            break;
        }
    }
    printf("Vendas totais do vendedor: R$%.2f\n", sum);
}

void excluirVendedor() {
    printf("=====================PROCESSO DE EXCLUSÃO DE VENDEDOR=====================\n");

    char nameEx[50];
    int pos = -1;

    do {
        flag = 0;
        printf("Digite o nome do vendedor: ");
        fgets(nameEx, 50, stdin);
        nameEx[strcspn(nameEx, "\n")] = '\0';

        for (int i = 0; i < n; i++) {
            if (strcmp(nameEx, vendedor[i].name) == 0) {
                printf("Nome: %s\n", vendedor[i].name);
                printf("Código: %d\n", vendedor[i].cod);
                printf("Salário: R$%.2f\n", vendedor[i].salary);
                pos = i;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("Nome não encontrado, tente novamente...\n");
            sleep(1);
        }
    } while (flag == 0);

    char opcEx;
    printf("Deseja realmente excluir (s/n)? ");
    scanf("%c%*c", &opcEx);

    if (opcEx == 's') {
        for (int i = pos; i < n - 1; i++) {
            vendedor[i] = vendedor[i + 1];
            for (int j = 0; j < 12; j++) {
                vendas[i][j] = vendas[i + 1][j];
            }
        }
        n--;
        printf("Funcionário excluído com sucesso.\n");
        sleep(1);
    } else if (opcEx == 'n') {
        printf("Exclusão cancelada.\n");
        sleep(1);
    } else {
        printf("Opção inválida.\n");
    }
}
