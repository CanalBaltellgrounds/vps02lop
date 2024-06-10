#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAQUINAS 4

int main() {
    int i;
    FILE *arquivo;
    char linha[100];
    int maquinas[NUM_MAQUINAS] = {0}; 

   
    arquivo = fopen("producao.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char data[11];
        char hora[6];
        int numeroMaquina;

       
        sscanf(linha, "%10[^;];%5[^;];%d", data, hora, &numeroMaquina);

       
        if (numeroMaquina >= 1 && numeroMaquina <= NUM_MAQUINAS) {
            maquinas[numeroMaquina - 1]++;
        }
    }

    
    fclose(arquivo);

 
    printf("Quantidade de exposições produzidas por cada máquina:\n");
    for (i = 0; i < NUM_MAQUINAS; i++) {
        printf("Máquina %d: %d\n", i + 1, maquinas[i]);
    }

    return 0;
}
