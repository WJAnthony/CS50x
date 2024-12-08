

for i to n-i
find largest number between preferences[pairs[i].winner][pairs[i].loser] and preferences[pairs[n-1].winner][pairs[n-1].loser]
swap largest number with preferences[pairs[i].winner][pairs[i].loser]

void swap(pair small, pair big)

for (int n = 0; n < pair_count; n++)
{
    int greatest_victory = 0
    for (int j = 0; j < pair_count; j++)
    {
        if (preferences[pairs[j].winner][pairs[j].loser] > greatest_victory)
        {
            greatest_victory = preferences[pairs[j].winner][pairs[j].loser];
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] == greatest_victory)
        {
            swap(pairs[i], pairs[n]);
        }
    }
    int j++;
}

void swap(pair small, pair big)
{
    pair temp = pair small;
    pair small = pair big;
    pair big = temp;
}


for (int j = 0; j < pair_count; j++)
{
    for (int i = 0; i < pair_count -1; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i].winner][pairs[i].loser])
        {
            swap(pairs[i], pairs[i + 1]);
        }
    }
}


for (int j = 1; j < number_of_heads; i++)
{
    if (head_of_graph[i] == head_of_graph[i - j])
    {
        return;
    }
}


bool test(int new_head, int current_head_count)
{
    for (int j = 0; j < current_head_count - 1; i++)
    {
        if (new_head == head_of_graph[j])
        {
        return false;
        }
    }
    return true;
}



bool test(int new_head, int current_head_count, int head_of_graph[])
{
    for (int j = 0; j < current_head_count - 1; j++)
    {
        if (new_head == head_of_graph[j])
        {
        return false;
        }
    }
    return true;
}


        head_of_graph[i] = pairs[i].winner;
        if (!test(head_of_graph[i], number_of_heads, head_of_graph))
        {
            return;
        }

// Recurison function to test if pair makes a loop

bool loop_test (int graph_head, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Base case
        if (loser == graph_head)
        {
            return true;
        }
        // Allowing the pair to become locked
        else if (locked[loser][i] = true)
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

int source;
for (int i = 0; i < candidate_count; i++)
{
    // Status:false represents that ith candidate has no edges pointing at it
    bool status = false
    for (int j = 0; j < candidate_count; j++)
    {
       if (locked[j][i] == true)
       {
        // Update status to show that ith candidate 1 edge pointing at it
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


bool indicator
