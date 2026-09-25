#include <stdio.h>
#include "../../include/tempo.h" // Caminho correto para o cabeçalho do professor

int main() {
    inicia_clock();
    
    // Um loop maior para fazer o computador trabalhar por alguns milissegundos
    double soma = 0;
    for (int i = 0; i < 100000000; i++) {
        soma += i;
    }
    
    finaliza_clock();
    
    printf("Resultado: %f\n", soma);
    printf("Tempo de execucao: %fs\n", tempo_execucao());
    
    return 0;
}
