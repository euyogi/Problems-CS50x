#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Declaro a variável 'camadas' para o while funcionar.
    int camadas;
    //Recebe um valor inteiro do usuário que corresponde a altura e, consequentemente, à -
    //quantidade de camadas da pirâmide.
    //Irá requisitar o valor até ser um valor entre 1 e 8 por convenção.
    do
    {
        camadas = get_int("Altura: ");
    }
    while (camadas < 1 || camadas > 8);

    //Esse for corresponde a cada camada da pirâmide.
    for (int camada_atual = 1; camada_atual <= camadas; camada_atual++)
    {
        //Esse for corresponde à quantidade de espaços antes dos blocos.
        for (int nEspacos = camadas - camada_atual; nEspacos > 0; nEspacos--)
        {
            printf(" ");
        }
        //Esse for corresponde à quantidade de blocos em cada camada.
        for (int nDeBlocos = 1; nDeBlocos <= camada_atual; nDeBlocos++)
        {
            printf("#");
        }
        //Espaço após os blocos da primeira parte
        printf("  ");
        //Blocos da segunda parte
        for (int nDeBlocos = 1; nDeBlocos <= camada_atual; nDeBlocos++)
        {
            printf("#");
        }
        //Quebra linha após cada camada.
        printf("\n");
    }
}
