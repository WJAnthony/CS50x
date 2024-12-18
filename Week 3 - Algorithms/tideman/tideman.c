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
} pair;

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
void swap(pair small[], pair big[]);
bool loop_test(int graph_head, int loser);

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
    // Loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    // For each voter, update global preference
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Adding pairs into pairs array
    int n = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Preferences are only one way as only one arrow between candidates
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[n].winner = i;
                pairs[n].loser = j;
                n++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort pairs using bubble sort
    for (int j = 0; j < pair_count; j++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                swap(&pairs[i], &pairs[i + 1]);
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (loop_test(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int source;
    for (int i = 0; i < candidate_count; i++)
    {
        // Set status to false to represents that ith candidate has no edges pointing at it at the start
        bool status = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                // Update status to show that ith candidate has 1 edge pointing at it
                status = true;
                break;
            }
        }
        // If after running through all candidates, status is still false, ith candidate is source
        if (status == false)
        {
            source = i;
        }
    }
    printf("%s\n", candidates[source]);
    return;
}

// Swap function
void swap(pair small[], pair big[])
{
    pair temp = *small;
    *small = *big;
    *big = temp;
}

// Recursive function to check if a loop is formed
bool loop_test(int graph_head, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Base case
        if (loser == graph_head)
        {
            return true;
        }
        // Allowing the pair to become locked
        else if (locked[loser][i] == true)
        {
            // Recursive call to see if original graph head has beaten
            if (loop_test(graph_head, i))
            {
                return true;
            }
        }
    }
    return false;
}
