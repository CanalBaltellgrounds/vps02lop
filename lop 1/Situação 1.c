#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("producao.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            totalViagens++;
        }
    }
    fclose(arq);
}

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("%-10s  %-20s  %-12s  %-20s  %-20s  %-10s  %-10s  %-10s\n", "Matricula", "Funcionario", "Data", "Origem", "Destino", "Distância", "Preço", "Total");
    for(i=0; i < totalViagens; i++)
    {
        printf("%-10d  %-20s  %-12s  %-20s  %-20s  %-10d  %-10.2f  %-10.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total);
    }
}

void calcularReembolso()
{
    float precoLitroCombustivel = 4.50; // Exemplo: preço do litro do combustível
    float percentualReembolso = 1.0 / 3.0; // 33.33% ou 1/3 do valor do combustível pela distância

    for (i = 0; i < totalViagens; i++)
    {
        float reembolso = (precoLitroCombustivel * viagens[i].distancia) / 3.0;
        viagens[i].total = reembolso;
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularReembolso();
    mostrarDados();
    return 0;
}

