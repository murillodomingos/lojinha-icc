#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct loja
{
    int id, qtd;
    float preço;
    char nome[50];
} Estoque;

void insere_produto(Estoque *vet, int indice)
{
    vet[indice].id = indice;
    scanf("%s", vet[indice].nome);
    scanf("%d", &vet[indice].qtd);
    scanf("%f", &vet[indice].preço);
}

void aumenta_estoque(Estoque *vet)
{
    int indice, aumento;
    scanf("%d", &indice);
    scanf("%d", &aumento);
    vet[indice].qtd += aumento;
}

void modifica_preco(Estoque *vet)
{
    int indice;
    scanf("%d", &indice);
    scanf("%f", &vet[indice].preço);
}

void consulta_estoque(Estoque *vet, int indice)
{
    for (int i = 0; i < indice; i++)
    {
        printf("%d %s %d\n", vet[i].id, vet[i].nome, vet[i].qtd);
    }
    printf("--------------------------------------------------\n");
}

void consulta_saldo(float saldo)
{
    printf("Saldo: %.2f\n", saldo);
    printf("--------------------------------------------------\n");
}

void venda(Estoque *vet, float *saldo)
{
    float somapreço = 0;
    int indice;

    while(1)
    {
        scanf("%d", &indice);

        if (indice == -1)
        {
            break;
        }

        vet[indice].qtd--;

        if(vet[indice].qtd < 0)
        {
            vet[indice].qtd = 0;
        }
        else
        {
            printf("%s %.2f\n", vet[indice].nome, vet[indice].preço);
            somapreço += vet[indice].preço;
        }
    }
    *saldo += somapreço; 
    printf("Total: %.2f\n", somapreço);
    printf("--------------------------------------------------\n");
}

int main(void)
{
    int produtos_iniciais, indice = 0, count = 1;
    float saldo;
    char sigla[2];
    Estoque *vet;

    scanf("%d", &produtos_iniciais);
    vet = (Estoque*)malloc(produtos_iniciais * sizeof(Estoque));

    scanf("%f", &saldo);

    while(1)
    {
        scanf(" %s", sigla);

        if(strcmp(sigla, "FE") == 0)
        {
            break;
        }
        else if(strcmp(sigla, "IP") == 0)
        {
            insere_produto(vet, indice);
            indice++;
        }
        else if(strcmp(sigla, "AE") == 0)
        {
            aumenta_estoque(vet);
        }
        else if(strcmp(sigla, "MP") == 0)
        {
            modifica_preco(vet);
        }
        else if(strcmp(sigla, "VE") == 0)
        {
            venda(vet, &saldo);
        }
        else if(strcmp(sigla, "CE") == 0)
        {
            consulta_estoque(vet, indice);
        }
        else if(strcmp(sigla, "CS") == 0)
        {
            consulta_saldo(saldo);
        }

        if(indice > produtos_iniciais)
        {
            vet = (Estoque*)realloc(vet, produtos_iniciais + 10 * count * sizeof(Estoque));
            count++;
        }
    }
}
