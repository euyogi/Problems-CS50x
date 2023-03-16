// Analisa um texto e mostra na tela qual a série escolar correspondente a complexidade desse texto.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Pede ao usuário o texto e mostra ele na tela.
    string texto = get_string("Text: ");
    printf("%s\n", texto);

    // Verifica o tamanho do texto.
    int tamTexto = strlen(texto);

    // Declara as variáveis que mostrarão a quantidade de elementos respectivos no texto.
    int nLetras = 0;
    int nSentencas = 0;
    int nPalavras = 0;

    for (int i = 0; i < tamTexto; i++)
    {
        // Verifica se é uma letra e soma ao contador.
        if (isalpha(texto[i]))
        {
            nLetras++;
        }
        // Verifica se há uma letra seguida de '.' ou ',' ou '?', se há: soma ao contador.
        if (isalpha(texto[i]) != 0 && (texto[i + 1] == '.' || texto[i + 1] == '!' || texto[i + 1] == '?'))
        {
            nSentencas++;
        }
        // Verifica se há uma letra seguida de uma não letra, se há: soma ao contador.
        if (isalpha(texto[i]) != 0 && isalpha(texto[i + 1]) == 0 && texto[i + 1] != '-'
            && texto[i + 1] != 39)
        {
            nPalavras++;
        }
    }

    // Declara as variáveis que serão utilizadas na fórmula.
    // L é a média de letras a cada 100 palavras.
    float L = (1.0 * nLetras / nPalavras) * 100;

    // S é a média de sentenças a cada 100 palavras.
    float S = (1.0 * nSentencas / nPalavras) * 100;

    // Fórmula de Coleman-Liau: calcula qual série compatível com o texto analisado.
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Formatação para mostrar na tela a série correspondente.
    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}
