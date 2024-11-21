/*
// Created by ryanf on 21/11/2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESENVOLVEDORES 100

typedef struct {
    int id;
    char nome[50];
    char linguagem[50];
    int experiencia;
} Desenvolvedor;

Desenvolvedor desenvolvedores[MAX_DESENVOLVEDORES];
int contador = 0;

void adicionarDesenvolvedor() {
    if (contador < MAX_DESENVOLVEDORES) {
        Desenvolvedor novoDesenvolvedor;
        novoDesenvolvedor.id = contador + 1;
        printf("Digite o nome do desenvolvedor: ");
        scanf(" %49[^\n]", novoDesenvolvedor.nome);
        printf("Digite a linguagem principal do desenvolvedor: ");
        scanf(" %49[^\n]", novoDesenvolvedor.linguagem);
        printf("Digite os anos de experiência: ");
        scanf("%d", &novoDesenvolvedor.experiencia);

        desenvolvedores[contador] = novoDesenvolvedor;
        contador++;

        printf("Desenvolvedor adicionado com sucesso!\n");
    } else {
        printf("Limite de desenvolvedores atingido!\n");
    }
}

void atualizarDesenvolvedor() {
    int id;
    printf("Digite o ID do desenvolvedor que deseja atualizar: ");
    scanf("%d", &id);

    if (id > 0 && id <= contador) {
        printf("Digite o novo nome do desenvolvedor: ");
        scanf(" %49[^\n]", desenvolvedores[id - 1].nome);
        printf("Digite a nova linguagem principal do desenvolvedor: ");
        scanf(" %49[^\n]", desenvolvedores[id - 1].linguagem);
        printf("Digite os novos anos de experiência: ");
        scanf("%d", &desenvolvedores[id - 1].experiencia);

        printf("Desenvolvedor atualizado com sucesso!\n");
    } else {
        printf("Desenvolvedor não encontrado!\n");
    }
}

void listarDesenvolvedores() {
    if (contador == 0) {
        printf("Nenhum desenvolvedor cadastrado.\n");
    } else {
        for (int i = 0; i < contador; i++) {
            printf("ID: %d, Nome: %s, Linguagem: %s, Experiência: %d anos\n",
                   desenvolvedores[i].id, desenvolvedores[i].nome, desenvolvedores[i].linguagem, desenvolvedores[i].experiencia);
        }

        char opcao;
        printf("\nDeseja exportar a lista de desenvolvedores para um arquivo CSV? (s/n): ");
        scanf(" %c", &opcao);

        if (opcao == 's' || opcao == 'S') {
            salvarDesenvolvedores();
        }
    }
}

void removerDesenvolvedor() {
    int id;
    printf("Digite o ID do desenvolvedor que deseja remover: ");
    scanf("%d", &id);

    if (id > 0 && id <= contador) {
        for (int i = id - 1; i < contador - 1; i++) {
            desenvolvedores[i] = desenvolvedores[i + 1];
        }
        contador--;
        printf("Desenvolvedor removido com sucesso!\n");
    } else {
        printf("Desenvolvedor não encontrado!\n");
    }
}

void salvarDesenvolvedores() {
    FILE *fptr = fopen("C/desenvolvedores.csv", "w");
    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(fptr, "id,nome,linguagem,experiencia\n");
    for (int i = 0; i < contador; i++) {
        fprintf(fptr, "%d,%s,%s,%d\n", desenvolvedores[i].id, desenvolvedores[i].nome, desenvolvedores[i].linguagem, desenvolvedores[i].experiencia);
    }
    fclose(fptr);
    printf("Dados salvos com sucesso!\n");
}

void carregarDesenvolvedores() {
    FILE *fptr = fopen("C/desenvolvedores.csv", "r");
    if (fptr == NULL) {
        printf("Nenhum arquivo encontrado para carregar.\n");
        return;
    }

    char buffer[150];
    fgets(buffer, 150, fptr);
    while (fgets(buffer, 150, fptr) != NULL) {
        Desenvolvedor desenvolvedor;
        sscanf(buffer, "%d,%49[^,],%49[^,],%d", &desenvolvedor.id, desenvolvedor.nome, desenvolvedor.linguagem, &desenvolvedor.experiencia);
        desenvolvedores[contador] = desenvolvedor;
        contador++;
    }
    fclose(fptr);
    printf("Dados carregados com sucesso!\n");
}

int main() {
    int opcao;
    carregarDesenvolvedores();
    do {
        printf("\n----- CRUD de Desenvolvedores -----\n");
        printf("1. Adicionar Desenvolvedor\n");
        printf("2. Listar Desenvolvedores\n");
        printf("3. Atualizar Desenvolvedor\n");
        printf("4. Remover Desenvolvedor\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarDesenvolvedor();
                break;
            case 2:
                listarDesenvolvedores();
                break;
            case 3:
                atualizarDesenvolvedor();
                break;
            case 4:
                removerDesenvolvedor();
                break;
            case 5:
                salvarDesenvolvedores();
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
