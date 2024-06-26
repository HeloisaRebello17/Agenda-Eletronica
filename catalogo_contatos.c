#include <stdio.h>
#include <string.h>
#include <stdbool.h> 

struct contact {
    char nome[50];
    char telefone[15];
};

#define LIMITE 250
#define ARQUIVO_NOME "contatos.ccf"

struct contact contatos[LIMITE]; 
int counter = 0;

void carregarContato() {
    FILE *file = fopen(ARQUIVO_NOME, "r");
    counter = 0;

    if (file != NULL) {
        while (fgets(contatos[counter].nome, 50, file)) {
            if (strlen(contatos[counter].nome) > 1) {
                fgets(contatos[counter].telefone, 15, file);
                contatos[counter].nome[strcspn(contatos[counter].nome, "\n")] = '\0';
                contatos[counter].telefone[strcspn(contatos[counter].telefone, "\n")] = '\0';
                counter++;
            }
        }
        fclose(file);
    } else {
        printf("Erro ao carregar contatos.\n");
    }
}

void contatoSalvo(struct contact ctt, FILE *file) {
    fputs(ctt.nome, file);
    fputs("\n", file);
    fputs(ctt.telefone, file);
    fputs("\n", file);
}

bool arquivoReescrito(int ignore) {
    bool r = false;
    struct contact temp[LIMITE];
    int n = 0;

    remove(ARQUIVO_NOME);
    FILE *file = fopen(ARQUIVO_NOME, "a+");

    if (file != NULL) {
        for (int i = 0; i < counter; i++) {
            if (i != ignore) {
                contatoSalvo(contatos[i], file);
                temp[n] = contatos[i];
                n++;
            }
        }

        for (int i = 0; i < n; i++) {
            contatos[i] = temp[i];
        }
        counter = n;
        r = true;

        fclose(file);
    }

    return r;
}

bool contatoInserido(struct contact ctt) {
    bool r = false;
    FILE *file = fopen(ARQUIVO_NOME, "a+");

    if (file != NULL) {
        r = true;

        contatoSalvo(ctt, file);
        contatos[counter] = ctt;
        counter++;

        fclose(file);
    }

    return r;
}

void criarContato() {
    if (counter < LIMITE) {
        printf("\nNOVO CONTATO\n");

        struct contact ctt;

        printf("Nome: ");
        fgets(ctt.nome, 50, stdin);
        ctt.nome[strcspn(ctt.nome, "\n")] = '\0';

        printf("Telefone: ");
        fgets(ctt.telefone, 15, stdin);
        ctt.telefone[strcspn(ctt.telefone, "\n")] = '\0'; // Remove o '\n' do final da string

        if (contatoInserido(ctt)) {
            printf("\nContato salvo!\n");
        } else {
            printf("\nErro ao salvar contato.\n");
        }
    } else {
        printf("\nMemoria cheia.\n");
    }
}

void contatoEditado(int i) {
    struct contact ctt;

    printf("\nEDITAR CONTATO\n");

    printf("Nome: %s\n", contatos[i].nome);
    fgets(ctt.nome, 50, stdin);
    ctt.nome[strcspn(ctt.nome, "\n")] = '\0'; 

    if (strlen(ctt.nome) > 1) {
        strcpy(contatos[i].nome, ctt.nome);
    }

    printf("Telefone: %s\n", contatos[i].telefone);
    fgets(ctt.telefone, 15, stdin);
    ctt.telefone[strcspn(ctt.telefone, "\n")] = '\0';

    if (strlen(ctt.telefone) > 1) {
        strcpy(contatos[i].telefone, ctt.telefone);
    }

    if (arquivoReescrito(-1)) {
        printf("\nContato salvo.\n");
    } else {
        printf("\nErro ao atualizar arquivo.\n");
    }
}

bool confirme(char *message) {
    char r;

    printf("%s | S para SIM, outro para NAO: ", message);
    scanf(" %c", &r);

    return (r == 's' || r == 'S');
}

void contatoDeletado(int i) {
    if (confirme("\nDeseja excluir este contato?")) {
        if (arquivoReescrito(i)) {
            printf("\nContato excluido.\n\n");
        }
    }
}

void mostrarContato(int i) {
    printf("[%i]\n", i + 1);
    printf("Nome: %s\n", contatos[i].nome);
    printf("Telefone: %s\n", contatos[i].telefone);
}

void listaContatos() {
    printf("\nLISTA DE CONTATOS\n\n");

    for (int i = 0; i < counter; i++) {
        mostrarContato(i);
        printf("------------------------\n");
    }

    if (counter > 0) {
        menuSelect();
    }
}

bool pesquisar(char *a, char *b, int limit) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && i < limit) {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return true;
}

void pesquisarContato() {
    char nome[50];

    printf("BUSCA CONTATO\n\n");
    printf("Digite o nome para busca: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("\nRESULTADO\n\n");

    bool found = false;
    for (int i = 0; i < counter; i++) {
        if (pesquisar(nome, contatos[i].nome, strlen(nome))) {
            mostrarContato(i);
            printf("----------------------------\n");
            found = true;
        }
    }

    if (found) {
        menuSelect();
    }
}

void menuSelect() {
    int selected = -1;
    int op = 0;

    printf("Informe o codigo do contato para selecionar | 0 para voltar ao menu : ");
    scanf("%i", &selected);
    while (getchar() != '\n'); 

    if (selected > 0 && selected <= counter) {
        selected--;
        printf("\nSelecionado: %s\n", contatos[selected].nome);
        printf("1 - Editar\n");
        printf("2 - Excluir\n");
        printf("Outro para sair\n");

        scanf("%i", &op);
        while (getchar() != '\n'); 

        switch (op) {
            case 1:
                contatoEditado(selected);
                break;
            case 2:
                contatoDeletado(selected);
                break;
            default:
                break;
        }
    } else {
        printf("\nContato inexistente.\n\n");
    }
}

void menuDefault() {
    int op = 0;

    while (op != 9) {
        printf("Selecione a opcao desejada:\n");
        printf("1 - Novo contato:\n");
        printf("2 - Lista de contatos:\n");
        printf("3 - Buscar contato\n");
        printf("4 - Editar contato\n");
        printf("5 - Excluir contato\n");
        printf("9 - Sair\n");

        scanf("%i", &op);
        while (getchar() != '\n'); 

        switch (op) {
            case 1:
                criarContato();
                break;
            case 2:
                listaContatos();
                break;
            case 3:
                pesquisarContato();
                break;
            case 4:
                if (counter > 0) {
                    menuSelect();
                } else {
                    printf("\nNão há contatos para editar.\n\n");
                }
                break;
            case 5:
                if (counter > 0) {
                    menuSelect();
                } else {
                    printf("\nNão há contatos para excluir.\n\n");
                }
                break;
            case 9:
                printf("Até mais!\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

int main() {
    carregarContato();
    menuDefault();

    return 0;
}


