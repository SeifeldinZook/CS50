#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }


    // ******************************************
    // for (int v = 0; v < voter_count; v++) {
    //     for (int w = 0; w < candidate_count; w++) {
    //         printf("[%i][%i]: %i - ", v, w, preferences[v][w]);
    //     }
    //     printf("\n");
    // }
    // ******************************************


    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // printf("=voter: %i\n", voter);
    // printf("=rank: %i\n", rank);
    // printf("=name: %s\n", name);
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k].name, name) == 0)
        {
            // printf("=k: %i\n", k);
            preferences[voter][rank] = k;
            // printf("preferences[%i][%i]: %i\n", voter, rank, preferences[voter][rank]);
            return true;
        }

    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    bool votingDone;
    // voterNo = 0   :5
    for (int voterNo = 0; voterNo < voter_count; voterNo++)
    {
        votingDone = false;
        // voterRank = 0   :3
		for (int voterRank = 0; voterRank < candidate_count && !votingDone; voterRank++)
		{
			int c = preferences[voterNo][voterRank];
    		if (!candidates[c].eliminated)
    		{
                candidates[c].votes++;
                votingDone = true;
            }
        }
    }

    // ******************************************
    // for (int w = 0; w < candidate_count; w++) {
    //     printf("%s votes %i\n", candidates[w].name ,candidates[w].votes);
    // }
    // ******************************************
    return;
}

// Print the winner of the election, if there is one
bool print_winner()
{
    int votesNeededToWin = round((float) voter_count / 2);
    // printf("x: %i\n", x);
    // printf("voter_count %i\n", voter_count);
    // printf("candidates[1].votes: %i\n", candidates[1].votes);
    // printf("candidates[2].votes: %i\n", candidates[2].votes);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > votesNeededToWin)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minVotes = candidates[0].votes;
	for (int i = 1; i < candidate_count; i++)
	{
		if (minVotes > candidates[i].votes && !candidates[i].eliminated)
		{
		    minVotes = candidates[i].votes;
		}
    }
    // printf("minVotes: %i\n", minVotes);
    return minVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
