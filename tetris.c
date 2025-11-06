#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

struct Peca {
    char tipo;
    int id;
};

struct Fila {
    struct Peca itens[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
};

void iniciarFila(struct Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaVazia(struct Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(struct Fila *f) {
    return f->tamanho == TAM_FILA;
}

struct Peca novaPeca(int id) {
    struct Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

void entrarFila(struct Fila *f, struct Peca p) {
    if (filaCheia(f)) return;
    
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

struct Peca sairFila(struct Fila *f) {
    struct Peca p = {' ', -1};
    if (filaVazia(f)) return p;
    
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return p;
}

void mostrarFila(struct Fila *f) {
    printf("Fila: ");
    if (filaVazia(f)) {
        printf("Vazia\n");
        return;
    }
    
    int i = f->frente;
    for (int count = 0; count < f->tamanho; count++) {
        printf("[%c%d] ", f->itens[i].tipo, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    struct Fila fila;
    int opcao;
    int id = 0;
    
    srand(time(NULL));
    iniciarFila(&fila);
    
    for (int i = 0; i < TAM_FILA; i++) {
        entrarFila(&fila, novaPeca(id++));
    }
    
    do {
        mostrarFila(&fila);
        printf("\n1 - Jogar peça\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            struct Peca p = sairFila(&fila);
            if (p.id != -1) {
                printf("Jogou: [%c%d]\n", p.tipo, p.id);
                entrarFila(&fila, novaPeca(id++));
            }
        }
        
    } while(opcao != 0);
    
    return 0;
}