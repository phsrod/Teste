#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int valor;
    struct NO *prox;
} NO;

typedef struct PILHA {
    NO *topo;
} PILHA;

PILHA* criarPilha(){
    PILHA *p = (PILHA*)malloc(sizeof(PILHA));
    p->topo = NULL;
    return p;
}

void inserirPilha(PILHA* pilha, int valor){
    NO* novo_no = (NO*)malloc(sizeof(NO));
    novo_no->valor = valor;
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
}

int removerPilha(PILHA* pilha){
    if (pilha->topo == NULL){
        return -1; // pilha vazia
    }
    NO* temp = pilha->topo;
    int val = temp->valor;
    pilha->topo = temp->prox;
    free(temp);
    return val;
}

void liberarPilha(PILHA* pilha){
    NO* atual = pilha->topo;
    while (atual != NULL){
        NO* temp = atual->prox;
        free(atual);
        atual = temp;
    }
    free(pilha);
}

void imprimirPilha(PILHA* pilha){
    NO* atual = pilha->topo;
    printf("Pilha: ");
    if (atual == NULL) {
        printf("(vazia)");
    }
    while (atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

int main(){
    PILHA* pilhaPrincipal = criarPilha();
    PILHA* pilhaUndo = criarPilha();
    int opcao;
    int num;

    printf("=========================================");
    printf("=== Gerenciador de Pilha com Undo ===\n");

    while (1){
        printf("\nMenu:\n");
        printf("1 - Inserir número\n");
        printf("2 - Remover número (pop)\n");
        printf("3 - Desfazer (undo)\n");
        printf("4 - Visualizar pilha\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // limpar entrada inválida
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o número para inserir: ");
                if (scanf("%d", &num) != 1) {
                    while(getchar() != '\n');
                    printf("Entrada inválida!\n");
                    break;
                }
                inserirPilha(pilhaPrincipal, num);
                printf("Número %d inserido na pilha principal.\n", num);
                break;

            case 2: {
                int removido = removerPilha(pilhaPrincipal);
                if (removido == -1) {
                    printf("Pilha principal vazia, nada para remover.\n");
                } else {
                    inserirPilha(pilhaUndo, removido);
                    printf("Número %d removido da pilha principal.\n", removido);
                }
                break;
            }

            case 3: {
                int undoVal = removerPilha(pilhaUndo);
                if (undoVal == -1) {
                    printf("Nada para desfazer!\n");
                } else {
                    inserirPilha(pilhaPrincipal, undoVal);
                    printf("Undo: número %d retornou para a pilha principal.\n", undoVal);
                }
                break;
            }

            case 4:
                imprimirPilha(pilhaPrincipal);
                break;

            case 5:
                printf("Saindo do programa.\n");
                liberarPilha(pilhaPrincipal);
                liberarPilha(pilhaUndo);
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}
