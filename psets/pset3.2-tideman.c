#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool lockedtransitive[MAX][MAX];

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
void lock_pairs(void);
void print_winner(void);
int strength_victory(int pair_number);
void recursive_lock(int i);

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
        // ranks[i] is voter's ith preference, and rank[i] is an integer 0 < rank[i] < candidate_count
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
        // Aggregate the voter ranks into the preferences matrix
        record_preferences(ranks);

        printf("\n");
        // Looping over all voters, the (i,j) entry tells us
        // how many voters prefer candidates[i] over candidates[j]
    }
    // For all (i,j) pairs in preferences matrix, if (i,j) > (j,i),
    // add (i,j) to pairs struct
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; // i refers to candidate[i]
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Let pair_number be the index of pairs
    int pair_number = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_number].winner = i;
                pairs[pair_number].loser = j;
                pair_number += 1;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_number].winner = j;
                pairs[pair_number].loser = i;
                pair_number += 1;
            }
        }
    }
    pair_count = pair_number;
    return;
}

int strength_victory(int pair_number)
{
    return preferences[pairs[pair_number].winner][pairs[pair_number].loser];
}

// Sort pairs in decreasing order by strength of victory (selection sort)
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j < pair_count; j++)
        {
            int count = 0;
            for (int k = i; k < pair_count; k++)
            if (strength_victory(k) > strength_victory(j))
            {
                count += 1;
                break;
            }
            if (count == 0) // Then we know strenth_victory(j) is maximum
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;

}

void recursive_lock(int i)
{
    // Create a temporary testing graph
    bool lockedtemp[MAX][MAX];
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = 0; b < candidate_count; b++)
        {
            lockedtemp[a][b] = lockedtransitive[a][b];
        }
    }

    // Apply the proposed edge onto test graph
    lockedtemp[pairs[i].winner][pairs[i].loser] = true;

    // Close the graph under transitivity
    for (int j = 0; j < candidate_count; j++)
    {
        if (lockedtemp[pairs[i].loser][j] == true)
        {
            lockedtemp[pairs[i].winner][j] = true;
        }
        if (lockedtemp[j][pairs[i].winner] == true)
        {
            lockedtemp[j][pairs[i].loser] = true;
        }
    }
    // Check that there are no cycles by checking for violations of antisymmetry
    int counter = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            if (lockedtemp[j][k] == true && lockedtemp[k][j] == true)
            {
                counter += 1;
            }
        }
    }
    if (counter == 0)
    {
        // Push the changes in lockedtemp to lockedtransitive and apply the proposed edge to the main graph

        // Main graph
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Transitive graph
        for (int a = 0; a < candidate_count; a++)
        {
            for (int b = 0; b < candidate_count; b++)
            {
                lockedtransitive[a][b] = lockedtemp[a][b];
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
// We may assume that there will not be more than one "source"
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        recursive_lock(i);
    }
}
// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                counter += 1;
                break;
            }
        }
        if (counter == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}