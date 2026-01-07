from collections import deque

# BFS for a single connected component
def bfsConnected(adj, src, visited, res):
    q = deque() # Creates a new double-ended queue
    visited[src] = True # Initially marks the starting node visited to prevent from being processed again
    q.append(src) # Adds the starting node to the queue to start the loop

    while q: # This loop continues running as long as there are nodes waiting in the queue.
        curr = q.popleft() # Removes the node in the front of the queue
        res.append(curr) # Records the node in the list

        # visit all the unvisited
        # neighbours of current node
        for x in adj[curr]: # Looks in the adjacency list for the current node. The list that contains all neighbors of curr
            if not visited[x]: # Checks if x is visited
                visited[x] = True # If new, mark as visited immediately
                q.append(x) # Add the neighbor to the back of the queue for processing later
                
# BFS for all components (handles disconnected graphs)
def bfs(adj):
    V = len(adj) 
    visited = [False] * V
    res = []

    for i in range(V):
        if not visited[i]:
            bfsConnected(adj, i, visited, res)
    return res

def addEdge(adj, u, v):
    adj[u].append(v)
    adj[v].append(u)
  
  
if __name__ == "__main__":
    V = 6
    adj = []
    
    # creating adjacency list
    for i in range(V):
        adj.append([])
        
    addEdge(adj, 1, 2)
    addEdge(adj, 2, 0)
    addEdge(adj, 0, 3)
    addEdge(adj, 5, 4)

    res = bfs(adj)

    for node in res:
        print(node, end=" ")
