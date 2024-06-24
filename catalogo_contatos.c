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
}