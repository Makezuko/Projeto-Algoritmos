#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_LISTA 10000 // Aumentando o tamanho da lista


// Função de Selection Sort
void SelectionSort(int *lista, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (lista[j] < lista[min_idx]) {
                min_idx = j;
            }
        }
        int temp = lista[min_idx];
        lista[min_idx] = lista[i];
        lista[i] = temp;
    }
}

// Função de Insertion Sort
void InsertionSort(int *lista, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int key = lista[i];
        int j = i - 1;
        while (j >= 0 && lista[j] > key) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = key;
    }
}

// Função de Bubble Sort
void bubbleSort(int *lista, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// Função de Merge Sort
void Merge(int *lista, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = lista[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = lista[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            lista[k] = L[i];
            i++;
        } else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        lista[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        lista[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void MergeSort(int *lista, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        MergeSort(lista, esquerda, meio);
        MergeSort(lista, meio + 1, direita);
        Merge(lista, esquerda, meio, direita);
    }
}

// Função de Quick Sort
void QuickSort(int *lista, int baixo, int alto) {
    if (baixo < alto) {
        int p = particao(lista, baixo, alto);
        QuickSort(lista, baixo, p - 1);
        QuickSort(lista, p + 1, alto);
    }
}

// Função de partição para o Quick Sort
int particao(int *lista, int baixo, int alto) {
    int pivo = lista[alto];
    int i = (baixo - 1);
    for (int j = baixo; j < alto; j++) {
        if (lista[j] < pivo) {
            i++;
            int temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp;
        }
    }
    int temp = lista[i + 1];
    lista[i + 1] = lista[alto];
    lista[alto] = temp;
    return (i + 1);
}

// Função de Heap Sort
void Heapify(int *lista, int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && lista[esquerda] > lista[maior])
        maior = esquerda;

    if (direita < n && lista[direita] > lista[maior])
        maior = direita;

    if (maior != i) {
        int temp = lista[i];
        lista[i] = lista[maior];
        lista[maior] = temp;

        Heapify(lista, n, maior);
    }
}

void HeapSort(int *lista, int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        Heapify(lista, tamanho, i);
    for (int i = tamanho - 1; i >= 0; i--) {
        int temp = lista[0];
        lista[0] = lista[i];
        lista[i] = temp;

        Heapify(lista, i, 0);
    }
}

// Função para imprimir a lista
void imprimirLista(int *lista, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

int main() {
    int lista[TAMANHO_LISTA];
    int i, j, num;
    int repetido;

    srand((unsigned)time(NULL));

    // Gera números aleatórios diferentes
    for (i = 0; i < TAMANHO_LISTA; i++) {
        do {
            repetido = 0;
            num = rand() % 10001; // Gera um número entre 0 e 10000

            // Verifica se o número já está na lista
            for (j = 0; j < i; j++) {
                if (lista[j] == num) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);

        lista[i] = num;
    }

    printf("Lista de %d números diferentes entre 0 e 10000 gerados aleatoriamente:\n", TAMANHO_LISTA);
    imprimirLista(lista, 10); // Imprime os primeiros 10 números da lista original

    int escolha;

    do {
        // Exibe o menu de opções
        printf("\nEscolha uma opção de ordenação:\n");
        printf("1. Selection Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("0. Sair\n");
        printf("Escolha uma opção (0-6): ");
        scanf("%d", &escolha);

        // Chama a função de ordenação correspondente
        clock_t inicio, fim;
        double tempo_cpu;

        switch (escolha) {
            case 1:
                inicio = clock();
                for (int k = 0; k < 5; k++) { 
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    SelectionSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 2:
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    InsertionSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 3:
                inicio = clock();
                for (int k = 0; k < 5; k++) { 
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    bubbleSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 4:
                inicio = clock();
                for (int k = 0; k < 5; k++) { 
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    MergeSort(copia, 0, TAMANHO_LISTA - 1);
                }
                fim = clock();
                break;
            case 5:
                inicio = clock();
                for (int k = 0; k < 5; k++) { 
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    QuickSort(copia, 0, TAMANHO_LISTA - 1);
                }
                fim = clock();
                break;
            case 6:
                inicio = clock();
                for (int k = 0; k < 5; k++) { 
                    int copia[TAMANHO_LISTA];
                    for (int l = 0; l < TAMANHO_LISTA; l++) {
                        copia[l] = lista[l];
                    }
                    HeapSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                continue;
        }

        tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %f segundos\n", tempo_cpu / 5); // Divide pelo número de repetições
        int copia[TAMANHO_LISTA];
        for (int l = 0; l < TAMANHO_LISTA; l++) {
            copia[l] = lista[l];
        }
        switch (escolha) {
            case 1: SelectionSort(copia, TAMANHO_LISTA); break;
            case 2: InsertionSort(copia, TAMANHO_LISTA); break;
            case 3: bubbleSort(copia, TAMANHO_LISTA); break;
            case 4: MergeSort(copia, 0, TAMANHO_LISTA - 1); break;
            case 5: QuickSort(copia, 0, TAMANHO_LISTA - 1); break;
            case 6: HeapSort(copia, TAMANHO_LISTA); break;
        }

    } while (escolha != 0);

    return 0;
}
