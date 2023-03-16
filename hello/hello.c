#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Mostra na tela 'hello, nome digitado'.
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
