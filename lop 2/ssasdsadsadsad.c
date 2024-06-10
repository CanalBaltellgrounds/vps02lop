#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAQUINAS 4
#define NUM_DIAS 30 // suponha que você tem 30 dias de produção

int main() {
    int i, j;
    FILE *arquivo, *relatorio;
    char linha[100];
    int maquinas[NUM_MAQUINAS][NUM_DIAS] = {0}; 

    arquivo = fopen("producao.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo)!= NULL) {
        char data[11];
        char hora[6];
        int numeroMaquina, dia;

        sscanf(linha, "%10[^;];%5[^;];%d", data, hora, &numeroMaquina);
        dia = atoi(data) - 1; // convertendo a data para um número de dia (0-29)

        if (numeroMaquina >= 1 && numeroMaquina <= NUM_MAQUINAS && dia >= 0 && dia < NUM_DIAS) {
            maquinas[numeroMaquina - 1][dia]++;
        }
    }

    fclose(arquivo);

    relatorio = fopen("explosivos.md", "w");
    if (relatorio == NULL) {
        printf("Erro ao criar o arquivo de relatório.\n");
        return 1;
    }

    fprintf(relatorio, "| Dia | Máquina 1 | Máquina 2 | Máquina 3 | Máquina 4 |\n");
    fprintf(relatorio, "| --- | --- | --- | --- | --- |\n");

    for (i = 0; i < NUM_DIAS; i++) {
        fprintf(relatorio, "| %d |", i + 1);
        for (j = 0; j < NUM_MAQUINAS; j++) {
            fprintf(relatorio, " %d |", maquinas[j][i]);
        }
        fprintf(relatorio, "\n");
    }

    fclose(relatorio);

    return 0;
}
