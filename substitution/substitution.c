// Criptografa um texto de acordo com uma chave dada que consiste de um rearranjo do alfabeto.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Declara a chave e uma string com o alfabeto para comparar depois.
    string key = argv[1];
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    // Mostra na tela mensagens de erro se a chave for inválida (nenhuma ou mais de uma chave,
    // menos ou mais de 26 letras, letras repetidas, incluir símbolos ou números).
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        // Verifica cada caractére da chave para conferir se é uma letra e se a mesma não se repete.
        int i, j, k;
        for (i = 0, j = 0; i < 26; i++)
        {
            if (isalpha(key[i]))
            {
                key[i] = tolower(key[i]);
                for (k = 0; k < 26; k++)
                {
                    if (key[i] == key[k])
                    {
                        j++;
                    }
                }
            }
            else
            {
                printf("Key must only contain letters.\n");
                return 1;
            }
        }
        if (j != 26)
        {
            printf("Key must contain each letter only once.\n");
            return 1;
        }

        // Caso a chave seja válida, insere no texto criptografado as letras correspondentes.
        else
        {
            //Declara as variáveis para perguntar ao usuário o texto, confere o tamanho do texto e declara a lista do texto criptografado.
            string plaintext = get_string("plaintext:  ");
            int lenPlain = strlen(plaintext);
            char ciphertext[lenPlain];

            // Repete o processo de acordo com o tamanho do texto inserido para criptografar cada letra.
            for (i = 0; i <= lenPlain; i++)
            {
                // Se for uma letra checa se é maiúscula ou minúscula e substitui pela correspondente na chave inserida anteriormente.
                if (isalpha(plaintext[i]))
                {
                    // Repete o processo 26 vezes (tamanho do alfabeto), para comparar letras e encontrar a letra criptografada correspondente.
                    for (j = 0; j < 26; j++)
                    {
                        if (plaintext[i] == alphabet[j])
                        {
                            ciphertext[i] = key[j];
                        }
                        else if (plaintext[i] == toupper(alphabet[j]))
                        {
                            ciphertext[i] = toupper(key[j]);
                        }
                    }
                }
                
                // Se não for uma letra apenas a insere normalmente no texto criptografado.
                else
                {
                    ciphertext[i] = plaintext[i];
                }
            }

            // Mostra na tela o texto criptografado.
            printf("ciphertext: %s\n", ciphertext);
        }
    }
}
