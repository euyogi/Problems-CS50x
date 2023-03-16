// Criptografa um texto inserido pelo usuário de acordo com a chave dada pelo mesmo.

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Caso o usuário não digite uma chave ou digite várias.
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Declara a variável 'k' que é a chave para a criptografia.
    int k = atoi(argv[1]) % 26;

    // Caso o usuário digite uma chave negativa ou não inteira.
    if (k <= 0)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

    // Pede ao usuário o texto à ser criptografado e guarda-o na variável.
    string plaintext = get_string("plaintext:  ");

    // Verifica o tamanho do texto inserido.
    int lenText = strlen(plaintext);

    // Declara a variável do texto criptografado.
    char ciphertext[lenText];

    // Adiciona à variável do texto criptografado cada letra do texto normal, agora criptogafadas.
    for (int i = 0; i < lenText; i++)
    {
        // Reseta a variável da chave, para as próximas letras.
        k = atoi(argv[1]) % 26;

        // Se for uma letra faz com que casos como 'z + 1' virem 'a' e não um símbolo qualquer.
        if (isalpha(plaintext[i]))
        {
            // Para letras minúsculas.
            if (islower(plaintext[i]))
            {
                if (plaintext[i] + k > 122)
                {
                    k = k - 26;
                }
            }

            // Para letras maiúsculas.
            else
            {
                if (plaintext[i] + k > 90)
                {
                    k = k - 26;
                }
            }

            // Codifica a letra para ela mudar para outra letra de acordo com a chave.
            ciphertext[i] = plaintext[i] + k;
        }

        // Se o caractére não for uma letra o adiciona ao texto criptografado normalmente.
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Mostra na tela o texto criptografado.
    printf("ciphertext: %s\n", ciphertext);
}
