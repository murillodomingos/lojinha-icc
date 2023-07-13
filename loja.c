/* TRABALHO ICC 2023.1 - PROF. RUDNEI

    INTEGRANTES: -BRUNO NEVES BOA SORTE 14562528
                 -CAIO URAMOTO EVANGELISTA 14777351
                 -MURILLO DOMINGOS DE ALMEIDA 14804083
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicao da struct
typedef struct loja
{
    int id, qtd;
    float preco;
    char nome[50];
} Estoque;

// rotina de inserção de novos produtos
void insere_produto(Estoque *vet, int indice)
{
    vet[indice].id = indice;
    scanf("%s", vet[indice].nome);
    scanf("%d", &vet[indice].qtd);
    scanf("%f", &vet[indice].preco);
}

// rotina de aumentar o numero de itens de certo produto
void aumenta_estoque(Estoque *vet)
{
    int indice, aumento;
    scanf("%d", &indice);
    scanf("%d", &aumento);
    vet[indice].qtd += aumento;
}

// rotina que modifica o preco de determinado produto
void modifica_preco(Estoque *vet)
{
    int indice;
    scanf("%d", &indice);
    scanf("%f", &vet[indice].preco);
}

// rotina que consulta o estoque do mercado
void consulta_estoque(Estoque *vet, int indice)
{
    for (int i = 0; i < indice; i++)
    {
        printf("%d %s %d\n", vet[i].id, vet[i].nome, vet[i].qtd);
    }
    printf("--------------------------------------------------\n");
}

// rotina que consulta o saldo em caixa
void consulta_saldo(float saldo)
{
    printf("Saldo: %.2f\n", saldo);
    printf("--------------------------------------------------\n");
}

// rotina de venda dos produtos
void venda(Estoque *vet, float *saldo)
{
    float somapreco = 0;
    int indice;

    // loop de venda terminado em -1
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
            printf("%s %.2f\n", vet[indice].nome, vet[indice].preco);
            somapreco += vet[indice].preco;
        }
    }
    *saldo += somapreco; 
    printf("Total: %.2f\n", somapreco);
    printf("--------------------------------------------------\n");
}

int main(void)
{
    // definicao das variaveis
    int produtos_iniciais, indice = 0, count = 1, linha = 0;
    float saldo;
    char sigla[2], linha_arquivo[100];;

    Estoque *vet = NULL;
    FILE *fp;

    // caso o arquivo nao esteja sao puxados os dados dele 
    if(((fp = fopen("estoque.txt", "r"))) != NULL)
    {
        while(fgets(linha_arquivo, sizeof(linha_arquivo), fp) != NULL)
        {
            linha++;
        }

        indice = linha - 1;
        produtos_iniciais = linha -1;
        vet = (Estoque*)malloc(indice * sizeof(Estoque));

        fseek(fp, 0, SEEK_SET);
        // linha 1 saldo
        fscanf(fp,"%f", &saldo);
        // linha 2 em diante produtos
        for(int i = 0; i < linha - 1; i++)
        {
            fscanf(fp, "%d %s %d %f", &vet[i].id, vet[i].nome, &vet[i].qtd, &vet[i].preco);
        }

        fclose(fp);
    }
    // caso nao segue execucao perguntadno a qtd de produtos e o saldo inicial em caixa
    else
    {
        scanf("%d", &produtos_iniciais);
        vet = (Estoque*)malloc(produtos_iniciais * sizeof(Estoque));
        scanf("%f", &saldo);
    }

    // verificacao dos comandos
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

            if(indice == produtos_iniciais)
            {
                vet = (Estoque*)realloc(vet, (produtos_iniciais + 10 * count) * sizeof(Estoque));
                count++;
            }
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
    }

    // imputa no arquivo as alterações feitas
    fp = fopen("estoque.txt", "w");

    fprintf(fp, "%f\n", saldo);
    for(int i = 0; i < indice; i++)
    {
        fprintf(fp, "%d %s %d %f\n", vet[i].id, vet[i].nome, vet[i].qtd, vet[i].preco);
    }
    fclose(fp);

    free(vet);
    vet = NULL;
}