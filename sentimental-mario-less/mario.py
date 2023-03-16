from cs50 import get_int

# Pergunta ao usuário qual a altura da semi-pirâmide, (entre 1 e 8)
while True:
    height = get_int('Height: ')

    if 1 <= height <= 8:
        break

# Mostra na tela os blocos da pirâmide
for c in range(height):
    c += 1
    print(' ' * (height - c) + '#' * c)
