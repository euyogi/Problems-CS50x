#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool hasCycle(int w, int l);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Varre todos os candidatos, se o nome for igual ao nome do candidato
    // o adiciona na lista ranks com seu respectivo rank
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Compara se houver um candidato com melhor rank e um com pior rank, significa que o eleitor prefere o com melhor rank
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                for (int l = 0; l < candidate_count; l++)
                {
                    if (ranks[i] == j && ranks[k] == l && i < k)
                    {
                        preferences[j][l]++;
                    }
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Varre todas as preferências e se mais eleitores tiverem preferido um candidato a outro
    // O  candidato preferido viro o ganhador do par, e o menos preferido o perdedor do par
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Lista de forças de vitória de cada par
    int strength[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser]
                      - preferences[pairs[i].loser][pairs[i].winner];
    }

    // Se a força do par for a maior força, o par é ordenado a posição mais a esquerda da lista
    for (int i = 0; i < pair_count; i++)
    {
        int index = i;
        for (int j = 1 + i; j < pair_count; j++)
        {
            if (strength[j] > strength[index])
            {
                index = j;
            }
        }
        int copyStrength = strength[i];
        strength[i] = strength[index];
        strength[index] = copyStrength;
        pair copyPair = pairs[i];
        pairs[i] = pairs[index];
        pairs[index] = copyPair;
    }
    return;
}

bool hasCycle(int w, int l)
{
    // Se já houver uma seta apontada do perdedor pro ganhador, se
    // agora, o ganhador apontar uma seta a ele formará um ciclo
    if (locked[l][w])
    {
        return true;
    }

    // Confere se o perdedor aponta uma seta para outro candidato
    // E confere se esse candidato aponta uma seta para o ganhador
    // Se sim, se o ganhador apontar uma seta para o perdedor, formará um ciclo
    // Se não confere se esse candidato aponta a seta para outro candidato
    // E confere se o outro candidato aponta uma seta para o ganhador
    // Se sim, se o ganhador apontar uma seta para o perdedor, formará um ciclo
    // (É um processo de recursão)
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[l][i] && hasCycle(w, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Se não for criar um ciclo, cria a seta entre os candidatos do par
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        if (!hasCycle(w, l))
        {
            locked[w][l] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Se não houver nenhuma seta para tal candidato, ele é o vencedor
    for (int i = 0; i < candidate_count; i++)
    {
        bool isSource = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isSource = false;
            }
        }
        if (isSource)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}