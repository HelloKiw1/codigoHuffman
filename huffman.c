#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 256

typedef struct no{

    unsigned char caracter;
    unsigned int frequencia;
    struct no *esq, *dir;

}No;

typedef struct{

    int tamanho, capacidade;
    No **vetor;

}MinHeap;


No* criar_no(unsigned char caracter, unsigned int frequencia){

    No *novo = malloc(sizeof(No));
    novo->caracter = caracter;
    novo->frequencia = frequencia;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}


MinHeap* criar_heap(int capacidade){

    MinHeap *heap = malloc(sizeof(MinHeap));

    heap->tamanho = 0;
    heap->capacidade = capacidade;
    heap->vetor = malloc( capacidade * sizeof(No*));

    return heap;
}

void trocar(No **a, No **b){

    No *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap *heap, int i){

    int menor = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if(esq < heap->tamanho && heap->vetor[esq]->frequencia < heap->vetor[menor]->frequencia)

        menor = esq;

    if(dir < heap->tamanho && heap->vetor[dir]->frequencia < heap->vetor[menor]->frequencia)

        menor = dir;

    if(menor != i){

        trocar(&heap->vetor[i], &heap->vetor[menor]);
        min_heapify(heap, menor);
    }
}

void inserir_heap(MinHeap *heap, No *novo){

    int i = heap->tamanho;

    heap->tamanho++;

    while(i && novo->frequencia < heap->vetor[(i-1)/2]->frequencia){

        heap->vetor[i] =
            heap->vetor[(i-1)/2];

        i = (i-1)/2;
    }

    heap->vetor[i] = novo;
}

No* remover_minimo(MinHeap *heap){

    No *temp = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;
    min_heapify(heap, 0);

    return temp;
}



void inicializar_tabela_com_zero(unsigned int tab[]){

    int i;

    for(i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preencher_tabela_frequencia(unsigned char *texto, unsigned int tab[], long tam){

    long i;

    for(i = 0; i < tam; i++)
        tab[texto[i]]++;
}



void preencher_heap(unsigned int tabela[], MinHeap *heap){

    int i;

    for(i = 0; i < TAM; i++){

        if(tabela[i] > 0){

            inserir_heap(heap, criar_no(i, tabela[i]));
        }
    }
}


No* montar_arvore(MinHeap *heap){

    No *primeiro, *segundo, *novo;

    while(heap->tamanho > 1){

        primeiro = remover_minimo(heap);
        segundo =remover_minimo(heap);
        novo =criar_no('+', primeiro->frequencia + segundo->frequencia);
        novo->esq = primeiro;
        novo->dir = segundo;

        inserir_heap(heap, novo);
    }

    return remover_minimo(heap);
}


int calcular_altura_arvore(No *raiz){

    int esq,dir;

    if(raiz == NULL)
        return -1;

    esq = calcular_altura_arvore(raiz->esq) + 1;

    dir = calcular_altura_arvore(raiz->dir) + 1;

    if(esq > dir)
        return esq;

    return dir;
}



char** alocar_memoria_dicionario(int colunas){

    char **dicionario;

    int i;
    dicionario = malloc(sizeof(char*) * TAM);

    for(i = 0; i < TAM; i++){

        dicionario[i] = calloc(colunas,sizeof(char));
    }

    return dicionario;
}

void criar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){

    char esquerda[colunas], direita[colunas];

    if(raiz->esq == NULL && raiz->dir == NULL){

        strcpy(
            dicionario[raiz->caracter],caminho);
    }

    else{

        strcpy(esquerda, caminho);
        strcpy(direita, caminho);
        strcat(esquerda, "0");
        strcat(direita, "1");
        criar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        criar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}


long calcular_tamanho_string(char **dicionario, unsigned char *texto, long tam){

    long i, tamanho = 0;

    for(i = 0; i < tam; i++){

        tamanho += strlen(dicionario[texto[i]]);
    }

    return tamanho + 1;
}

char* codificar(char **dicionario, unsigned char *texto, long tam){

    long i, tamanho = calcular_tamanho_string(dicionario, texto, tam);
    char *codigo = calloc(tamanho, sizeof(char));

    for(i = 0; i < tam; i++){

        strcat(codigo,dicionario[texto[i]]);
    }

    return codigo;
}


unsigned int bit_um(unsigned char byte, int i){

    unsigned char mascara = (1 << i);

    return byte & mascara;
}

int calcular_lixo(char *codificado){

    int tam = strlen(codificado), resto = tam % 8;

    if(resto == 0)
        return 0;

    return 8 - resto;
}



long descobrir_tamanho(char *nome){

    FILE *arq = fopen(nome, "rb");
    long tam;

    if(arq){fseek(arq, 0, SEEK_END);

        tam = ftell(arq);
        fclose(arq);

        return tam;
    }

    printf("\nErro ao abrir arquivo\n");

    return 0;
}

void ler_arquivo(unsigned char *texto, char *nome){

    FILE *arq = fopen(nome, "rb");
    long i = 0;
    int byte;

    if(arq){

        while((byte = fgetc(arq)) != EOF){

            texto[i] = byte;

            i++;
        }

        fclose(arq);
    }

    else
        printf("\nErro ao abrir arquivo\n");
}


void compactar(char *saida, char *codificado, unsigned int tabela[]){

    FILE *arquivo = fopen(saida, "wb");
    int i, j = 7;
    unsigned char mascara, byte = 0;

    if(arquivo){

        int quantidade = 0;

        for(i = 0; i < TAM; i++){

            if(tabela[i] > 0)
                quantidade++;
        }

        fwrite(&quantidade, sizeof(int), 1, arquivo);

        for(i = 0; i < TAM; i++){

            if(tabela[i] > 0){

                unsigned char c = i;
                fwrite(&c, sizeof(unsigned char),1,arquivo);
                fwrite(&tabela[i], sizeof(unsigned int), 1, arquivo);
            }
        }

        unsigned char lixo = calcular_lixo(codificado);
        fwrite(&lixo, sizeof(unsigned char), 1, arquivo);

        i = 0;

        while(codificado[i] != '\0'){

            mascara = 1;

            if(codificado[i] == '1'){
                mascara = mascara << j;
                byte = byte | mascara;
            }

            j--;

            if(j < 0){

                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                byte = 0;
                j = 7;
            }

            i++;
        }

        if(j != 7){

            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
        }

        fclose(arquivo);
    }

    else
        printf("\nErro ao abrir arquivo\n");
}


void ler_cabecalho(
    FILE *arquivo, unsigned int tabela[], unsigned char *lixo){
    int quantidade, i;
    unsigned char c;
    unsigned int freq;

    fread(&quantidade, sizeof(int),1, arquivo);

    inicializar_tabela_com_zero(tabela);

    for(i = 0; i < quantidade; i++){

        fread(&c, sizeof(unsigned char),1, arquivo);
        fread(&freq, sizeof(unsigned int),1, arquivo);

        tabela[c] = freq;
    }

    fread(lixo,sizeof(unsigned char),1,arquivo);
}

void descompactar(char *entrada,char *saida){

    FILE *arquivo = fopen(entrada, "rb");
    FILE *out = fopen(saida, "wb");

    unsigned int tabela[TAM];
    unsigned char lixo;
    MinHeap *heap;
    No *arvore;
    No *aux;
    unsigned char byte;
    long tamanho_arquivo, bytes_payload, atual = 0;
    int i;

    if(arquivo && out){

        ler_cabecalho(arquivo, tabela, &lixo);
        heap = criar_heap(TAM);
        preencher_heap(tabela, heap);
        arvore = montar_arvore(heap);
        aux = arvore;
        fseek(arquivo, 0, SEEK_END);
        tamanho_arquivo = ftell(arquivo);
        rewind(arquivo);
        int quantidade = 0;

        for(i = 0; i < TAM; i++){

            if(tabela[i] > 0)
                quantidade++;
        }

        fseek(arquivo, sizeof(int) + quantidade * (1 + sizeof(unsigned int)) + sizeof(unsigned char), SEEK_SET );
        bytes_payload = tamanho_arquivo - ftell(arquivo);

        while(fread(&byte, sizeof(unsigned char), 1, arquivo)){

            atual++;

            int limite = 0;

            if(atual == bytes_payload)
                limite = lixo;

            for(i = 7; i >= limite; i--){

                if(bit_um(byte, i))
                    aux = aux->dir;

                else
                    aux = aux->esq;

                if(aux->esq == NULL &&
                   aux->dir == NULL){

                    fwrite(&(aux->caracter), sizeof(unsigned char),1, out );

                    aux = arvore;
                }
            }
        }

        fclose(arquivo);

        fclose(out);
    }

    else
        printf("\nErro ao abrir arquivos\n");
}

int main(int argc, char *argv[]){

    setlocale(LC_ALL,"Portuguese");

    if(argc < 4){

        printf("\nUso:\n");
        printf("\nCompactar:\n" "./huffman -c entrada saida.huff\n");
        printf("\nDescompactar:\n" "./huffman -d entrada.huff saida\n");

        return 0;
    }

    if(strcmp(argv[1], "-c") == 0){

unsigned char *texto;
unsigned int tabela[TAM];
MinHeap *heap;
No *arvore;
int colunas;
char **dicionario, *codificado;
long tam;

tam = descobrir_tamanho(argv[2]);

texto = calloc(tam + 1, sizeof(unsigned char));

ler_arquivo(texto, argv[2]);

inicializar_tabela_com_zero(tabela);

preencher_tabela_frequencia(texto,tabela,tam);

heap = criar_heap(TAM);

preencher_heap(tabela,heap);

arvore = montar_arvore(heap);

colunas = calcular_altura_arvore(arvore) + 1;

dicionario = alocar_memoria_dicionario(colunas);

criar_dicionario(dicionario, arvore, "",colunas);

codificado = codificar(dicionario,texto,tam);

compactar(argv[3],codificado, tabela);
printf("\nArquivo compactado com sucesso!\n");}

    else if(strcmp(argv[1], "-d") == 0){

        descompactar(argv[2],argv[3]);
        printf("\nArquivo descompactado com sucesso!\n");
    }

    else{

        printf("\nErro\n");
    }

    return 0;
}