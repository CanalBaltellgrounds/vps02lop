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
    arq = fopen("viagens.csv", "r");
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

float Reembolso(int distancia, float preco) {
    return distancia * preco / 3;
}

void calcularTotal() {
    float totalGeral = 0;
    for(i=0; i < totalViagens; i++) {
        viagens[i].total = Reembolso(viagens[i].distancia, viagens[i].preco);
        totalGeral += viagens[i].total;
    }
    printf("\nValor total que a empresa vai ter que reembolsar: R$ %.2f\n", totalGeral);
}

void mostrarDados()
{
    float totalFuncionario = 0;
    char ultimoFuncionario[50];
    printf("Viagens ACME:\n");
    printf("Matricula\tFuncionario\tData\tOrigem\tDestino\tDist�ncia\tPre�o\tTotal\n");
    for(i=0; i < totalViagens; i++)
    {
        if(strcmp(viagens[i].funcionario, ultimoFuncionario) != 0) {
            if(strlen(ultimoFuncionario) > 0) {
                printf("\nTotal do reembolso para %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
            }
            strcpy(ultimoFuncionario, viagens[i].funcionario);
            totalFuncionario = 0;
        }
        printf("%d\t%s\t%s\t%s\t%s\t%d\t%.2f\t%.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total);
        totalFuncionario += viagens[i].total;
    }
    printf("\nTotal do reembolso para %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
}

int main(){
    setlocale(LC_ALL, "");
    carregaDados();
    calcularTotal();
    mostrarDados();
    return 0;
}
