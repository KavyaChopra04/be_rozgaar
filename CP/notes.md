# D_1_Hot_Start_Up 

1. Key idea: we needed to store `dp[i][k1][k2]` where k1 is the last program run on CPU1 and k2 is the last program run on CPU2. But the space constraints don't permit this
2. Be smarter with space optimisation: note that at each given i, atleast one of k1 and k2 is arr[i]. So instead of k^2 space complexity for each n, we can have O(2k) space complexity, and use that for our transitions

# D_Explorer_Space

1. Key idea: store `dp[x][y][steps]`. Note that the minimum path will be a retrace, so its the path from a neighbour to itself in k-2 steps + 2*edge between neighbour and current cell

# C_The_Sports_Festival

1. Key idea: DEQUE DP
2. Sort stuff, at each point there is a choice to remove the maximum or minimum elements (first or last)
3. These kind of problems can be tackled in O(n^2) by making `dp[i][j]` where `i` and `j` are array indices as our state

# J_Sushi
1. Key Idea: Space optimisation, and noticing that the answer only depends on the cardinality of 0, 1, 2 and 3 sushi plates. Can store 1, 2 and 3's number and subtract their sum from n to get the number of 0 plates
2. Think recursively in expected value questions, what happens when you make the smallest possible change (eating a sushi here)

# D_Omkar_and_Bed_Wars
1. Key Idea :  Don't jump straight to DP, get a feel for the problem first. Doable in greedy.

