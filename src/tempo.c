#include "tempo.h"
#include <time.h>


clock_t tempo_inicial;
clock_t tempo_final;


void inicia_clock() {
    tempo_inicial = clock();
}


void finaliza_clock() {
    tempo_final = clock();
}


double tempo_execucao() {
    return ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;


}


