#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo constantes para tamanhos máximos dos campos
#define MAX_NOME 50
#define MAX_TELEFONE 15
#define MAX_CONTATOS 100

// Estrutura para armazenar os dados de um contato
typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
} Contato;

// Array para armazenar os contatos e um contador de contatos
Contato contatos[MAX_CONTATOS];
int num_contatos = 0;

// Função para adicionar um novo contato
void adicionar_contato() {
    if (num_contatos >= MAX_CONTATOS) { // Verifica se há espaço para mais contatos
        printf("Limite de contatos atingido.\n");
        return;
    }
    // Solicita o nome e o telefone do novo contato
    printf("Digite o nome: ");
    scanf("%s", contatos[num_contatos].nome);
    printf("Digite o telefone: ");
    scanf("%s", contatos[num_contatos].telefone);
    num_contatos++; // Incrementa o contador de contatos
    printf("Contato adicionado com sucesso!\n");
}

// Função para pesquisar um contato pelo nome
void pesquisar_contato() {
    char nome[MAX_NOME];
    printf("Digite o nome a ser pesquisado: ");
    scanf("%s", nome);

    for (int i = 0; i < num_contatos; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) { // Verifica se o nome corresponde a algum contato
            printf("Contato encontrado: %s - %s\n", contatos[i].nome, contatos[i].telefone);
            return;
        }
    }
    printf("Contato nao encontrado.\n");
}

// Função para excluir um contato pelo nome
void excluir_contato() {
    char nome[MAX_NOME];
    printf("Digite o nome a ser excluido: ");
    scanf("%s", nome);

    for (int i = 0; i < num_contatos; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) { // Verifica se o nome corresponde a algum contato
            for (int j = i; j < num_contatos - 1; j++) {
                contatos[j] = contatos[j + 1]; // Move os contatos para preencher o espaço vazio
            }
            num_contatos--; // Decrementa o contador de contatos
            printf("Contato excluido com sucesso!\n");
            return;
        }
    }
    printf("Contato nao encontrado.\n");
}

// Função para salvar os contatos em um arquivo binário
void salvar_contatos() {
    FILE *arquivo = fopen("contatos.dat", "wb"); // Abre o arquivo para escrita binária
    if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }
    fwrite(&num_contatos, sizeof(int), 1, arquivo); // Salva o número de contatos
    fwrite(contatos, sizeof(Contato), num_contatos, arquivo); // Salva os contatos
    fclose(arquivo); // Fecha o arquivo
}

// Função para carregar os contatos de um arquivo binário
void carregar_contatos() {
    FILE *arquivo = fopen("contatos.dat", "rb"); // Abre o arquivo para leitura binária
    if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Nenhum dado salvo encontrado.\n");
        return;
    }
    fread(&num_contatos, sizeof(int), 1, arquivo); // Lê o número de contatos
    fread(contatos, sizeof(Contato), num_contatos, arquivo); // Lê os contatos
    fclose(arquivo); // Fecha o arquivo
}

// Função para exibir o menu e executar as opções selecionadas
void menu() {
    int opcao;
    carregar_contatos(); // Carrega os contatos salvos

    do {
        // Exibe o menu de opções
        printf("\nCatalogo de Contatos\n");
        printf("1. Adicionar Contato\n");
        printf("2. Pesquisar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Salvar e Sair\n");
        printf("Escolha uma opçao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_contato();
                break;
            case 2:
                pesquisar_contato();
                break;
            case 3:
                excluir_contato();
                break;
            case 4:
                salvar_contatos();
                printf("Contatos salvos com sucesso. Saindo...\n");
                break;
            default:
                printf("Opçao invalida.\n");
                break;
        }
    } while (opcao != 4); // Continua exibindo o menu até a opção 4 ser escolhida
}

int main() {
    menu(); // Inicia o programa exibindo o menu
    return 0;
}
