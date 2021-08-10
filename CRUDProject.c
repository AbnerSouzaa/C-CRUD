//Projeto - Sistema CRUD - Cadastro de vendas.
//by: Abner Souza
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PRODUTOS 100

int qtdProdutos = 0;

typedef struct{
    char nome[50];
    float preco;
    int validade;
    int quantidade;
    int existe;
    int PesquisarProduto;
    int codigo;
} Produto;


void LerProdutosDoArquivo(Produto produtos[MAX_PRODUTOS]){
    int codigo;

    FILE* fp = fopen("projetonovo.txt", "r");

    if (fp == NULL)
        printf("Erro ao abrir o arquivo\n");
    else{
        while(1){
            fscanf(fp,"%i", &codigo);

            produtos[qtdProdutos].codigo = codigo;

            fscanf(fp,"%s", produtos[qtdProdutos].nome);
            fscanf(fp,"%f", &produtos[qtdProdutos].preco);
            fscanf(fp,"%i", &produtos[qtdProdutos].validade);
            fscanf(fp,"%i", &produtos[qtdProdutos].quantidade);
            fscanf(fp,"%i", &produtos[qtdProdutos].existe);
            if(feof(fp)){
                break;
            }
            qtdProdutos++;

        }
    }
    fclose(fp);
}


void SalvarProdutosNoArquivo(Produto produtos[MAX_PRODUTOS]){

    FILE* fp = fopen("projetonovo.txt", "w");

    if (fp == NULL)
        printf("Erro ao abrir o arquivo.\n");
    else {
        for(int i = 0; i < qtdProdutos; i++) {
            if(produtos[i].existe == 1){
                fprintf(fp,"%i\n", produtos[i].codigo);
                fprintf(fp,"%s\n", produtos[i].nome);
                fprintf(fp,"%.2f\n", produtos[i].preco);
                fprintf(fp,"%i\n",produtos[i].validade);
                fprintf(fp,"%i\n", produtos[i].quantidade);
                fprintf(fp,"%i\n", produtos[i].existe);
            }
        }
    }
    fclose(fp);
}


void Menu(Produto produtos[MAX_PRODUTOS]){
    int escolha;
    printf("/////////////////////CADASTRO DE PRODUTOS///////////////\n\n\n");

    do{
        system("cls");
        printf("1- Cadastrar Produto. \n");
        printf("2- Pesquisar Produtos. \n");
        printf("3- Excluir Produto. \n");
        printf("4- listar todos. \n");
        printf("5- Alterar. \n");
        printf("0- Sair. \n");
        scanf("%i", &escolha);
        getchar();
        switch(escolha){
            case 1:
                AdicionarProduto(produtos);
            break;
            case 2:
                PesquisarProduto(produtos);
            break;
            case 3:
                DeletarProduto(produtos);
            break;
            case 4:
                ListarProdutos(produtos);
            break;
            case 5:
                AlterarProduto(produtos);
            break;
        }
        getchar();
    } while (escolha != 0);
}


void AdicionarProduto(Produto produtos[MAX_PRODUTOS]){

    char nome[50];
    int escolha;

    do{
        printf("Nome:\n");
        fgets(nome, 50, stdin);

        nome[strlen(nome)-1] = '\0';
        strcpy(produtos[qtdProdutos].nome, nome);

        printf("Codigo:\n");
        scanf("%i", &produtos[qtdProdutos].codigo);
        printf("Preco:\n");
        scanf("%f", &produtos[qtdProdutos].preco);
        printf("Validade:\n");
        scanf("%i", &produtos[qtdProdutos].validade);
        printf("Quantidade:\n");
        scanf("%i", &produtos[qtdProdutos].quantidade);
        getchar();

        produtos[qtdProdutos].existe = 1;
        qtdProdutos++;

        printf("1 - Continuar\n0 - Sair.\n");
        scanf("%i", &escolha);

    }while (escolha != 0);
}


void AlterarProduto(Produto produtos[MAX_PRODUTOS]){
    char nome[50];
    int codigo, escolha;

    system("cls");
    ListarProdutos(produtos);

    do{
        printf("Codigo do produto a ser alterado:");
        scanf("%i", &codigo);
        getchar();

        for(int i = 0; i < qtdProdutos; i++){
            if(codigo == produtos[i].codigo){

                printf("Novo nome: \n");
                fgets(nome, 50, stdin);

                nome[strlen(nome)-1] = '\0';
                strcpy(produtos[i].nome, nome);

                printf("Novo preco: \n");
                scanf("%f", &produtos[i].preco);
                printf("Nova validade: \n");
                scanf("%i", &produtos[i].validade);
                printf("Nova Quantidade: \n");
                scanf("%i", &produtos[i].quantidade);
            }
        }
        printf("Digite 1 para continuar pesquisando ou 0 para sair.\n");
        scanf("%i", &escolha);

    }while(escolha != 0);
}


void PesquisarProduto(Produto produtos[MAX_PRODUTOS]){
    int codigo;

    system("cls");
    ListarProdutos(produtos);

    printf("Digite o codigo do produto para pesquisar.\n");
    scanf("%i", &codigo);

    for(int i = 0; i < qtdProdutos; i++){
        if(codigo == produtos[i].codigo){
            printf("Codigo: %i\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: %.2f\n", produtos[i].preco);
            printf("Validade: %i\n",produtos[i].validade);
            printf("Quantidade: %i\n", produtos[i].quantidade);
            break;
        }
    }
    getchar();
}


void DeletarProduto(Produto produtos[MAX_PRODUTOS]){
    int codigo;

    system("cls");
    ListarProdutos(produtos);

    printf("Digite o codigo do produto a ser removido.\n");
    scanf("%i", &codigo);

    getchar();

    for(int i = 0; i < qtdProdutos; i++){
        if(produtos[i].codigo == codigo){
            produtos[i].existe = 0;
            break;
        }
    }

    printf("Produto removido com sucesso.");

    getchar();
}


void ListarProdutos(Produto produtos[MAX_PRODUTOS]){
    printf("----------------------------Lista de Produtos-------------------------------------\n");
    puts("COD\t\t NOME\t\t PRECO\t\t VALIDADE\t QUANTIDADE");

    for(int i = 0; i < qtdProdutos; i++){
        if(produtos[i].existe == 1){
            printf("%i\t\t",produtos[i].codigo);
            printf("%s\t\t",produtos[i].nome);
            printf("%.2f\t\t",produtos[i].preco);
            printf("%i\t\t",produtos[i].validade);
            printf("%i\t\t",produtos[i].quantidade);
            printf("---------------------------------------------------------------------\n");
        }
    }
}


int main(){
    Produto produtos[MAX_PRODUTOS];

    LerProdutosDoArquivo(produtos);

    Menu(produtos);

    SalvarProdutosNoArquivo(produtos);

    return 0;
}
