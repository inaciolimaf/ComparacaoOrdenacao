#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double potencia(int a, int b)
{
    int result = 1;
    for (int i = 0; i < b; i++)
        result = result * a;
    return result;
}

void BubbleSort(int n, int *v)
{
    int i, j, temp;
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (v[j] > v[j + 1])
            {
                temp = v[j]; // Troca
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void QuickSort(int n, int *v)
{
    if (n > 1)
    {
        int x = v[0];
        int a = 1;
        int b = n - 1;
        while (1)
        {
            while (a < n && v[a] <= x)
                a++;
            while (v[b] > x)
                b--;
            if (a < b)
            {
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
            else
                break;
        }
        v[0] = v[b];
        v[b] = x;
        QuickSort(b, v);
        QuickSort(n - a, &v[a]);
    }
}

void InsertionSort(int n, int *s)
{
    for (int i = 1; i < n; i++)
    {

        int j = i;

        while (j > 0 && s[j] <= s[j - 1])
        {
            int aux = s[j];
            s[j] = s[j - 1];
            s[j - 1] = aux;
            j -= 1;
        }
    }
}

void peneira(int *vet, int raiz, int fundo)
{
    int pronto, filhoMax, tmp;

    pronto = 0;
    while ((raiz * 2 <= fundo) && (!pronto))
    {
        if (raiz * 2 == fundo)
        {
            filhoMax = raiz * 2;
        }
        else if (vet[raiz * 2] > vet[raiz * 2 + 1])
        {
            filhoMax = raiz * 2;
        }
        else
        {
            filhoMax = raiz * 2 + 1;
        }

        if (vet[raiz] < vet[filhoMax])
        {
            tmp = vet[raiz];
            vet[raiz] = vet[filhoMax];
            vet[filhoMax] = tmp;
            raiz = filhoMax;
        }
        else
        {
            pronto = 1;
        }
    }
}

void HeapSort(int n, int *vet)
{
    int i, tmp;

    for (i = (n / 2); i >= 0; i--)
    {
        peneira(vet, i, n - 1);
    }

    for (i = n - 1; i >= 1; i--)
    {
        tmp = vet[0];
        vet[0] = vet[i];
        vet[i] = tmp;
        peneira(vet, 0, i - 1);
    }
}

void mergeSort_intercala(int *v, int esq, int meio, int dir)
{
    int i, j, k;
    int a_tam = meio - esq + 1;
    int b_tam = dir - meio;
    int *a = (int *)malloc(sizeof(int) * a_tam);
    int *b = (int *)malloc(sizeof(int) * b_tam);

    for (i = 0; i < a_tam; i++)
        a[i] = v[i + esq];
    for (i = 0; i < b_tam; i++)
        b[i] = v[i + meio + 1];

    for (i = 0, j = 0, k = esq; k <= dir; k++)
    {
        if (i == a_tam)
            v[k] = b[j++];
        else if (j == b_tam)
            v[k] = a[i++];
        else if (a[i] < b[j])
            v[k] = a[i++];
        else
            v[k] = b[j++];
    }
    free(a);
    free(b);
}

void mergeSort_ordena(int *v, int esq, int dir)
{
    if (esq == dir)
        return;
    int meio = (esq + dir) / 2;
    mergeSort_ordena(v, esq, meio);
    mergeSort_ordena(v, meio + 1, dir);
    mergeSort_intercala(v, esq, meio, dir);
    return;
}

void MergeSort(int n, int *v)
{
    mergeSort_ordena(v, 0, n - 1);
}

void executa_ordenacao(int numALgoritmo, int tam_vetor, int *v)
{
    if (numALgoritmo == 0)
    {
        BubbleSort(tam_vetor, v);
    }
    else if (numALgoritmo == 1)
    {
        InsertionSort(tam_vetor, v);
    }
    else if (numALgoritmo == 2)
    {
        QuickSort(tam_vetor, v);
    }
    else if (numALgoritmo == 3)
    {
        MergeSort(tam_vetor, v);
    }
    else if (numALgoritmo == 4)
    {
        HeapSort(tam_vetor, v);
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    clock_t t;
    const int TAM_MINIMO = 2, TAM_MAXIMO = 6;
    char algoritmos[5][20] = {"BubbleSort", "InsertionSort", "QuickSort", "MergeSort", "HeapSort"};
    for (int i = 0; i < 5; i++)
    {
        for (int j = TAM_MINIMO; j <= TAM_MAXIMO; j++)
        {
            int tam_vetor = potencia(10, j);
            int *v = (int *)malloc(tam_vetor * sizeof(int));
            for (int k = 0; k < tam_vetor; k++)
            {
                v[k] = rand();
            }
            t = clock();
            executa_ordenacao(i, tam_vetor, v);
            t = clock() - t;
            double tempoDecorrido = (double)(t*1000/ CLOCKS_PER_SEC);
            printf("\n %s: Tempo decorrido no tamanho %d: %lf", algoritmos[i], tam_vetor, tempoDecorrido);

            free(v);
        }
    }
    return 0;
}
