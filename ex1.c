#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

struct Aluno {
    int matricula;
    char nome[50];
    struct Aluno* proximo;
};

struct TabelaHash {
    struct Aluno* tabela[TAMANHO_TABELA];
};

int funcaoHash(int matricula) {
    return matricula % TAMANHO_TABELA;
}

void inicializarTabela(struct TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->tabela[i] = NULL;
    }
}

void inserirAluno(struct TabelaHash *tabela, int matricula, const char nome[]) {
    int indice = funcaoHash(matricula);

    struct Aluno* novoAluno = (struct Aluno*)malloc(sizeof(struct Aluno));
    novoAluno->matricula = matricula;
    strcpy(novoAluno->nome, nome);
    novoAluno->proximo = NULL;

    if (tabela->tabela[indice] == NULL) {
        tabela->tabela[indice] = novoAluno;
    } else {
        struct Aluno* atual = tabela->tabela[indice];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoAluno;
    }
}

void buscarAluno(struct TabelaHash *tabela, int matricula) {
    int indice = funcaoHash(matricula);

    struct Aluno* atual = tabela->tabela[indice];
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            printf("Nome do aluno com matricula %d: %s\n", matricula, atual->nome);
            return;
        }
        atual = atual->proximo;
    }

    printf("Aluno com matricula %d nao encontrado.\n", matricula);
}

int main() {
    struct TabelaHash tabelaAlunos;
    inicializarTabela(&tabelaAlunos);

    int matricula;
    char nome[50];

    for (int i = 0; i < 10; i++) {  
        printf("Digite a matricula do aluno %d: ", i + 1);
        scanf("%d", &matricula);
        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%s", nome);
        inserirAluno(&tabelaAlunos, matricula, nome);
    }

    printf("\nDigite a matricula do aluno para buscar: ");
    scanf("%d", &matricula);
    buscarAluno(&tabelaAlunos, matricula);

    return 0;
}
