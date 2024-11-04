#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para exibir a lista
void exibirLista(int lista[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

// Selection Sort
void SelectionSort(int lista[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (lista[j] < lista[minIndex]) {
                minIndex = j;
            }
        }
        // Troca
        int temp = lista[i];
        lista[i] = lista[minIndex];
        lista[minIndex] = temp;
    }
    printf("Lista ordenada com Selection Sort:\n");
    exibirLista(lista, tamanho);
}

// Insertion Sort
void InsertionSort(int lista[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int key = lista[i];
        int j = i - 1;
        while (j >= 0 && lista[j] > key) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = key;
    }
    printf("Lista ordenada com Insertion Sort:\n");
    exibirLista(lista, tamanho);
}

// Bubble Sort
void bubbleSort(int lista[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                // Troca
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    printf("Lista ordenada com Bubble Sort:\n");
    exibirLista(lista, tamanho);
}

// Merge Sort - Funções auxiliares
void merge(int lista[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = lista[left + i];
    for (int j = 0; j < n2; j++) R[j] = lista[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) lista[k++] = L[i++];
        else lista[k++] = R[j++];
    }
    while (i < n1) lista[k++] = L[i++];
    while (j < n2) lista[k++] = R[j++];
}

void MergeSort(int lista[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(lista, left, mid);
        MergeSort(lista, mid + 1, right);
        merge(lista, left, mid, right);
    }
}

// Função para Merge Sort
void chamarMergeSort(int lista[], int tamanho) {
    MergeSort(lista, 0, tamanho - 1);
    printf("Lista ordenada com Merge Sort:\n");
    exibirLista(lista, tamanho);
}

// Quick Sort - Funções auxiliares
int partition(int lista[], int low, int high) {
    int pivot = lista[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (lista[j] < pivot) {
            i++;
            int temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp;
        }
    }
    int temp = lista[i + 1];
    lista[i + 1] = lista[high];
    lista[high] = temp;
    return (i + 1);
}

void QuickSort(int lista[], int low, int high) {
    if (low < high) {
        int pi = partition(lista, low, high);
        QuickSort(lista, low, pi - 1);
        QuickSort(lista, pi + 1, high);
    }
}

// Função para Quick Sort
void chamarQuickSort(int lista[], int tamanho) {
    QuickSort(lista, 0, tamanho - 1);
    printf("Lista ordenada com Quick Sort:\n");
    exibirLista(lista, tamanho);
}

// Heap Sort - Funções auxiliares
void heapify(int lista[], int tamanho, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < tamanho && lista[left] > lista[largest]) largest = left;
    if (right < tamanho && lista[right] > lista[largest]) largest = right;

    if (largest != i) {
        int temp = lista[i];
        lista[i] = lista[largest];
        lista[largest] = temp;
        heapify(lista, tamanho, largest);
    }
}

void HeapSort(int lista[], int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--) heapify(lista, tamanho, i);
    for (int i = tamanho - 1; i >= 0; i--) {
        int temp = lista[0];
        lista[0] = lista[i];
        lista[i] = temp;
        heapify(lista, i, 0);
    }
    printf("Lista ordenada com Heap Sort:\n");
    exibirLista(lista, tamanho);
}

int main() {
    int lista[3000];
    int tamanho = 3000;
    int i, j, num;
    int repetido;

    srand((unsigned) time(NULL));

    for (i = 0; i < tamanho; i++) {
        do {
            repetido = 0;
            num = rand() % 10001;

            for (j = 0; j < i; j++) {
                if (lista[j] == num) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);

        lista[i] = num;
    }

    printf("Lista de 1000 números diferentes entre 0 e 10000:\n");
    exibirLista(lista, tamanho);

    int escolha;
    do {
        printf("\nEscolha um algoritmo de ordenação:\n");
        printf("1. Selection Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("0. Sair\n");
        printf("Escolha uma opção (0-6): ");
        
        scanf("%d", &escolha);

        int listaCopia[tamanho];
        for (i = 0; i < tamanho; i++) listaCopia[i] = lista[i];

        switch (escolha) {
            case 1: SelectionSort(listaCopia, tamanho); break;
            case 2: InsertionSort(listaCopia, tamanho); break;
            case 3: bubbleSort(listaCopia, tamanho); break;
            case 4: chamarMergeSort(listaCopia, tamanho); break;
            case 5: chamarQuickSort(listaCopia, tamanho); break;
            case 6: HeapSort(listaCopia, tamanho); break;
            case 0: printf("Saindo do menu...\n"); break;
            default: printf("Opção inválida! Por favor, escolha uma opção entre 0 e 6.\n");
        }
    } while (escolha != 0);

    return 0;
}
