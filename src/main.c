#include <stdio.h>
#include "tempo.h"


int main(){
    inicia_clock();
    for(int i=0; 1<100000; i++){
    }
    finaliza_clock();


    printf("gastou %fs\n", tempo_execucao());


    return 0;


}
