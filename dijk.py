import heapq

def dijkstra(graph, start):
    # Initialize distances to infinity
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    
    # Priority Queue: (distance, node)
    pq = [(0, start)]
    
    while pq:
        current_dist, current_node = heapq.heappop(pq)
        
        # Optimization: If we found a shorter way to this node already, skip
        if current_dist > distances[current_node]:
            continue
        
        # Check neighbors
        for neighbor, weight in graph[current_node].items():
            distance = current_dist + weight
            
            # Relaxation Step
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))
                
    return distances
