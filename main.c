#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   

// Definição de uma constante TAMANHO_LISTA que será o tamanho do vetor/lista
#define TAMANHO_LISTA 100000 

// Declaração de todas as funções utilizadas no código
void SelectionSort(int *lista, int tamanho);
void InsertionSort(int *lista, int tamanho);
void bubbleSort(int *lista, int tamanho);
void MergeSort(int *lista, int esquerda, int direita);
void QuickSort(int *lista, int baixo, int alto);
void HeapSort(int *lista, int tamanho);
void gerarLista(int *lista, int tamanho);
void copiaLista(int *origem, int *destino, int tamanho);
void imprimirLista(int *lista, int tamanho);

// Função que copia os elementos de uma lista (origem) para outra lista (destino)
void copiaLista(int *origem, int *destino, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];  // Copia elemento por elemento
    }
}

// Função para gerar uma lista de números aleatórios entre 0 e tamanho-1
void gerarLista(int *lista, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        lista[i] = i; // Preenche a lista com números sequenciais de 0 a tamanho-1
    }

    // Embaralha a lista usando o algoritmo Fisher-Yates para gerar números aleatórios
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Gera um índice aleatório entre 0 e i
        int temp = lista[i];
        lista[i] = lista[j];        // Troca os elementos
        lista[j] = temp;            // Troca os elementos
    }
}

// Função de Selection Sort: Ordena a lista selecionando o menor elemento repetidamente
void SelectionSort(int *lista, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int min_idx = i;  // Assume que o primeiro elemento é o menor
        for (int j = i + 1; j < tamanho; j++) {
            if (lista[j] < lista[min_idx]) {
                min_idx = j;  // Se encontrar um elemento menor, atualiza o índice
            }
        }
        // Troca o elemento da posição i com o mínimo encontrado
        int temp = lista[min_idx];
        lista[min_idx] = lista[i];
        lista[i] = temp;
    }
}

// Função de Insertion Sort: Ordena a lista inserindo os elementos nas posições corretas
void InsertionSort(int *lista, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int key = lista[i];  // Armazena o elemento atual para comparações
        int j = i - 1;
        // Move os elementos maiores para a direita
        while (j >= 0 && lista[j] > key) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = key;  // Insere o elemento na posição correta
    }
}

// Função de Bubble Sort: Ordena a lista trocando elementos adjacentes em ordem crescente
void bubbleSort(int *lista, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                // Troca os elementos adjacentes se estiverem na ordem errada
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// Função de Merge Sort: Divide a lista em duas metades e as ordena recursivamente
void Merge(int *lista, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;  // Tamanho da sublista da esquerda
    int n2 = direita - meio;       // Tamanho da sublista da direita

    // Criação de duas sublistas temporárias
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro ao alocar memória para Merge Sort.\n");
        exit(EXIT_FAILURE);
    }

    // Preenche as sublistas temporárias
    for (int i = 0; i < n1; i++)
        L[i] = lista[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = lista[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    // Mescla as duas sublistas de volta para a lista original
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

    // Copia os elementos restantes de L, se houver
    while (i < n1) {
        lista[k] = L[i];
        i++;
        k++;
    }
    // Copia os elementos restantes de R, se houver
    while (j < n2) {
        lista[k] = R[j];
        j++;
        k++;
    }

    // Libera a memória alocada para as sublistas
    free(L);
    free(R);
}

// Função recursiva de Merge Sort
void MergeSort(int *lista, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        MergeSort(lista, esquerda, meio);     // Ordena a primeira metade
        MergeSort(lista, meio + 1, direita);  // Ordena a segunda metade
        Merge(lista, esquerda, meio, direita); // Mescla as duas metades
    }
}

// Função de partição do Quick Sort
int particao(int *lista, int baixo, int alto) {
    int pivo = lista[alto];  // Seleciona o último elemento como pivo
    int i = baixo - 1;       // Índice do menor elemento

    for (int j = baixo; j < alto; j++) {
        if (lista[j] < pivo) {
            i++;  // Encontra o próximo elemento menor que o pivo
            int temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp;  // Troca
        }
    }

    // Coloca o pivo na sua posição final
    int temp = lista[i + 1];
    lista[i + 1] = lista[alto];
    lista[alto] = temp;
    return (i + 1);  // Retorna o índice do pivo
}

// Função recursiva de Quick Sort
void QuickSort(int *lista, int baixo, int alto) {
    if (baixo < alto) {
        int p = particao(lista, baixo, alto);  // Divide a lista em duas partes
        QuickSort(lista, baixo, p - 1);        // Ordena a primeira parte
        QuickSort(lista, p + 1, alto);         // Ordena a segunda parte
    }
}

// Função de Heap Sort: Utiliza a estrutura de heap (árvore binária) para ordenar
void Heapify(int *lista, int n, int i) {
    int maior = i;           // Assume que o nó atual é o maior
    int esquerda = 2 * i + 1; // Índice do filho esquerdo
    int direita = 2 * i + 2;  // Índice do filho direito

    if (esquerda < n && lista[esquerda] > lista[maior]) 
        maior = esquerda;    // Se o filho esquerdo é maior, atualiza o índice maior

    if (direita < n && lista[direita] > lista[maior]) 
        maior = direita;     // Se o filho direito é maior, atualiza o índice maior

    if (maior != i) {  // Se o maior não é o nó atual, troca os elementos
        int temp = lista[i];
        lista[i] = lista[maior];
        lista[maior] = temp;
        Heapify(lista, n, maior);  // Recursivamente arruma o heap
    }
}
// Função principal de Heap Sort
void HeapSort(int *lista, int tamanho) {
    // Constrói o heap a partir da metade da lista
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        Heapify(lista, tamanho, i);  // Constrói um heap (max-heap) para toda a lista
    
    // Extrai os elementos do heap um por um, trocando-os com o último elemento não ordenado
    for (int i = tamanho - 1; i >= 0; i--) {
        // Troca o elemento raiz (maior valor) com o último elemento não ordenado
        int temp = lista[0];
        lista[0] = lista[i];
        lista[i] = temp;
        
        // Chama Heapify para reestruturar o heap e manter a propriedade de heap
        Heapify(lista, i, 0);  // Para a parte não ordenada da lista
    }
}

// Função para imprimir os elementos de uma lista
void imprimirLista(int *lista, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);  // Imprime cada elemento seguido de um espaço
    }
    printf("\n");  // Adiciona uma nova linha no final da impressão
}

int main() {
    // Declaração de variáveis
    int lista[TAMANHO_LISTA];  // Lista principal de tamanho TAMANHO_LISTA
    int copia[TAMANHO_LISTA];  // Lista auxiliar para fazer cópias durante os testes
    int escolha;  // Variável para armazenar a opção escolhida pelo usuário

    srand((unsigned)time(NULL));  // Inicializa o gerador de números aleatórios com base no tempo atual

    gerarLista(lista, TAMANHO_LISTA);  // Gera a lista com números aleatórios
    printf("Alguns dos números gerados entre 0 e %d gerados aleatoriamente:\n", TAMANHO_LISTA);
    imprimirLista(lista, 10);  // Imprime os primeiros 10 números gerados

    do {
        // Exibe o menu de opções de ordenação
        printf("\nEscolha uma opção de ordenação:\n");
        printf("1. Selection Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("0. Sair\n");
        printf("Escolha uma opção (0-6): ");
        scanf("%d", &escolha);  // Lê a escolha do usuário

        clock_t inicio, fim;  // Variáveis para medir o tempo de execução
        double tempo_cpu;     // Variável para armazenar o tempo médio de execução

        switch (escolha) {  // Seleciona o algoritmo com base na escolha do usuário
            case 1:  // Selection Sort
                inicio = clock();  // Marca o início do tempo
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);  // Faz uma cópia da lista
                    SelectionSort(copia, TAMANHO_LISTA);  // Ordena usando Selection Sort
                }
                fim = clock();  // Marca o fim do tempo
                break;
            case 2:  // Insertion Sort
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);
                    InsertionSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 3:  // Bubble Sort
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);
                    bubbleSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 4:  // Merge Sort
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);
                    MergeSort(copia, 0, TAMANHO_LISTA - 1);
                }
                fim = clock();
                break;
            case 5:  // Quick Sort
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);
                    QuickSort(copia, 0, TAMANHO_LISTA - 1);
                }
                fim = clock();
                break;
            case 6:  // Heap Sort
                inicio = clock();
                for (int k = 0; k < 5; k++) {
                    copiaLista(lista, copia, TAMANHO_LISTA);
                    HeapSort(copia, TAMANHO_LISTA);
                }
                fim = clock();
                break;
            case 0:  // Sai do programa
                printf("Saindo...\n");
                break;
            default:  // Caso o usuário insira uma opção inválida
                printf("Opção inválida.\n");
                continue;  // Continua o loop sem sair
        }

        // Se a opção escolhida foi válida, calcula e exibe o tempo médio de execução
        if (escolha >= 1 && escolha <= 6) {
            tempo_cpu = ((double)(fim - inicio)) / (CLOCKS_PER_SEC * 5);  // Calcula o tempo médio
            printf("Tempo médio de execução: %f segundos\n", tempo_cpu);
        }

    } while (escolha != 0);  // O loop continua até o usuário escolher sair

    return 0;  // Retorna 0 indicando que o programa foi executado com sucesso
}