// Ejercicio 5
// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum number
// of integers required
int minNumbers(int x, int *arr, int n)
{
    // Queue for BFS
    queue<int> q;

    // Base value in queue
    q.push(x);

    // Boolean array to check if a number has been
    // visited before
    unordered_set<int> v;

    // Variable to store depth of BFS
    int d = 0;

    // BFS algorithm
    while (q.size())
    {

        // Size of queue
        int s = q.size();
        while (s--)
        {

            // Front most element of the queue
            int c = q.front();

            // Base case
            if (!c)
                return d;
            q.pop();
            if (v.find(c) != v.end() or c < 0)
                continue;

            // Setting current state as visited
            v.insert(c);

            // Pushing the required states in queue
            for (int i = 0; i < n; i++)
                q.push(c - arr[i]);
        }

        d++;
    }

    // If no possible solution
    return -1;
}

// Driver code
int main()
{
    int arr[] = {1, 5, 12};
    int n = sizeof(arr) / sizeof(int);
    int x = 15;

    cout << minNumbers(x, arr, n);

    return 0;
}