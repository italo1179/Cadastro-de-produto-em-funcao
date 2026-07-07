#include <stdio.h>
#include <string.h>
#define max_prd 20
#define in 0

void calc_subtotal(float prd_preco[], int prd_quantidade[], int n, float vlr_subtotal[], float *soma_total, float *vlr_total)
{
    for (int i = 0; i < n; i++)
    {
        vlr_subtotal[i] = prd_preco[i] * prd_quantidade[i];
    }
    for (int i = 0; i < n; i++)
    {
        *soma_total += vlr_subtotal[i];
    }
    *vlr_total = *soma_total;
    return;
}

float aplicar_desconto(float *soma_total, float *aux, float *porcentagem_desc, float vlr_total)
{
    char cupom10[8] = "PROMO10";
    char cupom25[8] = "PROMO25";
    char c;
    char cupomuser[50];

    printf("Você tem cupom de desconto?(s/n)");
    fflush(stdin);
    scanf(" %c", &c);
    do
    {
        printf("Escreva seu cupom:");
        scanf("%19s", cupomuser);
        if (strcmp(cupomuser, cupom10) == 0)
        {
            *aux = *soma_total * 0.10;
            *soma_total = *soma_total - *aux;
            *porcentagem_desc = 10;
            printf("Cupom valido!\n");
            printf("Deseja usar outro cupom?(s/n)");
            fflush(stdin);
            scanf(" %c", &c);
        }
        else if (strcmp(cupomuser, cupom25) == 0)
        {
            *aux = *soma_total * 0.25;
            *soma_total = *soma_total - *aux;
            *porcentagem_desc = 25;
            printf("Cupom valido!\n");
            printf("Deseja usar outro cupom?(s/n)");
            fflush(stdin);
            scanf(" %c", &c);
        }
        else
        {
            printf("Codigo invalido!\n");
            printf("Tentar novamente?(s/n)\n");
            fflush(stdin);
            scanf(" %c", &c);
        }
    } while (c == 's' || c == 'S');
}

int main()
{
    char prd_nome[max_prd][max_prd];
    int i;
    int n = 0;
    char c;
    int prd_quantidade[max_prd];
    float prd_preco[max_prd];
    float vlr_subtotal[max_prd];
    float soma_total = 0;       // valor do desconto
    float porcentagem_desc = 0; // valor da porcentagem do desconto (10 ou 25)
    float aux = 0;
    float vlr_total; // valor sem o desconto

    printf("== Caixa Registradora ==\n");
    printf("Cadastro de produtos:\n");
    c = 's';

    do
    {
        printf("Nome do Produto:");
        scanf("%49s", prd_nome[n]);
        printf("Preço:");
        scanf("%f", &prd_preco[n]);
        printf("Quantidade do Produto:");
        scanf("%d", &prd_quantidade[n]);
        printf("Quer cadastrar outro produto?(s/n)");
        scanf(" %c", &c);
        n++;
    } while (c == 's' || c == 'S');

    calc_subtotal(prd_preco, prd_quantidade, n, vlr_subtotal, &soma_total, &vlr_total);

    aplicar_desconto(&soma_total, &aux, c, &porcentagem_desc, vlr_total);

    printf("\n=====   CUPOM FISCAL   =====\n");
    for (i = 0; i < n; i++)
    {
        printf("%dx ", prd_quantidade[i]);
        printf("%s ", prd_nome[i]);
        printf("  %.2f ", prd_preco[i]);
        printf(" --> R$ %.2f\n", vlr_subtotal[i]);
    }
    printf("------------------------\n");
    printf("Subtotal:          R$ %.2f\n", vlr_total);
    printf("Desconto(%.0f%%):    R$ %.2f\n", porcentagem_desc, aux);
    printf("Total:              R$ %.2f\n", soma_total);

    return 0;
}
